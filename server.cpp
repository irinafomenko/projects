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
#include "enum_commands.h"
#include "class_connect.h"

using namespace std;

/*---------------------------------------------*/
Logger log_server("log_example.txt", "Server"); // класс Logger
/*---------------------------------------------*/
int sock_server;
myQueue* my_command = new myQueue;
myDeque* myDequ = new myDeque;
Connect cnct_server; //объект класса Connect

void have_elements_in_response(int sock_server)
{
    log_server.print("have_elements_in_respons()"); // класс Logger
    char have_elements[4] = "yes";
    int size_have_elements = sizeof(have_elements);
    send(sock_server, &size_have_elements, sizeof(int), 0);
    send(sock_server, &have_elements, size_have_elements, 0);
    log_server.print("Exit have_elements_in_respons()"); // класс Logger
}

void connection_messages()
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
    myCmd enum_cmd;
    int begin_el;
    int end_el;
    int size_of_deque;
    int size;
    myDeque* send_deque = new myDeque;
    while(my_command->get_size() != 0)
    {
        try
        {
            pair<std::string, int> k = my_command->head();
            cout << k.first << endl;// чтобы знать какая команда выполняется
            enum_cmd = str_to_enum(k.first);
            switch(enum_cmd)
            {
                case PUSH:
                    myDequ->push(k.second);
                    break;
                case PUSH_FRONT:
                    myDequ->push_front(k.second);
                    break;
                case POP:
                    myDequ->pop();
                    have_elements_in_response(sock_server);
                    break;
                case POP_BACK:
                    myDequ->pop_back();
                    have_elements_in_response(sock_server);
                    break;
                case BEGIN_ELEMENT:
                    begin_el = myDequ->begin_element();
                    have_elements_in_response(sock_server);
                    send(sock_server, &begin_el, sizeof(int), 0);
                    break;
                case END_ELEMENT:
                    end_el = myDequ->end_element();
                    have_elements_in_response(sock_server);
                    send(sock_server, &end_el, sizeof(int), 0);
                    break;
                case GET_SIZE:
                    size_of_deque = myDequ->get_size();
                    have_elements_in_response(sock_server);
                    send(sock_server, &size_of_deque, sizeof(int), 0);
                    break;
                case PRINT:
                    myDequ->print();
                    have_elements_in_response(sock_server);
                    size = myDequ->get_size();
                    send(sock_server, &size, sizeof(int), 0);
                    myDequ->copy_to(send_deque);
                    while(send_deque->get_size() != 0)
                    {
                        int el = send_deque->begin_element();
                        send(sock_server, &el, sizeof(int), 0);
                        send_deque->pop();
                    }
                    break;
                default:
                    break;
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
    cnct_server.connect_for_server(ip_addr);

    while(1)
    {
        if((sock_server = cnct_server.connect_server_with_client()) < 0) {break;}
        /*--------------------------------------*/
        connection_messages();
        /*--------------------------------------*/
        receiving_commands();
        /*--------------------------------------*/
        commands_execute();
        /*--------------------------------------*/
        cnct_server.close_socket(sock_server);
    }
    /*---------------------------------------------*/
    log_server.print("Exit main_server()"); // класс Logger
    /*---------------------------------------------*/
}

