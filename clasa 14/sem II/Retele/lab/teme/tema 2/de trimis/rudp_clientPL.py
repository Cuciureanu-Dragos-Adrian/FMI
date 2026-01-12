# client
import socket
import logging
import sys
import rudp

logging.basicConfig(format = u'[LINE:%(lineno)d]# %(levelname)-8s [%(asctime)s]  %(message)s', level = logging.NOTSET)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, proto=socket.IPPROTO_UDP)

port = 10000
adresa = 'localhost'
serverAddress = (adresa, port)


rudp.threeWayHandshakeClientPL(sock, serverAddress)
rudp.sendClient(sock, serverAddress)
