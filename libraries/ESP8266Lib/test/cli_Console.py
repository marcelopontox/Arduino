#!/usr/bin/env python 

from time import *
from socket import * 

HOST = '192.168.199.191'
#HOST = '192.168.1.7'
PORT = 8888
BUFSIZ = 1024 
ADDR = (HOST, PORT) 

tcpCliSock = socket(AF_INET, SOCK_STREAM) 
tcpCliSock.connect(ADDR) 

print "Receiving..."
while True: 
	#data = "Hello,I am Python."
	#data = raw_input('> ') 
	
	#data = ctime() +"$"+ data
	#if data:  
	#	tcpCliSock.send('%s\r\n' % data) 
	#sleep(1)	
	
	data = tcpCliSock.recv(BUFSIZ) 
	#if data == "EXIT": 
	#    break 
	print "Rev:",data.strip()
	
tcpCliSock.close()
print "TCP Client Closed."
