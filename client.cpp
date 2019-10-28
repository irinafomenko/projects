//
// Created by ifomenko on 24.10.2019.
//
#include <iostream>
#include "Logger.h"
#include "class_deque.h"
#include "server.h"
#include <functional>
#include <thread>
#include <mutex>
#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#ifndef SPISOK_2_CLIENT_H
#define SPISOK_2_CLIENT_H

/*---------------------------------------------*/
myQueue* my_command = new myQueue;
/*---------------------------------------------*/
/*---------------------------------------------*/
Logger log_client("log_example.txt", "Client"); // класс Logger
/*---------------------------------------------*/

void send_to_server()
{
    /*---------------------------------------------*/
    log_client.print("send_to_server()"); // класс Logger
    /*---------------------------------------------*/
    int size_queue;
    int sock;//для клиента
    struct sockaddr_in addr;//адрес
    sock = socket(AF_INET, SOCK_STREAM, 0);//создание сокета
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;//семейство адресов
    addr.sin_port = htons(3425); // или любой другой порт...
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);//IP-адресс хоста
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)//для установления соединения
    {
        perror("connect");
        exit(2);
    }
    size_queue = my_command->size_of_queue();
    //send(sock, &change, sizeof(change), 0);
    send(sock, &size_queue, sizeof(size_queue), 0);
    while(my_command->size_of_queue() != 0)
    {
        pair<string,int> el = my_command->head();
        int size_cmd = el.first.length();
        char el_first[size_cmd];
        strcpy(el_first,el.first.c_str());
        int el_second = el.second;
        send(sock, &size_cmd, sizeof(int), 0);
        send(sock, &el_first, size_cmd, 0);
        send(sock, &el_second, sizeof(el_second), 0);
        my_command->pop();
    }
    close(sock);//закрытие сокета
    /*---------------------------------------------*/
    log_client.print("send_to_server() exit"); // класс Logger
    /*---------------------------------------------*/
}

void main_client()
{
    /*---------------------------------------------*/
    log_client.print("main_client()"); // класс Logger
    /*---------------------------------------------*/
    int change = 1;
    /*
    sock = socket(AF_INET, SOCK_STREAM, 0);//создание сокета
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;//семейство адресов
    addr.sin_port = htons(3425); // или любой другой порт...
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);//IP-адресс хоста
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)//для установления соединения
    {
        perror("connect");
        exit(2);
    }
    */


    int el;
    while((change >= 1) && (change < 10))
    {
        //mut.lock();//чтобы второй поток ничего не выводил пока не выбрана команда
        cout << "1 - Add element to back" << endl;
        cout << "2 - Add element to front" << endl;
        cout << "3 - Delete first element" << endl;
        cout << "4 - Delete last element" << endl;
        cout << "5 - Print first element" << endl;
        cout << "6 - Print last element" << endl;
        cout << "7 - Print size" << endl;
        cout << "8 - Print deque" << endl;
        cout << "9 - Send to server" << endl;
        cout << "10 - Quit" << endl;
        //mut.lock();
        cin >> change;
        //mut.unlock();

        //try
        //{
        switch (change) {
            case 1:
                cout << "Enter element: ";
                cin >> el;
                my_command->push("push", el);
                break;
            case 2:
                cout << "Enter element: ";
                cin >> el;
                my_command->push("push_front", el);
                break;
            case 3:
                my_command->push( "pop");
                break;
            case 4:
                my_command->push( "pop_back");
                break;
            case 5:
                my_command->push( "begin_element");
                break;
            case 6:
                my_command->push( "end_element");
                break;
            case 7:
                my_command->push( "size_of_queue");
                break;
            case 8:
                my_command->push( "print");
                break;
            case 9:
                send_to_server();
                break;
            case 10:
                break;
            default:
                break;
        }
        //}
        //catch (std::exception& e)
        //{
        //    std::cout << e.what() << std::endl;
        //}

    }
    //close(sock);//закрытие сокета
    /*---------------------------------------------*/
    log_client.print("main_client() exit"); // класс Logger
    /*---------------------------------------------*/
}

#endif //SPISOK_2_CLIENT_H
