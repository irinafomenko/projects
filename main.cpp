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
myQueue* myQu = new myQueue;
myDeque* myDequ = new myDeque;
/*---------------------------------------------*/
//list <string> my_commands;
//list <int> elements;
myQueue* my_command = new myQueue;
mutex mut;
/*---------------------------------------------*/
/*---------------------------------------------*/
Logger log("log_example.txt"); // класс Logger
/*---------------------------------------------*/

int xtime = 5;
int change = 1;
void func_for_thread()
{
    cout << "thread" << endl;
    int n = 0;
    while(change != 9)
    {
        this_thread::sleep_for(std::chrono::seconds(xtime));
        /*list<int>::iterator el = elements.begin();
        for (list<string>::iterator k = my_commands.begin(); k != my_commands.end(); ++k) {
            if (*k == "push") {
                myDequ->push(*el);
                ++el;
            }
            if (*k == "push_front") {
                myDequ->push_front(*el);
                ++el;
            }
            if (*k == "pop") { myDequ->pop(); }
            if (*k == "pop_back") { myDequ->pop_back(); }
            if (*k == "head_element") { cout << myDequ->head_element() << endl; }
            if (*k == "end_element") { cout << myDequ->end_element() << endl; }
            if (*k == "size_of_queue") { cout << myDequ->size_of_queue() << endl; }
            if (*k == "print") { myDequ->print(); }
        }*/
        Structure::List* k = my_command->head_element_queue();
        mut.lock();
        for(int i = 0; i != my_command->size_of_queue(); i++)
        //while(my_command->size_of_queue() != 0)
        {
            cout << k->command << endl;
            if (k->command == "push")
            {
                myDequ->push(k->num);
            }
            if (k->command == "push_front")
            {
                myDequ->push_front(k->num);
            }
            if (k->command == "pop") { myDequ->pop(); }
            if (k->command == "pop_back") { myDequ->pop_back(); }
            if (k->command == "head_element") { cout << myDequ->head_element() << endl; }
            if (k->command == "end_element") { cout << myDequ->end_element() << endl; }
            if (k->command == "size_of_queue") { cout << myDequ->size_of_queue() << endl; }
            if (k->command == "print") { myDequ->print();}
            k = k->next;
            //my_command->pop();
        }
    mut.unlock();
        mut.lock();
        my_command->pop();
        /*---------------------------------------------*/
        log.print("It's thread 2! | Выполнил команды!"); // класс Logger
        /*---------------------------------------------*/
        mut.unlock();
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

        try {
            switch (change) {
                case 1:
                {
                    cout << "Enter element: ";
                    cin >> el;
                    //myDequ->push(el);
                    my_command->push(el, "push");
                    //elements.push_back(el);
                    //my_commands.push_back("push");
                    break;
                }
                case 2:
                {
                    cout << "Enter element: ";
                    cin >> el;
                    my_command->push(el, "push_front");
                    //elements.push_back(el);
                    //my_commands.push_back("push_front");
                    //myDequ->push_front(el);
                    break;
                }
                case 3:
                {
                    my_command->push( "pop");
                    //my_commands.push_back("pop");
                    //myDequ->pop();
                    break;
                }
                case 4:
                {
                    my_command->push( "pop_back");
                    //my_commands.push_back("pop_back");
                    //myDequ->pop_back();
                    break;
                }
                case 5:
                {
                    my_command->push( "head_element");
                    //my_commands.push_back("head_element");
                    //cout << myDequ->head_element() << endl;
                    break;
                }
                case 6:
                {
                    my_command->push( "end_element");
                    //my_commands.push_back("end_element");
                    //cout << myDequ->end_element() << endl;
                    break;
                }
                case 7:
                {
                    my_command->push( "size_of_queue");
                    //my_commands.push_back("size_of_queue");
                    //cout << "Size: " << myDequ->size_of_queue() << endl;
                    break;
                }
                case 8:
                {
                    my_command->push( "print");
                    //my_commands.push_back("print");
                    //myDequ->print();
                    break;
                }
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

int main(int argc, char *argv[])
{

    if(argc>1)
    {
        for(int i = 1; i < argc; i++)
        {
            int el = atoi(argv[i]);
            myQu->push(el);
            myDequ->push(el);
        }
    }
    /*---------------------------------------------*/
    thread my_thread_1(main_menu); //главное меню
    my_thread_1.join();
    /*---------------------------------------------*/

    return 0;
}