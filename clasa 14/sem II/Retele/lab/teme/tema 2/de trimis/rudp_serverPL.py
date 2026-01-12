# Server
import socket
import logging
import rudp

logging.basicConfig(format = u'[LINE:%(lineno)d]# %(levelname)-8s [%(asctime)s]  %(message)s', level = logging.NOTSET)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, proto=socket.IPPROTO_UDP)

port = 10000
adresa = 'localhost'
server_address = (adresa, port)
sock.bind(server_address)

print(f"Serverul a pornit pe {adresa} si portul {port}\n\n")

rudp.threeWayHandshakeServerPL(sock)
rudp.sendServer(sock)
