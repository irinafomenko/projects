//
// Created by ifomenko on 28.10.2019.
//
#include "client.cpp"
#ifndef SPISOK_2_CLIENT_H
#define SPISOK_2_CLIENT_H

void main_client(const char *ip_addr);
void menu();
void thread_for_dialog_with_server(const char *ip_addr);
void query_execution();
void send_to_server();
void messages_with_server(const char *ip_addr);

#endif //SPISOK_2_CLIENT_H
