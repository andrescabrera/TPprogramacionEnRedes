/// select =>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/socket.h>

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "tcpServer.h"

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/un.h>

fd_set readset, tempset;

int cantidadDeClientesConectados = 0;
int cantidadDeArchivosTransferidos = 0;

int mMaxFd;

/**
    @brief Acepta un nuevo cliente para el socket especificado por parametro.
    @param socket descriptor de cualquier tipo de socket.
*/
int accept_new_clients(int socket)
{
    logger("Nuevo cliente en cola");
    struct sockaddr_in addr;
    int len = sizeof(addr);
    int result = accept(socket, (struct sockaddr *)&addr, (socklen_t*)&len);
    if (result == -1)
        // These are not errors according to the manpage.
        if (!(errno == ENETDOWN || errno == EPROTO || errno == ENOPROTOOPT || errno == EHOSTDOWN || errno == ENONET || errno == EHOSTUNREACH || errno == EOPNOTSUPP || errno == ENETUNREACH))
            perror("accept error");
    cantidadDeClientesConectados++;
    FD_SET(result, &readset);
    FD_SET(result, &tempset);
    mMaxFd = (mMaxFd < result) ? result : mMaxFd;
    FD_CLR(socket, &tempset);
    return result;
}

void listen_and_accept_new_clients()
{
    int tcp_socket_server = getTcpSocketServer();
    mMaxFd = getMaxFd();
    
    int j, result;
    struct timeval tv;

    FD_ZERO(&readset);
    FD_SET(tcp_socket_server, &readset);

    do
    {
        //memcpy(&tempset, &readset, sizeof(tempset));
        FD_SET(tcp_socket_server, &tempset);

        tv.tv_sec = 30;
        tv.tv_usec = 0;
        result = select(mMaxFd + 1, &tempset, NULL, NULL, &tv);
        printf("maxFd = %d", mMaxFd);
        if (result == 0)
        {
            logger("select() timed out!\n");
        }
        else if (result < 0 && errno != EINTR)
        {
            perror("select()");
        }
        else if (result > 0)
        {
            if (FD_ISSET(tcp_socket_server, &tempset))
            {
                int socketClienteAceptado = accept_new_clients(tcp_socket_server);
                printf("Cliente Nuevo\n");
            }

            for (j=0; j<mMaxFd+1; j++)
            {
                if (FD_ISSET(j, &tempset))
                {
                    lanzarThread(j);
                    FD_CLR(j, &tempset);
                }      
            }
        }
    }
    while (1);

}