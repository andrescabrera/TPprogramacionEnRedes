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
#include "db-api.h"

void stop_main();
void init_data (DB *dbp);

int main(int argc, char *argv[])
{
    int ret;
    ret = init_db();
    if (ret != 0){
        logger("Error with DB; terminating.");
        exit(1);
    }
 
    DB *dbp = getDBP(); 
    init_data(dbp); //agrego valores a la base de datos   
    
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
    dbp->close(dbp, 0);
    return EXIT_SUCCESS;
}

void stop_main()
{
    stop_tcp_server();
}

void init_data (DB *dbp) 
{
	// add values (DB, key, value)
	set(dbp, "ejemplo1.html", "ejemplo.andres");
	set(dbp, "image1.jpg", "/resources/ejemplo2.html");
	set(dbp, "image2.jpg", "/resources/ejem3.html");
	set(dbp, "image3.jpg", "/resources/ejem4.html");
}

void get_value_from_request_key(char *key, char *value)
{
    DB *dbp = getDBP();
	if(get(dbp, key, value) == 1){ //on error returns 1
		strcpy(value, "test ERROR");
	}
}