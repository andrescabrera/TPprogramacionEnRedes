/// sockets =>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/un.h>

#define PORT 3456

typedef struct argumentosThread
{
    int socketDescriptor;
} strarg;

int tcp_socket_server, udp_socket_server, unix_socket_server, maxfd; ///< Descriptores tanto para TCP, UDP y Unix.

///@brief Crea el socket, Configura las opciones, enlaza el puerto a la interface y pone el socket a la escucha de conexiones entrantes.
int start_tcp_server()
{
    logger("starting TCP server");
    // Create the server-side socket
    tcp_socket_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (tcp_socket_server < 0)
    {
        perror("TCP socket");
        return 0;
    }
    maxfd = tcp_socket_server;

    int flag = 1;
    int result = setsockopt( tcp_socket_server, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(int) );
    if (result < 0)
    {
        perror("TCP setsockopt(TCP_NODELAY)");
        return 0;
    }

    result = setsockopt( tcp_socket_server, SOL_SOCKET, SO_REUSEADDR, (char *)&flag, sizeof(int) );
    if (result < 0)
    {
        perror("TCP setsockopt(SO_REUSEADDR)");
        return 0;
    }

    result = setsockopt( tcp_socket_server, SOL_SOCKET, SO_KEEPALIVE, (char *)&flag, sizeof(int) );
    if (result < 0)
    {
        perror("TCP setsockopt(SO_KEEPALIVE)");
        return 0;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to the appropriate port and interface (INADDR_ANY)
    if ( bind( tcp_socket_server, (struct sockaddr *)&address, sizeof(address) ) < 0 )
    {
        perror("TCP bind");
        return 0;
    }

    // Listen for incoming connection(s)
    if ( listen( tcp_socket_server, 1 ) < 0 )
    {
        perror("TCP listen");
        return 0;
    }

    logger("TCP server started");
    return 1;
}


///@brief Libera los recursos del socket
void stop_tcp_server()
{
    close(tcp_socket_server);
    logger("TCP server stopped");
}