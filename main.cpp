#include <iostream>
#include "newqueue.h"
#include "myqueue.h"
#include "Logger.h"
#include "Structure.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc>1)
    {
        for(int i = 1; i < argc; i++)
        {
            int el = atoi(argv[i]);
            push(el);
        }
    }
    /*---------------------------------------------*/
    // Работа с классами
    myQueue* obj;
    obj = new myQueue();
    obj->push(5);
    obj->push(6);
    cout << "1: ";
    obj->Print();
    obj->pop();
    cout << "2: ";
    obj->Print();
    cout << "3: ";
    if(obj->head_element() != 0) cout << obj->head_element() << endl;
    else cout << "List have not elements!" << endl;
    cout << "4: ";
    cout << "Size: " << obj->print_size() << endl;

    myDequeue* obj2 = new myDequeue;
    obj2->push(8);
    obj2->push_front(7);
    obj2->push_front(9);
    obj2->push(10);
    obj2->push(11);
    cout << "1: ";
    obj2->Print();
    obj2->pop();
    cout << "2: ";
    obj2->Print();
    cout << "3: ";
    cout << "Size: " << obj2->print_size() << endl;
    cout << "4: ";
    if(obj->head_element() != 0) cout << obj2->head_element() << endl;
    else cout << "Queue have not elements!" << endl;
    cout << "5: ";
    obj2->pop_back();
    obj2->Print();
    cout << "6: ";
    if(obj2->end_element() != 0) cout << obj2->end_element() << endl;
    else cout << "Queue have not elements!" << endl;
    /*---------------------------------------------*/
    Logger log("log_example.txt"); // класс Logger
    log.print("It's work!"); // класс Logger
    /*---------------------------------------------*/
    //queue.begin = new List;//List(0);
    int el;
    int change_list = 1; //выбор списка
    int change = 1; //выбор действий
    unsigned int s_time;
    while((change_list>=1) && (change_list<=2)) {
        //выбор списка
        cout << "Change:" << endl;
        cout << "1 - Queue" << endl;
        cout << "2 - My list" << endl;
        cout << "Press any key to exit" << endl;
        cin >> change_list;

        switch(change_list)
        {
            case 1:
                //выбор действия
                cout << "Change:" << endl;
                cout << "1 - Speed_test" << endl;
                cout << "2 - Quit" << endl;
                cin >> change;
                switch(change)
                {
                    case 1:
                        s_time = speed_test();
                        cout << "Time: " << s_time << endl;
                        break;
                    case 2:
                        break;
                    default:
                        break;
                }

                break;
            case 2:
                //выбор действия
                cout << "Change:" << endl;
                cout << "1 - Add element to back" << endl;
                cout << "2 - Add element to front" << endl;
                cout << "3 - Delete first element" << endl;
                cout << "4 - Delete last element" << endl;
                cout << "5 - Print first element" << endl;
                cout << "6 - Print last element" << endl;
                cout << "7 - Print size" << endl;
                cout << "8 - Print list" << endl;
                cout << "9 - Speed_test" << endl;
                cout << "10 - Quit" << endl;
                cin >> change;

                switch (change) {
                    case 1:
                        cout << "Enter element: ";
                        cin >> el;
                        push(el);
                        break;
                    case 2:
                        cout << "Enter element: ";
                        cin >> el;
                        push_front(el);
                        break;
                    case 3:
                        pop();
                        break;
                    case 4:
                        pop_back();
                        break;
                    case 5:
                        if(head_element() != 0) cout << head_element() << endl;
                        else cout << "Queue have not elements!" << endl;
                        break;
                    case 6:
                        if(end_element() != 0) cout << end_element() << endl;
                        else cout << "Queue have not elements!" << endl;
                        break;
                    case 7:
                        cout << "Size: " << print_size() << endl;
                        break;
                    case 8:
                        Print();
                        break;
                    case 9:
                        //s_time = speed_test_mylist();
                        //cout << "Time: " << s_time << endl;
                        speed_test_mylist();
                        break;
                    case 10:
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }

    }

    return 0;
}