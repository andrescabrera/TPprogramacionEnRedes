#include "peticion.h"

int readMessage(int socketDescriptorCliente, char *mensaje);
char *substring(char *unString, int start, int end);
void processMessage(char *mensaje);

void atenderPeticion(int socketDescriptor)
{
    char *message = malloc(8092);
    char logMessage[256];
    int salida = 0;
    
    do
    {
        salida = readMessage(socketDescriptor, message);
        if(salida == -1)
        {
            sprintf(logMessage, "ERROR: Cliente %d desconectado abruptamente. Cerrando thread\n", socketDescriptor);
        }
        else if (salida == 0)
        {
            sprintf(logMessage, "Cliente %d desconectado de forma normal.\n", socketDescriptor);
        }
        logger(logMessage);
        processMessage(message);
    }
    while(salida > 0);  //TODO El corte debería ser el error de read_message, por ejemplo que se desconecto el cliente es un 0...
    //FD_CLR(argumentosDelThread->socketDescriptor, &readset);
}

int readMessage(int clientSocketDescriptor, char *message)
{
    int bufferSize = 256;
    char buffer[bufferSize];
    int result;
    int retorno;
    logger("funcion readMessage");
    
    do
    {
        memset(buffer, '\0', bufferSize);
        result = read(clientSocketDescriptor, buffer, bufferSize);
        strcat(message, buffer);
    }
    while (result != -1 && result == bufferSize && errno != EINTR);
    return result;
}

void processMessage(char *message)
{
    printf("funcion processMessage\n");
    printf("Full Message:\n");
    logger(message);
}

char *substring(char *unString, int start, int end) {
    char *subbuff = malloc(end - start);
    memcpy(subbuff, unString + start, end - start);
    subbuff[end - start] = '\0';
    return subbuff;
}