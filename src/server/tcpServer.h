#ifndef TCPSERVER_H_INCLUDED
#define TCPSERVER_H_INCLUDED

int start_tcp_server();
void stop_tcp_server();

int getTcpSocketServer();
int getMaxFd();

#endif // TCPSERVER_H_INCLUDED
