//
// Created by ifomenko on 12.11.2019.
//

#ifndef SPISOK_2_CLASS_CONNECT_H
#define SPISOK_2_CLASS_CONNECT_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <windows.h>
#include <thread>
#include <iostream>
#include "Logger.h"

class Connect
{
private:
    struct sockaddr_in addr;//адрес
    int sock;//для клиента
    int listener;
public:
    static const char* name_class;
    int connect_for_client(const char *ip_addr);
    int connect_for_server(const char *ip_addr);
    int connect_server_with_client();
    void close_socket(int sock);
};

#endif //SPISOK_2_CLASS_CONNECT_H
