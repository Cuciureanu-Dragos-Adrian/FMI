import random as rand
import struct
import socket
from re import S
from threading import TIMEOUT_MAX
from time import time
from urllib import response

# FLAGS
SYN_FLAG = 0b10000000
SEQ_FLAG = 0b01000000
ACK_FLAG = 0b00100000
SYN_ACK_FLAG = 0b10100000
PSH_FLAG = 0b00010000
FIN_FLAG = 0b00001000

timeOut = 1
sizeRECVFORM = 4096
triesSendPacket = 10
seqNumberClient = None
seqNumberServer = None
ackNumber = 0

hadoba = False


g = open('out.txt', "w")

def createSequenceNumbers():
    global seqNumberClient, seqNumberServer

    seqNumberClient = rand.randint(0, 2 ** 16 - 1)
    seqNumberServer = rand.randint(0, 2 ** 16 - 1)

    while seqNumberClient == seqNumberServer:
        seqNumberServer = rand.randint(0, 2 ** 16 - 1)

    
def createHeader(seqNumber, ackNumber, flags, mesage = ''):
    header = struct.pack('!H', seqNumber)
    header += struct.pack('!H', ackNumber)
    header += struct.pack('B', flags)
    header += bytes(mesage, 'utf-8')

    return header


def unpackHeader(header):
    seqNumber = struct.unpack('!H', header[:2])[0]
    ackNumber = struct.unpack('!H', header[2:4])[0]
    flags = struct.unpack('B', header[4:5])[0]

    return seqNumber, ackNumber, flags


def unpackHeaderMesage(header):
    seqNumber = struct.unpack('!H', header[:2])[0]
    ackNumber = struct.unpack('!H', header[2:4])[0]
    flags = struct.unpack('B', header[4:5])[0]
    mesage = header[5:].decode('utf-8')

    return seqNumber, ackNumber, flags, mesage


def incrementNumber(number, increment):
    return (number + increment) % (2 ** 16)


def threeWayHandshakeClient(sockClient, server):
    global seqNumberClient

    # print(f"Handshake starting\n")
    # sockClient.settimeout(timeOut)

    # print("1. SYN part of the 3-way handshake\n")

    # create the first header and send the packet to the server with the SYN flag
    headerSYN = createHeader(seqNumberClient, 0, SYN_FLAG)
    sockClient.sendto(headerSYN, server)

    responseFromServer, serverAdress = sockClient.recvfrom(sizeRECVFORM)

    # get the return from the server
    seqServer, ackNumberServer, flags = unpackHeader(responseFromServer)

    # verify the response (ackNumberServer) and if it has the SYN and ACK flags
    if flags & SYN_ACK_FLAG and ackNumberServer == incrementNumber(seqNumberClient, 1):
        # print("3. ACK part of the 3-way handshake\n")

        # create another header to send the ACK flag
        seqNumberClient = incrementNumber(seqNumberClient, 1)
        seqServer = incrementNumber(seqServer, 1)
        headerACK = createHeader(seqNumberClient, seqServer, ACK_FLAG)

        sockClient.sendto(headerACK, server)


def threeWayHandshakeServer(sockServer):
    global seqNumberServer

    responseFromClient, clientAdress = sockServer.recvfrom(sizeRECVFORM)
    seqClient, ackNumberClient, flags = unpackHeader(responseFromClient)

    if flags & SYN_FLAG:
        # print("2. SYN/ACK part of the 3-way handshake\n")

        ackNumberServer = incrementNumber(seqClient, 1)
        headerSYNACK = createHeader(seqNumberServer, ackNumberServer, SYN_ACK_FLAG)
        sockServer.sendto(headerSYNACK, clientAdress)

        responseFromClient, clientAdress = sockServer.recvfrom(sizeRECVFORM)
        seqClient, ackNumberClient, flags = unpackHeader(responseFromClient)

        if flags & ACK_FLAG and ackNumberClient == incrementNumber(seqNumberServer, 1):
            seqNumberServer = incrementNumber(seqNumberServer, 1)

            # print(f"{seqClient, seqNumberServer}")
            # print(f"Handshake with {clientAdress} completed\n")


def threeWayHandshakeClientPL(sockClient, server):
    global seqNumberClient, hadoba

    sockClient.settimeout(timeOut)

    while True:
        headerSYN = createHeader(seqNumberClient, 0, SYN_FLAG)
        sockClient.sendto(headerSYN, server)
        
        try:
            responseFromServer, serverAdress = sockClient.recvfrom(sizeRECVFORM)
            seqServer, ackNumberServer, flags = unpackHeader(responseFromServer)

            if flags & SYN_ACK_FLAG and ackNumberServer == incrementNumber(seqNumberClient, 1):
                seqNumberClient = incrementNumber(seqNumberClient, 1)
                seqServer = incrementNumber(seqServer, 1)
                headerACK = createHeader(seqNumberClient, seqServer, ACK_FLAG)
                
                sockClient.sendto(headerACK, server)

                break
            
        except:
            print("sunt in except")
            continue

    hadoba = True

    while hadoba:
        try:
            headerACK = createHeader(seqNumberClient, seqServer, ACK_FLAG)
            sockClient.sendto(headerACK, server)

        except:
            break


