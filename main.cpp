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
    Logger log("log_example.txt"); // класс Logger
    /*---------------------------------------------*/
    //queue.begin = new List;//List(0);
    int el;
    int change_list = 1; //выбор списка
    int change = 1; //выбор действий
    int change_class = 1; //выбор класса
    int change_queue =1; //выбор действя для queue (class)
    myQueue* myQu = new myQueue;
    myDequeue* myDequ = new myDequeue;
    unsigned int s_time;
    while((change_list>=1) && (change_list<=3)) {
        /*---------------------------------------------*/
        log.print("It's work!"); // класс Logger
        /*---------------------------------------------*/
        //выбор списка
        cout << "Change:" << endl;
        cout << "1 - Queue" << endl;
        cout << "2 - My queue (Structure)" << endl;
        cout << "3 - My queue (CLass)" << endl;
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
            case 3:
                //выбор действия
                cout << "Change:" << endl;
                cout << "1 - Queue" << endl;
                cout << "2 - Dequeue" << endl;
                cout << "3 - Quit" << endl;
                cin >> change_class;

                switch (change_class){
                    case 1:
                        cout << "Change:" << endl;
                        cout << "1 - Add element to back" << endl;
                        cout << "2 - Delete first element" << endl;
                        cout << "3 - Print first element" << endl;
                        cout << "4 - Print size" << endl;
                        cout << "5 - Print list" << endl;
                        cout << "6 - Quit" << endl;
                        cin >> change_queue;

                        switch (change_queue){
                            case 1:
                                cout << "Enter element: ";
                                cin >> el;
                                myQu->push(el);
                                break;
                            case 2:
                                myQu->pop();
                                break;
                            case 3:
                                if(myQu->head_element() != 0) cout << myQu->head_element() << endl;
                                else cout << "Queue have not elements!" << endl;
                                break;
                            case 4:
                                cout << "Size: " << myQu->print_size() << endl;
                                break;
                            case 5:
                                myQu->Print();
                                break;
                            case 6:
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
                        cout << "9 - Quit" << endl;
                        cin >> change;

                        switch (change) {
                            case 1:
                                cout << "Enter element: ";
                                cin >> el;
                                myDequ->push(el);
                                break;
                            case 2:
                                cout << "Enter element: ";
                                cin >> el;
                                myDequ->push_front(el);
                                break;
                            case 3:
                                myDequ->pop();
                                break;
                            case 4:
                                myDequ->pop_back();
                                break;
                            case 5:
                                if(myDequ->head_element() != 0) cout << myDequ->head_element() << endl;
                                else cout << "Queue have not elements!" << endl;
                                break;
                            case 6:
                                if(myDequ->end_element() != 0) cout << myDequ->end_element() << endl;
                                else cout << "Queue have not elements!" << endl;
                                break;
                            case 7:
                                cout << "Size: " << myDequ->print_size() << endl;
                                break;
                            case 8:
                                myDequ->Print();
                                break;
                            case 9:
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }

            default:
                break;
        }

    }

    return 0;
}