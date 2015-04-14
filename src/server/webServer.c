#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

/// sockets =>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/un.h>

/// select =>
#include <sys/time.h>
#include <sys/select.h>

/// threads =>
#include <pthread.h>

/// componentes =>
#include "logger.h"
#include "menu.h"

/// constantes =>
#define PORT 3456

int cantidadDeClientesConectados = 0;
int cantidadDeArchivosTransferidos = 0;

int main(int argc, char *argv[])
{
    pthread_t v_thread_menu_servidor;
    pthread_create (&v_thread_menu_servidor, NULL, menu_servidor, NULL);

    if (start_tcp_server())
    {
        logger("Server started successfully");
    }
    else
    {
        stop_main();
        return EXIT_FAILURE;
    }

    listen_and_accept_new_clients();

    stop_main();
    cerrarLogger();
    return EXIT_SUCCESS;
}