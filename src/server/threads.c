#include "threads.h"

typedef struct argumentosThread
{
    int socketDescriptor;
} strarg;

int readHttpMessage(int socketDescriptorCliente, char *mensajeHTTP);
char *substring(char *unString, int start, int end);
void processHttpMessage(char *mensajeHTTP);

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

void *atenderPeticion (void *arguments)
{
    strarg *threadArguments = (strarg*)arguments;
    char *httpMessage = malloc(8092);
    char logMessage[256];
    int salida = 0;
    
    do
    {
        salida = readHttpMessage(threadArguments->socketDescriptor, httpMessage);
        if(salida == -1)
        {
            sprintf(logMessage, "ERROR: Cliente %d desconectado abruptamente. Cerrando thread\n", threadArguments->socketDescriptor);;;
        }
        else if (salida == 0)
        {
            sprintf(logMessage, "Cliente %d desconectado de forma normal.\n", threadArguments->socketDescriptor);
        }
        logger(logMessage);
        processHttpMessage(httpMessage);
    }
    while(salida > 0);  //TODO El corte debería ser el error de read_message, por ejemplo que se desconecto el cliente es un 0...
    //FD_CLR(argumentosDelThread->socketDescriptor, &readset);
    return NULL;
}

int readHttpMessage(int clientSocketDescriptor, char *httpMessage)
{
    int bufferSize = 256;
    char buffer[bufferSize];
    int result;
    int retorno;
    logger("funcion readHttpMessage");
    
    do
    {
        memset(buffer, '\0', bufferSize);
        result = read(clientSocketDescriptor, buffer, bufferSize);
        strcat(httpMessage, buffer);
    }
    while (result != -1 && result == bufferSize && errno != EINTR);
    return result;
}

void processHttpMessage(char *httpMessage)
{
    printf("funcion processHttpMessage\n");
    printf("Full HTTP Message:\n");
    logger(httpMessage);
    char GET[4] = "GET\0";
    char *method = substring(httpMessage, 0, 3);
    logger("Method: ");
    logger(method);
    
    if(strcmp(method, GET) == 0) {
        
        int i = 0;
        while(httpMessage[i] != '\n')
        {
            i++;
        }

        char *path = substring(httpMessage, 4, i - 10);
        logger(path);
    }
}

char *substring(char *unString, int start, int end) {
    char *subbuff = malloc(end - start);
    memcpy(subbuff, unString + start, end - start);
    subbuff[end - start] = '\0';
    return subbuff;
}