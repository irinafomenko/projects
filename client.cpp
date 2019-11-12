//
// Created by ifomenko on 24.10.2019.
//
#include "class_myqueue.h" //для очереди команд
#include <list>
#include <sys/socket.h>
#include <windows.h>
#include <thread>
#include "enum_commands.h"
#include "class_connect.h"

using namespace std;

/*---------------------------------------------*/
myQueue* my_commands = new myQueue;
bool flag_exit = FALSE;
int sock;//для клиента
myQueue* deq_element = new myQueue; //для вывода элементов (дэка, первого, последнего, размера)
myCmd enum_cmd;
Connect cnct_client; //объект класса Connect
/*---------------------------------------------*/
/*---------------------------------------------*/
Logger log_client("log_example.txt", "Client"); // класс Logger
/*---------------------------------------------*/

void messages_with_server(const char *ip_addr)
{
    log_client.print("server_connection()"); // класс Logger
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

    log_client.print("Exit server_connection()"); // класс Logger
}

void send_to_server()
{
    log_client.print("send_to_server()"); // класс Logger
    int size_queue;
    size_queue = my_commands->get_size();
    send(sock, &size_queue, sizeof(size_queue), 0);
    while(my_commands->get_size() != 0)
    {
        pair<string,int> el;
        try
        {
            el = my_commands->head();
            int size_cmd = el.first.length();
            char el_first[size_cmd];
            strcpy(el_first,el.first.c_str());
            int el_second = el.second;
            send(sock, &size_cmd, sizeof(int), 0);
            send(sock, &el_first, size_cmd, 0);
            send(sock, &el_second, sizeof(el_second), 0);
            //для выводов элементов и сообщений исключений
            enum_cmd = str_to_enum(el.first);
            switch(enum_cmd)
            {
                case POP:
                    deq_element->push(el);
                    break;
                case POP_BACK:
                    deq_element->push(el);
                    break;
                case BEGIN_ELEMENT:
                    deq_element->push(el);
                    break;
                case END_ELEMENT:
                    deq_element->push(el);
                    break;
                case GET_SIZE:
                    deq_element->push(el);
                    break;
                case PRINT:
                    deq_element->push(el);
                    break;
                default:
                    break;
            }
            my_commands->pop();
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    log_client.print("Commands sent"); // класс Logger
    log_client.print("Exit server_connection()"); // класс Logger
}

void query_execution()
{
    log_client.print("query_execution()"); // класс Logger
    //выполнение запросов
    while(deq_element->get_size() != 0)
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
        int size_msg_exception;//для проверки вывода исключения
        recv(sock, &size_msg_exception, sizeof(int), 0);
        char msg_exception[size_msg_exception];//для проверки вывода исключения
        recv(sock, &msg_exception, size_msg_exception, 0);
        if( !strcmp(msg_exception, "yes"))
        {
            enum_cmd = str_to_enum(cmd);
            switch(enum_cmd)
            {
                case BEGIN_ELEMENT:
                    recv(sock, &el, sizeof(int), 0);
                    cout << "Begin element is " << el << endl;
                    break;
                case END_ELEMENT:
                    recv(sock, &el, sizeof(int), 0);
                    cout << "End element is " << el << endl;
                    break;
                case GET_SIZE:
                    recv(sock, &el, sizeof(int), 0);
                    cout << "Size of deque:  " << el << endl;
                    break;
                case PRINT:
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
                    break;
                default:
                    break;
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
    log_client.print("Commands executed"); // класс Logger
    log_client.print("Exit query_execution()"); // класс Logger
}

void thread_for_dialog_with_server(const char *ip_addr)
{
    log_client.print("thread_for_dialog_with_server()"); // класс Logger
    while(1)
    {
        Sleep(5000);
        /*---------------------------------------------*/
        sock = cnct_client.connect_for_client(ip_addr);
        log_client.print("Connected!"); // класс Logger
        messages_with_server(ip_addr);
        /*--------------------------------------*/
        send_to_server();
        /*--------------------------------------*/
        query_execution();
        /*--------------------------------------*/
        cnct_client.close_socket(sock);
        /*---------------------------------------------*/
        log_client.print("Connection closed"); // класс Logger
        /*---------------------------------------------*/
        if(flag_exit == TRUE) {break;}
    }
    log_client.print("Exit thread_for_dialog_with_server()"); // класс Logger
}

void menu()
{
    log_client.print("Menu()"); // класс Logger
    int change = 1;
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
                my_commands->push(change_command);
                break;
            case 2:
                cout << "Enter element: ";
                //cin >> el;
                cin >> change_command.second;
                change_command.first = "push_front";
                my_commands->push(change_command);
                break;
            case 3:
                change_command.first = "pop";
                my_commands->push(change_command);
                break;
            case 4:
                change_command.first = "pop_back";
                my_commands->push(change_command);
                break;
            case 5:
                change_command.first = "begin_element";
                my_commands->push(change_command);
                break;
            case 6:
                change_command.first = "end_element";
                my_commands->push(change_command);
                break;
            case 7:
                change_command.first = "get_size";
                my_commands->push(change_command);
                break;
            case 8:
                change_command.first = "print";
                my_commands->push(change_command);
                break;
            default:
                flag_exit = TRUE;
                break;
        }

    }
    log_client.print("Exit menu()"); // класс Logger
}

void main_client(const char *ip_addr)
{
    /*---------------------------------------------*/
    log_client.print("main_client()"); // класс Logger
    /*---------------------------------------------*/
    /*---------------------------------------------*/
    thread thread_for_server(thread_for_dialog_with_server, ip_addr);
    /*---------------------------------------------*/
    menu();
    /*---------------------------------------------*/
    thread_for_server.join();
    /*---------------------------------------------*/
    log_client.print("Exit main_client()"); // класс Logger
    /*---------------------------------------------*/
}

