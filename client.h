//
// Created by ifomenko on 28.10.2019.
//
#include "client.cpp"
#ifndef SPISOK_2_CLIENT_H
#define SPISOK_2_CLIENT_H

void main_client(const char *ip_addr);
void thread_for_send_to_server(const char *ip_addr);
void send_to_server(const char *ip_addr);

#endif //SPISOK_2_CLIENT_H
