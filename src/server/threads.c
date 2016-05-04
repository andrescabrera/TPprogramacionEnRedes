#include "threads.h"

typedef struct argumentosThread
{
    int socketDescriptor;
} strarg;

void lanzarThread(int socket_server)
{
    pthread_t unThread;
    pthread_attr_t atributos;

    if (pthread_attr_init(&atributos) != 0)
    {
        logger("Problema al inicializar los atributos del thread");
        exit(1);
    }

    strarg *argumentos;
    argumentos = (strarg*)calloc(1, sizeof(strarg));
    argumentos->socketDescriptor = socket_server;

    if((pthread_create(&unThread, &atributos, atenderPeticion, (void *)argumentos)) != 0)
    {
        logger("Problema al iniciar el thread");
    }
}

void *atenderPeticion (void *argumentos)
{
    logger("atenderPeticion");

    // TODO Recibir mensaje HTTP

    return NULL;
}