#ifndef THREADS_H_INCLUDED
#define THREADS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/un.h>
#include <sys/socket.h>

void lanzarThread(int socket_server);
void *atenderPeticion (void *argumentos);

#endif