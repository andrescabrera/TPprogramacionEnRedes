/**
    @brief Acepta un nuevo cliente para el socket especificado por parametro.
    @param socket descriptor de cualquier tipo de socket.
*/
int accept_new_clients(int socket)
{
    logger("New client in queue");
    struct sockaddr_in addr;
    int len = sizeof(addr);
    int result = accept(socket, (struct sockaddr *)&addr, (socklen_t*)&len);
    if (result == -1)
        // These are not errors according to the manpage.
        if (!(errno == ENETDOWN || errno == EPROTO || errno == ENOPROTOOPT || errno == EHOSTDOWN || errno == ENONET || errno == EHOSTUNREACH || errno == EOPNOTSUPP || errno == ENETUNREACH))
            perror("accept error");
    cantidadDeClientesConectados++;
    FD_SET(result, &readset);
    FD_SET(result, &tempset); //Agregado los clientes al tempset tambien para que los vea en el for
    maxfd = (maxfd < result) ? result : maxfd;
    FD_CLR(socket, &tempset);
    return result;
}

void listen_and_accept_new_clients()
{
    int j, result;
    struct timeval tv;

    FD_ZERO(&readset);
    FD_SET(tcp_socket_server, &readset);
    FD_SET(udp_socket_server, &readset);
    FD_SET(unix_socket_server, &readset);

    do
    {
//        menuGUI();
        //mostrarListadoClientesConectados(); //testing
        //memcpy(&tempset, &readset, sizeof(tempset));

        FD_SET(tcp_socket_server, &tempset);
        FD_SET(udp_socket_server, &tempset); //Vuelvo agregar los servidores para ver si hay nuevos clientes que aceptar
        FD_SET(unix_socket_server, &tempset);

        tv.tv_sec = 30;
        tv.tv_usec = 0;
        result = select(maxfd + 1, &tempset, NULL, NULL, &tv);

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
            if (FD_ISSET(udp_socket_server, &tempset))
            {
                //lanzarThreadUDP(udp_socket_server);
            }

            if (FD_ISSET(tcp_socket_server, &tempset))
            {
                int socketClienteAceptado = accept_new_clients(tcp_socket_server);
                printf("Cliente Nuevo\n");
            }

            if (FD_ISSET(unix_socket_server, &tempset))
            {
                //lanzarThread(unix_socket_server);
            }
//            printf("\t\tBuscando clientes en el tempset\n\n");
            for (j=0; j<maxfd+1; j++)
            {
//                printf("%d |", j);
                if (FD_ISSET(j, &tempset)) //En este momento estan solo los clientes. Los servidores los elimine en accept
                {
                    lanzarThread(j);
                    FD_CLR(j, &tempset); //Elimino el cliente que acabo de atender.
                }      // end if (FD_ISSET(j, &tempset))
            }      // end for (j=0;...)
//            printf("\n");
        }
        // end else if (result > 0)
    }
    while (1);

}