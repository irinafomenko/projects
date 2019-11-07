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

void have_elements_in_response(int sock)
{
    char have_elements[4] = "yes";
    int size_have_elements = sizeof(have_elements);
    send(sock, &size_have_elements, sizeof(int), 0);
    send(sock, &have_elements, size_have_elements, 0);
}

void main_server(const char *ip_addr)
{
    /*---------------------------------------------*/
    log_server.print("main_server()"); // класс Logger
    /*---------------------------------------------*/
    int size_queue;
    myDeque* myDequ = new myDeque;
    myQueue* my_command = new myQueue;
    int sock, listener;//для сервера
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

    while(1)
    {
        /*--------------------------------------*/
        //вывод сообщения о подключении клиента и отправка ответного сообщения
        //создает для общения с клиентом новый сокет
        if((sock = accept(listener, NULL, NULL)) < 0) {break;}
        //получение ip адреса клиента
        int size_ip_addr_client;
        recv(sock, &size_ip_addr_client, sizeof(int), 0);
        char ip_addr_client[size_ip_addr_client];
        recv(sock, &ip_addr_client, size_ip_addr_client, 0);
        string msg_for_logger = "New client connected! ";
        /*--------------------------------------*/
        log_server.print(msg_for_logger + ip_addr_client); // класс Logger
        /*--------------------------------------*/
        cout << "New client connected! " << ip_addr_client << endl;
        //отправка сообщения клиенту
        int size_msg = 18;
        char msg[size_msg];
        strcpy(msg,"Hello from server!");
        send(sock, &size_msg, sizeof(int), 0);
        send(sock, &msg, size_msg, 0);

        /*--------------------------------------*/
        recv(sock, &size_queue, sizeof(int), 0);

        for(int i=0; i<size_queue; i++)
        {
            int size_cmd;
            pair<string, int> el;
            recv(sock, &size_cmd, sizeof(int), 0);
            char el_first[size_cmd];
            recv(sock, &el_first, size_cmd, 0);
            recv(sock, &el.second, sizeof(int), 0);
            el.first = el_first;
            my_command->push(el);
        }

        while(my_command->size_of_queue() != 0)
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
                    have_elements_in_response(sock);
                }
                if (k.first == "pop_back")
                {
                    myDequ->pop_back();
                    have_elements_in_response(sock);
                }
                if (k.first == "begin_element")
                {
                    //cout << myDequ->begin_element() << endl;
                    int begin_el = myDequ->begin_element();
                    have_elements_in_response(sock);
                    send(sock, &begin_el, sizeof(int), 0);
                }
                if (k.first == "end_element")
                {
                    //cout << myDequ->end_element() << endl;
                    int end_el = myDequ->end_element();
                    have_elements_in_response(sock);
                    send(sock, &end_el, sizeof(int), 0);
                }
                if (k.first == "size_of_queue")
                {
                    //cout << myDequ->size_of_queue() << endl;
                    int size_of_queue = myDequ->size_of_queue();
                    have_elements_in_response(sock);
                    send(sock, &size_of_queue, sizeof(int), 0);
                }
                if (k.first == "print")
                {
                    myDequ->print();
                    have_elements_in_response(sock);
                    int size = myDequ->size_of_queue();
                    send(sock, &size, sizeof(int), 0);
                    myDeque* send_deque = new myDeque;
                    myDequ->copy_to(send_deque);
                    while(send_deque->size_of_queue() != 0)
                    {
                        int el = send_deque->begin_element();
                        send(sock, &el, sizeof(int), 0);
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
                send(sock, &size_msg, sizeof(int), 0);
                send(sock, &msg, size_msg, 0);
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
        close(sock);//закрытие сокета
        /*---------------------------------------------*/
        log_server.print("Connection closed"); // класс Logger
        /*---------------------------------------------*/
    }
    /*---------------------------------------------*/
    log_server.print("main_server() exit"); // класс Logger
    /*---------------------------------------------*/
}

