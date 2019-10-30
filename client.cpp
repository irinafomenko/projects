//
// Created by ifomenko on 24.10.2019.
//
#include <iostream>
#include "Logger.h"
#include "class_myqueue.h"
#include <functional>
#include <list>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <windows.h>
#include <thread>

using namespace std;

/*---------------------------------------------*/
myQueue* my_command = new myQueue;
bool flag_exit = FALSE;
/*---------------------------------------------*/
/*---------------------------------------------*/
Logger log_client("log_example.txt", "Client"); // класс Logger
/*---------------------------------------------*/

void send_to_server(const char *ip_addr)
{
    /*---------------------------------------------*/
    log_client.print("send_to_server()"); // класс Logger
    /*---------------------------------------------*/
    int deque_print = 0;
    int size_queue;
    myQueue* deq_element = new myQueue;
    int sock;//для клиента
    struct sockaddr_in addr;//адрес
    sock = socket(AF_INET, SOCK_STREAM, 0);//создание сокета
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;//семейство адресов
    addr.sin_port = 3425; // или любой другой порт...
    addr.sin_addr.s_addr = inet_addr(ip_addr);//IP-адресс хоста
    /*
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)//для установления соединения
    {
        perror("connect");
        exit(2);
    }
     */
    while(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        log_client.print("Can't connect!"); // класс Logger
        cout << "Can't connect!" << endl;
        cout << "Try again..." << endl;
        Sleep(5000);
    }
    log_client.print("Connected!"); // класс Logger
    /*--------------------------------------*/
    //отправка ip адресса клиента
    int size_ip_addr = sizeof(ip_addr)+1;
    char ip_addr_client[size_ip_addr];
    strcpy(ip_addr_client,ip_addr);
    send(sock, &size_ip_addr, sizeof(int), 0);
    send(sock, &ip_addr_client, size_ip_addr, 0);
    /*--------------------------------------*/
    //получение сообщения от сервера
    int size_msg;
    recv(sock, &size_msg, sizeof(int), 0);
    char msg[size_msg];
    recv(sock, &msg, size_msg, 0);
    cout << msg << endl;
    /*--------------------------------------*/
    size_queue = my_command->size_of_queue();
    send(sock, &size_queue, sizeof(size_queue), 0);
    while(my_command->size_of_queue() != 0)
    {
        pair<string,int> el;
        try
        {
            el = my_command->head();
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        int size_cmd = el.first.length();
        char el_first[size_cmd];
        strcpy(el_first,el.first.c_str());
        int el_second = el.second;
        send(sock, &size_cmd, sizeof(int), 0);
        send(sock, &el_first, size_cmd, 0);
        send(sock, &el_second, sizeof(el_second), 0);
        if(el.first == "begin_element") {deq_element->push("begin_element");}
        else if(el.first == "end_element") {deq_element->push("end_element");}
        else if(el.first == "size_of_queue") {deq_element->push("size_of_queue");}
        if(el.first == "print") {deque_print++;}
        try
        {
            my_command->pop();
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    while(deq_element->size_of_queue() != 0)
    {

            int el;
            string cmd;
            try
            {
                cmd = deq_element->head().first;
            }
            catch (std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
            recv(sock, &el, sizeof(int), 0);
            if(cmd == "begin_element") {cout << "Begin element is " << el << endl;}
            if(cmd == "end_element") {cout << "End element is " << el << endl;}
            if(cmd == "size_of_queue") {cout << "Size of deque:  " << el << endl;}
        try
        {
            deq_element->pop();
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }

    }
    while(deque_print != 0)
    {
        cout << "Deque: ";
        int size;
        recv(sock, &size, sizeof(int), 0);
        for(int i=0; i<size; i++)
        {
            int el;
            recv(sock, &el, sizeof(int), 0);
            cout << el << " ";
        }
        cout << endl;
        deque_print--;
    }
    close(sock);//закрытие сокета
    /*---------------------------------------------*/
    log_client.print("Connection closed"); // класс Logger
    /*---------------------------------------------*/
}

void thread_for_send_to_server(const char *ip_addr)
{
    while(1)
    {
        Sleep(5000);
        send_to_server(ip_addr);
        if(flag_exit == TRUE) {break;}
    }
}

void main_client(const char *ip_addr)
{
    /*---------------------------------------------*/
    log_client.print("main_client()"); // класс Logger
    /*---------------------------------------------*/
    /*---------------------------------------------*/
    thread thread_for_server(thread_for_send_to_server, ip_addr);
    /*---------------------------------------------*/
    int change = 1;
    int el;
    while((change >= 1) && (change < 9))
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
        cout << "9 - Quit" << endl;
        //mut.lock();
        cin >> change;
        //mut.unlock();

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
            default:
                flag_exit = TRUE;
                break;
        }

    }
    thread_for_server.join();
    /*---------------------------------------------*/
    log_client.print("main_client() exit"); // класс Logger
    /*---------------------------------------------*/
}

