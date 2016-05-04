#ifndef THREADS_H_INCLUDED
#define THREADS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void lanzarThread(int socket_server);
void *atenderPeticion (void *argumentos);

#endif