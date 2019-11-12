//
// Created by ifomenko on 23.10.2019.
//
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "Logger.h"
#include "class_deque.h"

using namespace std;

/*---------------------------------------------*/
Logger log_server("log_example.txt", "Server"); // класс Logger
/*---------------------------------------------*/
int sock_server, listener;
myQueue* my_command = new myQueue;
myDeque* myDequ = new myDeque;

void have_elements_in_response(int sock_server)
{
    log_server.print("have_elements_in_respons()"); // класс Logger
    char have_elements[4] = "yes";
    int size_have_elements = sizeof(have_elements);
    send(sock_server, &size_have_elements, sizeof(int), 0);
    send(sock_server, &have_elements, size_have_elements, 0);
    log_server.print("Exit have_elements_in_respons()"); // класс Logger
}

void setting_connect(const char *ip_addr)
{
    log_server.print("setting_connect()"); // класс Logger
    struct sockaddr_in addr;//адрес
    listener = socket(AF_INET, SOCK_STREAM, 0);//создание сокета
    if(listener < 0)
    {
        perror("socket");
        log_server.print("error socket"); // класс Logger
        exit(1);
    }

    addr.sin_family = AF_INET;//семейство адресов
    addr.sin_port = 3425; // htons(3425);//порт
    addr.sin_addr.s_addr = inet_addr(ip_addr);// htonl(INADDR_ANY);//IP-адрес хоста
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)//связывание сокета с адресом
    {
        perror("bind");
        log_server.print("error bind"); // класс Logger
        exit(2);
    }

    listen(listener, 1);//очередь запросов на соединение
    log_server.print("Exit setting_connect()"); // класс Logger
}

void client_connection()
{
    log_server.print("client_connection()"); // класс Logger
    //вывод сообщения о подключении клиента и отправка ответного сообщения
    //получение ip адреса клиента
    int size_ip_addr_client;
    recv(sock_server, &size_ip_addr_client, sizeof(int), 0);
    char ip_addr_client[size_ip_addr_client];
    recv(sock_server, &ip_addr_client, size_ip_addr_client, 0);
    string msg_for_logger = "New client connected! ";
    /*--------------------------------------*/
    log_server.print(msg_for_logger + ip_addr_client); // класс Logger
    /*--------------------------------------*/
    cout << "New client connected! " << ip_addr_client << endl;
    //отправка сообщения клиенту
    int size_msg = 18;
    char msg[size_msg];
    strcpy(msg,"Hello from server!");
    send(sock_server, &size_msg, sizeof(int), 0);
    send(sock_server, &msg, size_msg, 0);
    log_server.print("Exit client_connection()"); // класс Logger
}

void receiving_commands()
{
    log_server.print("receiving_commands()"); // класс Logger
    int size_queue;
    recv(sock_server, &size_queue, sizeof(int), 0);

    for(int i=0; i<size_queue; i++)
    {
        int size_cmd;
        pair<string, int> el;
        recv(sock_server, &size_cmd, sizeof(int), 0);
        char el_first[size_cmd];
        recv(sock_server, &el_first, size_cmd, 0);
        recv(sock_server, &el.second, sizeof(int), 0);
        el.first = el_first;
        my_command->push(el);
    }
    log_server.print("Commands received"); // класс Logger
    log_server.print("Exit receiving_commands()"); // класс Logger
}

void commands_execute()
{
    log_server.print("commands_execute()"); // класс Logger
    while(my_command->get_size() != 0)
    {
        try
        {
            pair<std::string, int> k = my_command->head();
            cout << k.first << endl;// чтобы знать какая команда выполняется
            if (k.first == "push") { myDequ->push(k.second); }
            if (k.first == "push_front") { myDequ->push_front(k.second); }
            if (k.first == "pop")
            {
                myDequ->pop();
                have_elements_in_response(sock_server);
            }
            if (k.first == "pop_back")
            {
                myDequ->pop_back();
                have_elements_in_response(sock_server);
            }
            if (k.first == "begin_element")
            {
                //cout << myDequ->begin_element() << endl;
                int begin_el = myDequ->begin_element();
                have_elements_in_response(sock_server);
                send(sock_server, &begin_el, sizeof(int), 0);
            }
            if (k.first == "end_element")
            {
                //cout << myDequ->end_element() << endl;
                int end_el = myDequ->end_element();
                have_elements_in_response(sock_server);
                send(sock_server, &end_el, sizeof(int), 0);
            }
            if (k.first == "get_size")
            {
                //cout << myDequ->size_of_queue() << endl;
                int size_of_deque = myDequ->get_size();
                have_elements_in_response(sock_server);
                send(sock_server, &size_of_deque, sizeof(int), 0);
            }
            if (k.first == "print")
            {
                myDequ->print();
                have_elements_in_response(sock_server);
                int size = myDequ->get_size();
                send(sock_server, &size, sizeof(int), 0);
                myDeque* send_deque = new myDeque;
                myDequ->copy_to(send_deque);
                while(send_deque->get_size() != 0)
                {
                    int el = send_deque->begin_element();
                    send(sock_server, &el, sizeof(int), 0);
                    send_deque->pop();
                }
            }
        }
        catch (std::exception& e)
        {
            //std::cout << e.what() << std::endl;
            string msg_str = e.what();
            //const char *msg_str = e.what();
            int size_msg = msg_str.length();
            char msg[size_msg];
            strcpy(msg,msg_str.c_str());
            send(sock_server, &size_msg, sizeof(int), 0);
            send(sock_server, &msg, size_msg, 0);
        }
        try
        {
            my_command->pop();// чтобы очередь команд каждый раз не повторялась
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    log_server.print("Commands executed"); // класс Logger
    log_server.print("Exit commands_execute()"); // класс Logger
}

void main_server(const char *ip_addr)
{
    /*---------------------------------------------*/
    log_server.print("main_server()"); // класс Logger
    /*---------------------------------------------*/
    setting_connect(ip_addr);

    while(1)
    {
        if((sock_server = accept(listener, NULL, NULL)) < 0) {break;}
        /*--------------------------------------*/
        client_connection();
        /*--------------------------------------*/
        receiving_commands();
        /*--------------------------------------*/
        commands_execute();
        /*--------------------------------------*/
        close(sock_server);//закрытие сокета
        /*---------------------------------------------*/
        log_server.print("Connection closed"); // класс Logger
        /*---------------------------------------------*/
    }
    /*---------------------------------------------*/
    log_server.print("Exit main_server()"); // класс Logger
    /*---------------------------------------------*/
}

