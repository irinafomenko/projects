//
// Created by ifomenko on 23.10.2019.
//

#ifndef SPISOK_2_SERVER_H
#define SPISOK_2_SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

/*---------------------------------------------*/
Logger log_server("log_example.txt", "Server"); // класс Logger
/*---------------------------------------------*/

void main_server()
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
    addr.sin_port = htons(3425);//порт
    addr.sin_addr.s_addr = htonl(INADDR_ANY);//IP-адрес хоста
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)//связывание сокета с адресом
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 1);//очередь запросов на соединение

    while(1)
    {

        sock = accept(listener, NULL, NULL);//создает для общения с клиентом новый сокет
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
                if (k.first == "begin_element") { cout << myDequ->begin_element() << endl; }
                if (k.first == "end_element") { cout << myDequ->end_element() << endl; }
                if (k.first == "size_of_queue") { cout << myDequ->size_of_queue() << endl; }
                if (k.first == "print") { myDequ->print();}
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

#endif //SPISOK_2_SERVER_H
