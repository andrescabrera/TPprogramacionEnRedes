#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

/// select =>
#include <sys/time.h>
#include <sys/select.h>

/// threads =>
#include <pthread.h>

/// componentes =>
#include "logger.h"
#include "menu.h"
#include "tcpServer.h"
#include "connectionHandler.h"

/// constantes =>
#define PORT 3456

void stop_main();

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

void stop_main()
{
    stop_tcp_server();
}