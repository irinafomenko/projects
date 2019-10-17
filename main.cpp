#include <iostream>
#include "Logger.h"
#include "class_deque.h"
#include <functional>
#include <thread>
#include <mutex>
#include <list>
//#include "queue_menu.h"

using namespace std;

/*---------------------------------------------*/
myDeque* myDequ = new myDeque;
myQueue* my_command = new myQueue;
mutex mut;
/*---------------------------------------------*/
/*---------------------------------------------*/
Logger log("log_example.txt"); // класс Logger
/*---------------------------------------------*/

int xtime = 10;
int change = 1;
void func_for_thread()
{
    cout << "thread" << endl;
    while(change != 9)
    {
        this_thread::sleep_for(std::chrono::seconds(xtime));

        mut.lock();
        for(int i = 0; i <= my_command->size_of_queue(); i++)
        {
            pair<std::string, int> k = my_command->head();
            cout << k.first << endl;// чтобы знать какая команда выполняется
            if (k.first == "push")
            {
                myDequ->push(k.second);
            }
            if (k.first == "push_front")
            {
                myDequ->push_front(k.second);
            }
            if (k.first == "pop") { myDequ->pop(); }
            if (k.first == "pop_back") { myDequ->pop_back(); }
            if (k.first == "head_element") { cout << myDequ->begin_element() << endl; }
            if (k.first == "end_element") { cout << myDequ->end_element() << endl; }
            if (k.first == "size_of_queue") { cout << myDequ->size_of_queue() << endl; }
            if (k.first == "print") { myDequ->print();}

            my_command->pop();// чтобы очередь команд каждый раз не повторялась
        }
        mut.unlock();
        //my_command->pop();
        /*---------------------------------------------*/
        log.print("It's thread 2! | Выполнил команды!"); // класс Logger
        /*---------------------------------------------*/
    }
}

void main_menu()
{
    /*---------------------------------------------*/
    thread my_thread_2(func_for_thread); //создание потоков
    /*---------------------------------------------*/


    int el;
    while((change >= 1) && (change <= 8))
    {
        mut.lock();//чтобы второй поток ничего не выводила пока не выбрана команда
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
        mut.unlock();

        try
        {
            switch (change) {
                case 1:
                    mut.lock();//также чтобы не разрывались строчки
                    cout << "Enter element: ";
                    cin >> el;
                    mut.unlock();
                    my_command->push("push", el);
                    break;
                case 2:
                    mut.lock();
                    cout << "Enter element: ";
                    cin >> el;
                    mut.unlock();
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
                    break;
                default:
                    break;
            }
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        /*---------------------------------------------*/
        log.print("It's thread 1! | Получил команду!"); // класс Logger
        /*---------------------------------------------*/
    }
    my_thread_2.join();

}

int main()
{

    /*---------------------------------------------*/
    thread my_thread_1(main_menu); //главное меню
    my_thread_1.join();
    /*---------------------------------------------*/

    return 0;
}