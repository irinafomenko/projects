#include <iostream>
#include "newqueue.h"
#include "myqueue.h"

using namespace std;

int main()
{
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
                        cout << head_element() << endl;
                        break;
                    case 6:
                        cout << end_element() << endl;
                        break;
                    case 7:
                        cout << "Size: " << print_size() << endl;
                        break;
                    case 8:
                        Print();
                        break;
                    case 9:
                        s_time = speed_test_mylist();
                        cout << "Time: " << s_time << endl;
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