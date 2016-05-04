CC     = gcc
DEBUG  = -ggdb3
#CFLAGS = $(DEBUG) -Wall -pthread 
#LDLIBS = -lpthread -ldb
LDLIBS = -lpthread
webServer: webServer.o tcpServer.o logger.o menu.o connectionHandler.o threads.o $(CFLAGS) $(LDLIBS)
webServer.o: webServer.c tcpServer.h logger.h menu.h connectionHandler.h tipos.h
	$(CC) -c $(CFLAGS) -o webServer.o webServer.c $(LDFLAGS)
menu.o: menu.c menu.h logger.h
	$(CC) -c $(CFLAGS) -o menu.o menu.c $(LDFLAGS)
logger.o: ../logger/logger.c logger.h
	$(CC) -c $(CFLAGS) -o logger.o ../logger/logger.c $(LDFLAGS)
tcpServer.o: tcpServer.c tcpServer.h
	$(CC) -c $(CFLAGS) -o tcpServer.o tcpServer.c $(LDFLAGS)
connectionHandler.o: connectionHandler.c connectionHandler.h
	$(CC) -c $(CFLAGS) -o connectionHandler.o connectionHandler.c $(LDFLAGS)
threads.o: threads.c threads.h
	$(CC) -c $(CFLAGS) -o threads.o threads.c $(LDFLAGS)