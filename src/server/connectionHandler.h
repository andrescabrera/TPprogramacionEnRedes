#ifndef CONNECTIONHANDLER_H_INCLUDED
#define CONNECTIONHANDLER_H_INCLUDED


#include "threads.h"

int accept_new_clients(int socket);
void listen_and_accept_new_clients();

#endif // CONNECTIONHANDLER_H_INCLUDED