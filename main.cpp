#include <iostream>
#include "Logger.h"
#include "class_deque.h"
#include <windows.h>
#include <functional>
#include <thread>
#include <mutex>
#include <list>
#include <map>
#include <queue>
//#include "queue_menu.h"

using namespace std;

/*---------------------------------------------*/
myQueue* myQu = new myQueue;
myDeque* myDequ = new myDeque;
/*---------------------------------------------*/
list <string> my_commands;
list <int> elements;
mutex mut;
/*---------------------------------------------*/

int xtime = 10;
int change = 1;
void func_for_thread()
{
    cout << "thread" << endl;
    int n = 0;
    while(change != 9) {
        this_thread::sleep_for(std::chrono::seconds(xtime));
        list<int>::iterator el = elements.begin();
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
        }
        //break;
        //n++;
        //my_commands.clear();
        //elements.clear();
    }
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
    thread my_thread_2(func_for_thread); //создание потоков

    //unique_lock<std::mutex> guard(m, std::defer_lock);
    /*---------------------------------------------*/

    int el;
    while((change >= 1) && (change <= 8)) {
        cout << "1 - Add element to back" << endl;
        cout << "2 - Add element to front" << endl;
        cout << "3 - Delete first element" << endl;
        cout << "4 - Delete last element" << endl;
        cout << "5 - Print first element" << endl;
        cout << "6 - Print last element" << endl;
        cout << "7 - Print size" << endl;
        cout << "8 - Print deque" << endl;
        cout << "9 - Quit" << endl;
        cin >> change;

        try {
            switch (change) {
                case 1:
                {
                    cout << "Enter element: ";
                    cin >> el;
                    //myDequ->push(el);
                    elements.push_back(el);
                    my_commands.push_back("push");
                    break;
                }
                case 2:
                {
                    cout << "Enter element: ";
                    cin >> el;
                    elements.push_back(el);
                    my_commands.push_back("push_front");
                    //myDequ->push_front(el);
                    break;
                }
                case 3:
                {
                    my_commands.push_back("pop");
                    //myDequ->pop();
                    break;
                }
                case 4:
                {
                    my_commands.push_back("pop_back");
                    //myDequ->pop_back();
                    break;
                }
                case 5:
                {
                    my_commands.push_back("head_element");
                    //cout << myDequ->head_element() << endl;
                    break;
                }
                case 6:
                {
                    my_commands.push_back("end_element");
                    //cout << myDequ->end_element() << endl;
                    break;
                }
                case 7:
                {
                    my_commands.push_back("size_of_queue");
                    //cout << "Size: " << myDequ->size_of_queue() << endl;
                    break;
                }
                case 8:
                {
                    my_commands.push_back("print");
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

    }
    my_thread_2.join();

    return 0;
}