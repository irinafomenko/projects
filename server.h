//
// Created by ifomenko on 28.10.2019.
//
#include "server.cpp"
#ifndef SPISOK_2_SERVER_H
#define SPISOK_2_SERVER_H

void have_elements_in_response(int sock);
void main_server(const char *ip_addr);
void commands_execute();
void receiving_commands();
void connection_messages();

#endif //SPISOK_2_SERVER_H
