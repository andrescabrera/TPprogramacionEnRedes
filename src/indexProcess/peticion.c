#include "peticion.h"

int readMessage(int socketDescriptorCliente, char *mensaje);
int sendMessage(int socketDescriptorCliente, char *mensaje);
char *substring(char *unString, int start, int end);
void processPath(char *path, int socketDescriptorCliente);

void atenderPeticion(int socketDescriptor)
{
    char *path = malloc(8092);
    char logMessage[256];
    int salida = 0;
    
    do
    {
        salida = readMessage(socketDescriptor, path);
        if(salida == -1)
        {
            sprintf(logMessage, "ERROR: Cliente %d desconectado abruptamente. Cerrando thread\n", socketDescriptor);
        }
        else if (salida == 0)
        {
            sprintf(logMessage, "Cliente %d desconectado de forma normal.\n", socketDescriptor);
        }
        logger(logMessage);
        processPath(path, socketDescriptor);
    }
    while(salida > 0);
    //FD_CLR(socketDescriptor, &readset);
}

int sendMessage(int clientSocketDescriptor, char *message)
{
     send(clientSocketDescriptor, message, strlen(message), 0);
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

void processPath(char *path, int socketDescriptor)
{
    printf("funcion processMessage\n");
    printf("Full Message:\n");
    logger(path);
    // TODO get Absolute path from BerkleyDB
    char absolutePath[256] = "absolute path";
    sendMessage(socketDescriptor, absolutePath);
}

char *substring(char *unString, int start, int end) {
    char *subbuff = malloc(end - start);
    memcpy(subbuff, unString + start, end - start);
    subbuff[end - start] = '\0';
    return subbuff;
}