def threeWayHandshakeServerPL(sockServer):
    global seqNumberServer

    sockServer.settimeout(timeOut)

    while True:
        try:
            responseFromClient, clientAdress = sockServer.recvfrom(sizeRECVFORM)
            seqClient, ackNumberClient, flags = unpackHeader(responseFromClient)

            if flags & SYN_FLAG:
                ackNumberServer = incrementNumber(seqClient, 1)
                headerSYNACK = createHeader(seqNumberServer, ackNumberServer, SYN_ACK_FLAG)
                sockServer.sendto(headerSYNACK, clientAdress)

                if hadoba == True:
                    break

        except:
            continue

    while hadoba:
        try:
            responseFromClient2, clientAdress = sockServer.recvfrom(sizeRECVFORM)
            seqClient, ackNumberClient, flags = unpackHeader(responseFromClient2)

            if flags & ACK_FLAG and ackNumberClient == incrementNumber(seqNumberServer, 1):
                seqNumberServer = incrementNumber(seqNumberServer, 1)
                hadoba = False

                break

        except:
            continue


def sendClient(sockClient, server):
    global seqNumberClient, seqNumberServer
    print(seqNumberClient, seqNumberServer)

    while True:
        mesage = input("\nenter your message: ")
        increment = len(mesage)

        headerPSH = createHeader(seqNumberClient, 0, PSH_FLAG, mesage)
        sockClient.settimeout(timeOut)

        while True:
            sockClient.sendto(headerPSH, server)

            try:
                responseFromServer, serverAdress = sockClient.recvfrom(sizeRECVFORM)
                seqServer, ackNumberServer, flags = unpackHeader(responseFromServer)
                
                if flags & ACK_FLAG and ackNumberServer == incrementNumber(seqNumberClient, 1):
                    seqNumberClient = incrementNumber(seqNumberClient, increment)
                    seqNumberServer = incrementNumber(seqNumberServer, 1)
                
                    sockClient.setblocking(True)

                    print(f"{seqNumberClient, seqNumberServer}")

                    if mesage == "end":
                        endConnectionClient(sockClient, server)
                        return

                    break
                
            except:
                continue     


def sendServer(sockServer):
    global seqNumberServer

    #sockServer.settimeout(timeOut)

    while True:
        while True:
            responseFromClient, clientAdress = sockServer.recvfrom(sizeRECVFORM)
            seqClient, ackNumberClient, flags, mesage = unpackHeaderMesage(responseFromClient)

            if flags & PSH_FLAG:
                ackNumberServer = incrementNumber(seqClient, 1)
                headerACK = createHeader(seqNumberServer, ackNumberServer, ACK_FLAG)
                sockServer.sendto(headerACK, clientAdress)

                print(f"Mesajul transmis este: {mesage}\n")

                sockServer.setblocking(True)

                if mesage == "end":
                    endConnectionServer(sockServer)
                    return

                break
                

def endConnectionClient(sockClient, server):
    global seqNumberClient

    headerFIN = createHeader(seqNumberClient, 0, FIN_FLAG)
    sockClient.sendto(headerFIN, server)

    responseFromServer, serverAdress = sockClient.recvfrom(sizeRECVFORM)
    seqServer, ackNumberServer, flags = unpackHeader(responseFromServer)

    if flags & ACK_FLAG and ackNumberServer == incrementNumber(seqNumberClient, 1):
        responseFromServer, serverAdress = sockClient.recvfrom(sizeRECVFORM)
        seqServer, ackNumberServer, flags = unpackHeader(responseFromServer)

        if flags & FIN_FLAG:
            seqNumberClient = incrementNumber(seqNumberClient, 1)
            seqServer = incrementNumber(seqServer, 1)
            headerACK = createHeader(seqNumberClient, seqServer, ACK_FLAG)
            sockClient.sendto(headerACK, server)

            sockClient.close()
            return


def endConnectionServer(sockServer):
    global seqNumberServer

    responseFromClient, clientAdress = sockServer.recvfrom(sizeRECVFORM)
    seqClient, ackNumberClient, flags = unpackHeader(responseFromClient)

    if flags & FIN_FLAG:
        ackNumberServer = incrementNumber(seqClient, 1)
        headerACK = createHeader(seqNumberServer, ackNumberServer, ACK_FLAG)
        sockServer.sendto(headerACK, clientAdress)

        headerFIN = createHeader(seqNumberServer, 0, FIN_FLAG)
        sockServer.sendto(headerFIN, clientAdress)

        responseFromClient, clientAdress = sockServer.recvfrom(sizeRECVFORM)
        seqClient, ackNumberClient, flags = unpackHeader(responseFromClient)

        if flags & ACK_FLAG and ackNumberClient == incrementNumber(seqNumberServer, 1):
            seqNumberServer = incrementNumber(seqNumberServer, 1)

            print("Succesfully ended conection!!!\n")

            sockServer.close()
            exit()


if seqNumberClient == seqNumberServer == None:
    createSequenceNumbers()
    