CC=gcc
CFLAGS=-lpthread 
webServer: webServer.o tcpServer.o logger.o menu.o connectionHandler.o
webServer.o: webServer.c tcpServer.h logger.h menu.h connectionHandler.h
	$(CC) $(CFLAGS) -c -o webServer.o webServer.c
menu.o: menu.c menu.h logger.h
	$(CC) $(CFLAGS) -c -o menu.o menu.c
logger.o: ../logger/logger.c logger.h
	$(CC) $(CFLAGS) -c -o logger.o logger.c
tcpServer.o: tcpServer.c tcpServer.h
	$(CC) $(CFLAGS) -c -o tcpServer.o tcpServer.c
connectionHandler.o: connectionHandler.c connectionHandler.h
	$(CC) $(CFLAGS) -c -o connectionHandler.o connectionHandler.c