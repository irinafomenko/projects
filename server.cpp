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

void main_server(const char *ip_addr)
{
    /*---------------------------------------------*/
    log_server.print("main_server()"); // класс Logger
    /*---------------------------------------------*/
    int size_queue;
    int bytes_size_queue;
    myDeque* myDequ = new myDeque;
    myQueue* my_command = new myQueue;
    int sock, listener;//для сервера
    struct sockaddr_in addr;//адрес
    listener = socket(AF_INET, SOCK_STREAM, 0);//создание сокета
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;//семейство адресов
    addr.sin_port = 3425; // htons(3425);//порт
    addr.sin_addr.s_addr = inet_addr(ip_addr);// htonl(INADDR_ANY);//IP-адрес хоста
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)//связывание сокета с адресом
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 1);//очередь запросов на соединение

    while(1)
    {
        /*--------------------------------------*/
        //вывод сообщения о подключении клиента и отправка ответного сообщения
        if((sock = accept(listener, NULL, NULL)) >= 0);//создает для общения с клиентом новый сокет
        {
            cout << "New client connected!" << endl;
            int size_msg = 18;
            char msg[size_msg];
            strcpy(msg,"Hello from server!");
            send(sock, &size_msg, sizeof(int), 0);
            send(sock, &msg, size_msg, 0);
        }
        /*--------------------------------------*/
        bytes_size_queue = recv(sock, &size_queue, sizeof(int), 0);
        if(bytes_size_queue <= 0) {break;}

        for(int i=0; i<size_queue; i++)
        {
            int el_second;
            int size_cmd;
            recv(sock, &size_cmd, sizeof(int), 0);
            char el_first[size_cmd];
            recv(sock, &el_first, size_cmd, 0);
            recv(sock, &el_second, sizeof(int), 0);
            my_command->push(el_first, el_second);
        }


        while(my_command->size_of_queue() != 0)
        {
            try
            {
                pair<std::string, int> k = my_command->head();
                cout << k.first << endl;// чтобы знать какая команда выполняется
                if (k.first == "push") { myDequ->push(k.second); }
                if (k.first == "push_front") { myDequ->push_front(k.second); }
                if (k.first == "pop") { myDequ->pop(); }
                if (k.first == "pop_back") { myDequ->pop_back(); }
                if (k.first == "begin_element")
                {
                    //cout << myDequ->begin_element() << endl;
                    int begin_el = myDequ->begin_element();
                    send(sock, &begin_el, sizeof(int), 0);
                }
                if (k.first == "end_element")
                {
                    //cout << myDequ->end_element() << endl;
                    int end_el = myDequ->end_element();
                    send(sock, &end_el, sizeof(int), 0);
                }
                if (k.first == "size_of_queue")
                {
                    //cout << myDequ->size_of_queue() << endl;
                    int size_of_queue = myDequ->size_of_queue();
                    send(sock, &size_of_queue, sizeof(int), 0);
                }
                if (k.first == "print")
                {
                    //myDequ->print();
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
                std::cout << e.what() << std::endl;
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
    }
    /*---------------------------------------------*/
    log_server.print("main_server() exit"); // класс Logger
    /*---------------------------------------------*/
}

