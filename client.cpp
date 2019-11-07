//
// Created by ifomenko on 24.10.2019.
//
#include "class_myqueue.h" //для очереди команд
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
    int size_queue;
    int size_msg_exception;//для проверки вывода исключения
    char msg_exception[size_msg_exception];//для проверки вывода исключения
    myQueue* deq_element = new myQueue; //для вывода элементов (дэка, первого, последнего, размера)
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
            int size_cmd = el.first.length();
            char el_first[size_cmd];
            strcpy(el_first,el.first.c_str());
            int el_second = el.second;
            send(sock, &size_cmd, sizeof(int), 0);
            send(sock, &el_first, size_cmd, 0);
            send(sock, &el_second, sizeof(el_second), 0);
            //для выводов элементов и сообщений исключений
            if(el.first == "pop") {deq_element->push(el);}
            else if(el.first == "pop_back") {deq_element->push(el);}
            else if(el.first == "begin_element") {deq_element->push(el);}
            else if(el.first == "end_element") {deq_element->push(el);}
            else if(el.first == "size_of_queue") {deq_element->push(el);}
            else if(el.first == "print") {deq_element->push(el);}
            my_command->pop();
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    //выполнение запросов
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
        recv(sock, &size_msg_exception, sizeof(int), 0);
        recv(sock, &msg_exception, size_msg_exception, 0);
        if( !strcmp(msg_exception, "yes"))
        {
            if(cmd == "begin_element")
            {
                recv(sock, &el, sizeof(int), 0);
                cout << "Begin element is " << el << endl;
            }
            if(cmd == "end_element")
            {
                recv(sock, &el, sizeof(int), 0);
                cout << "End element is " << el << endl;
            }
            if(cmd == "size_of_queue")
            {
                recv(sock, &el, sizeof(int), 0);
                cout << "Size of deque:  " << el << endl;
            }
            if(cmd == "print")
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
            }
        }
        else
        {
            cout << msg_exception << endl;
        }
        try
        {
            deq_element->pop();
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }

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
    int el;//добавление элемента в дек
    pair<string, int> change_command ("command",0);
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
                //cin >> el;
                cin >> change_command.second;
                change_command.first = "push";
                my_command->push(change_command);
                break;
            case 2:
                cout << "Enter element: ";
                //cin >> el;
                cin >> change_command.second;
                change_command.first = "push_front";
                my_command->push(change_command);
                break;
            case 3:
                change_command.first = "pop";
                my_command->push(change_command);
                break;
            case 4:
                change_command.first = "pop_back";
                my_command->push(change_command);
                break;
            case 5:
                change_command.first = "begin_element";
                my_command->push(change_command);
                break;
            case 6:
                change_command.first = "end_element";
                my_command->push(change_command);
                break;
            case 7:
                change_command.first = "size_of_queue";
                my_command->push(change_command);
                break;
            case 8:
                change_command.first = "print";
                my_command->push(change_command);
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

