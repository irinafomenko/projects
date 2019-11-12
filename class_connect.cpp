//
// Created by ifomenko on 12.11.2019.
//
#include "class_connect.h"

const char* Connect::name_class = "Connect";
Logger log_connect("log_example.txt", Connect::name_class); // класс Logger

int Connect::connect_for_client(const char *ip_addr)
{
    log_connect.print("connect_for_client()"); // класс Logger
    sock = socket(AF_INET, SOCK_STREAM, 0);//создание сокета
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;//семейство адресов
    addr.sin_port = 3425; // или любой другой порт...
    addr.sin_addr.s_addr = inet_addr(ip_addr);//IP-адресс хоста

    while(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        log_connect.print("Client can't connect!"); // класс Logger
        std::cout << "Can't connect!" << std::endl;
        std::cout << "Try again..." << std::endl;
        Sleep(5000);
    }
    log_connect.print("Exit connect_for_client()"); // класс Logger
    return sock;
}

int Connect::connect_for_server(const char *ip_addr)
{
    log_connect.print("connect_for_server()"); // класс Logger
    struct sockaddr_in addr;//адрес
    listener = socket(AF_INET, SOCK_STREAM, 0);//создание сокета
    if(listener < 0)
    {
        perror("socket");
        log_connect.print("error socket"); // класс Logger
        exit(1);
    }

    addr.sin_family = AF_INET;//семейство адресов
    addr.sin_port = 3425; // htons(3425);//порт
    addr.sin_addr.s_addr = inet_addr(ip_addr);// htonl(INADDR_ANY);//IP-адрес хоста
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)//связывание сокета с адресом
    {
        perror("bind");
        log_connect.print("error bind"); // класс Logger
        exit(2);
    }

    listen(listener, 1);//очередь запросов на соединение
    log_connect.print("Exit connect_for_server()"); // класс Logger
}

int Connect::connect_server_with_client()
{
    log_connect.print("connect_server_with_client()"); // класс Logger
    log_connect.print("Exit connect_server_with_client()"); // класс Logger
    return accept(listener, NULL, NULL);
}

void Connect::close_socket(int sock)
{
    log_connect.print("close_socket()"); // класс Logger
    close(sock);
    log_connect.print("Connection closed"); // класс Logger
    log_connect.print("Exit close_socket()"); // класс Logger
}