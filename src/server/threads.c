#include "threads.h"

typedef struct argumentosThread
{
    int socketDescriptor;
} strarg;

#define PUERTO_DESTINO 3457
#define IP_DESTINO "127.0.0.1"
#define BUFFER_SIZE 512

int sendPathToIndexProcess(char *path); // se conecta, envia el path y devuelve el socket
int readMessage(int socketDescriptorCliente, char *mensajeHTTP);
char *substring(char *unString, int start, int end);
void processHttpMessage(char *mensajeHTTP, int sockClient);
void sendFile(int clientSocketDescriptor, char *message);

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
    char logMessage[BUFFER_SIZE];
    int salida = 0;
    
    do
    {
        salida = readMessage(threadArguments->socketDescriptor, httpMessage);
        if(salida == -1)
        {
            sprintf(logMessage, "ERROR: Cliente %d desconectado abruptamente. Cerrando thread\n", threadArguments->socketDescriptor);;;
        }
        else if (salida == 0)
        {
            sprintf(logMessage, "Cliente %d desconectado de forma normal.\n", threadArguments->socketDescriptor);
        }
        logger(logMessage);
        processHttpMessage(httpMessage, threadArguments->socketDescriptor);
    }
    while(salida > 0);  //TODO El corte debería ser el error de read_message, por ejemplo que se desconecto el cliente es un 0...
    //FD_CLR(argumentosDelThread->socketDescriptor, &readset);
    return NULL;
}

int readMessage(int clientSocketDescriptor, char *message)
{
    char buffer[BUFFER_SIZE];
    int result;
    int retorno;
    logger("funcion readMessage");
    
    do
    {
        memset(buffer, '\0', BUFFER_SIZE);
        result = read(clientSocketDescriptor, buffer, BUFFER_SIZE);
        printf("Leidos %d bytes, contenido: %s\n", result, buffer);
        strcat(message, buffer);
    }
    while (result != -1 && result == BUFFER_SIZE && errno != EINTR);
    return result;
}

void processHttpMessage(char *httpMessage, int sockClient)
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

        char *path = substring(httpMessage, 5, i - 10);
        logger(path);
        int sockIndexProcess = sendPathToIndexProcess(path);
        char *realPath = malloc(8092);
        readMessage(sockIndexProcess, realPath);
        sendFile(sockClient, realPath);
    }
}

void sendFile(int clientSocketDescriptor, char *absolutePath)
{
    char response_buffer[BUFFER_SIZE];
    int bytes_sent;
    int file_size;
    logger("abro el archivo");
    logger(absolutePath);
	FILE *file = fopen(absolutePath, "rb");
	
    if (file == NULL) {
        char *errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
        
        sprintf(response_buffer, "HTTP/1.0 404 NOT FOUND\r\n\r\n"); 
        logger(response_buffer);
        int header_len = strlen(response_buffer);
        bytes_sent = send(clientSocketDescriptor, response_buffer, header_len, 0);
    } else {
        fseek(file, 0, SEEK_END); // seek to end of file
    	file_size = ftell(file); // get current file pointer
    	printf("\r\nfile_size: [%d]\n", file_size);
    	fseek(file, 0, SEEK_SET); // seek back to beginning of file
        sprintf(response_buffer, "HTTP/1.0 200 Ok\r\nContent-type: text/plain\r\nContent-Length: %d\r\n\r\n", file_size); 
        logger(response_buffer);
        int header_len = strlen(response_buffer);
        bytes_sent = send(clientSocketDescriptor, response_buffer, header_len, 0);
    
    	int bytes_read;
    	while((bytes_read = fread(response_buffer, 1, BUFFER_SIZE, file)) > 0){
    		bytes_sent = send(clientSocketDescriptor, response_buffer, bytes_read, 0);	
    	}
    	
    	fclose(file);    
    }
}

int sendPathToIndexProcess(char *path)
{
    struct sockaddr_in server;
    int sock;
    
    // mando el path al indexProcess via Sockets
    ///@brief Creo el socket para el cliente
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Error al crear socket cliente");
        logger("Error al crear el socket cliente.");
        exit(EXIT_FAILURE);
    }

    server.sin_addr.s_addr = inet_addr(IP_DESTINO);
    server.sin_family = AF_INET;
    server.sin_port = htons(PUERTO_DESTINO);

    ///@brief Enlazo con el servidor
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("Error en la conexion");
        logger("Error en la conexion al servidor.");
        exit(EXIT_FAILURE);
    }
    
    send (sock, path, strlen(path), 0);
    
    return sock;
}

char *substring(char *unString, int start, int end) {
    char *subbuff = malloc(end - start);
    memcpy(subbuff, unString + start, end - start);
    subbuff[end - start] = '\0';
    return subbuff;
}