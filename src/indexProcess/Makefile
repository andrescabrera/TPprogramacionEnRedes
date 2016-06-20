CC     = gcc
DEBUG  = -ggdb3
LDLIBS = -I./include -L./lib -ldb -lpthread
indexProcess: indexProcess.o tcpServer.o logger.o menu.o connectionHandler.o peticion.o db-access.o $(CFLAGS)
indexProcess.o: indexProcess.c tcpServer.h logger.h menu.h connectionHandler.h tipos.h db-access.h
	$(CC) -c $(CFLAGS) -o indexProcess.o indexProcess.c $(LDLIBS)
menu.o: menu.c menu.h logger.h
	$(CC) -c $(CFLAGS) -o menu.o menu.c $(LDLIBS)
logger.o: ../logger/logger.c logger.h
	$(CC) -c $(CFLAGS) -o logger.o ../logger/logger.c $(LDLIBS)
tcpServer.o: tcpServer.c tcpServer.h
	$(CC) -c $(CFLAGS) -o tcpServer.o tcpServer.c $(LDLIBS)
connectionHandler.o: connectionHandler.c connectionHandler.h
	$(CC) -c $(CFLAGS) -o connectionHandler.o connectionHandler.c $(LDLIBS)
peticion.o: peticion.c peticion.h db-api.h
	$(CC) -c $(CFLAGS) -o peticion.o peticion.c $(LDLIBS)
db-access.o: db-access.c db-access.h
	$(CC) -c $(CFLAGS) -o db-api.o db-api.c $(LDLIBS)