#include <iostream>
#include <queue>
#include <ctime>

using namespace std;

struct Data
{
    int data;
};

struct List
{

    List() : next(NULL){}
    List(int n) : next(NULL)
    {
        num.data = n;
    }
    Data num;
    List* next;
};

struct Queue_v1
{
    Queue_v1() : begin(NULL), end(NULL){}
    List* begin;
    List* end;
    int size = 0;
};
Queue_v1 queue_v1;

void Print()
{
    if(queue_v1.begin==NULL)
    {
        cout << "Is empty!" << endl;
    }
    else
    {
        List* tmp = queue_v1.begin;
        while (tmp!=NULL)
        {
            int el = tmp->num.data;
            cout << el << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }

}


void push(int n)
{
    if(queue_v1.end!=NULL)
    {
        queue_v1.end->next = new List(n);
        queue_v1.end = queue_v1.end->next;
    }
    else
    {
        queue_v1.end = new List(n);
        queue_v1.begin = queue_v1.end;
    }
    queue_v1.size++;
}

void pop()
{
    if (queue_v1.begin!=NULL)
    {
        if (queue_v1.begin == queue_v1.end) queue_v1.end = NULL;
        List* el = queue_v1.begin;
        queue_v1.begin = queue_v1.begin->next;
        delete el;
        queue_v1.size--;
    }
    else
    {
        cout << "List have not elements!" << endl;
    }
}

int head_element()
{
    if(queue_v1.begin!=NULL)
    {
        int el = queue_v1.begin->num.data;
        //cout << el << endl;
        return el;
    }
    else
    {
        cout << "List have not elements!" << endl;
        return 0;
    }
}

unsigned int speed_test_mylist()
{
    int number;
    int size;
    int indx = 0;
    cout << "Enter the numbers of items: " << endl;
    cin >> number;
    int *array = new int[number];
    //--1--
    for (int i = 0; i < number; i++)
    {
        array[i] = 1 + rand() % 10;
    }
    unsigned int start_time =  clock(); // начальное время
    //--2--
    for(int i=0; i<number; i++)
    {
        push(array[i]);
    }
    //--3--
    size = queue_v1.size;
    while(size!=0 && indx<number)
    {
        if(head_element() == array[indx])
        {
            //int el = head_element();
            //cout << "TRU: " << el << " - " << array[indx] << endl;
            pop();
            indx++;
        }
        else
        {
            int el = head_element();
            cout << "False!" << el << " - " << array[indx] << endl;
            break;
        }
    }
    unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time; // искомое время

    return search_time;
}

/*----------STL-----------*/
unsigned int speed_test()
{
    int number;
    int indx = 0;
    cout << "Enter the numbers of items: " << endl;
    cin >> number;
    queue <int> q;
    int *array = new int[number];
    //--1--
    for (int i = 0; i < number; i++)
    {
        array[i] = 1 + rand() % 10;
    }
    unsigned int start_time =  clock(); // начальное время
    //--2--
    for(int i=0; i<number; i++)
    {
        q.push(array[i]);
    }
    //--3--
    while(!q.empty() && indx<number) {

        if(q.front() == array[indx])
        {
            //cout << "TRU: " << q.front() << " - " << array[indx] << endl;
            q.pop();
            indx++;
        }
        else
        {
            cout << "False!" << q.front() << " - " << array[indx] << endl;
            break;
        }
    }
    unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time; // искомое время
    delete [] array;
    return search_time;
}
/*------------------------*/

int main()
{
    //queue.begin = new List;//List(0);
    //queue.end = queue.begin;
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
                cout << "1 - Add element" << endl;
                cout << "2 - Delete first element" << endl;
                cout << "3 - Print first element" << endl;
                cout << "4 - Print size" << endl;
                cout << "5 - Print list" << endl;
                cout << "6 - Speed_test" << endl;
                cout << "7 - Quit" << endl;
                cin >> change;

                switch (change) {
                    case 1:
                        cout << "Enter element: ";
                        cin >> el;
                        push(el);
                        break;
                    case 2:
                        pop();
                        break;
                    case 3:
                        cout << head_element() << endl;
                        break;
                    case 4:
                        cout << "Size: " << queue_v1.size << endl;
                        break;
                    case 5:
                        Print();
                        break;
                    case 6:
                        s_time = speed_test_mylist();
                        cout << "Time: " << s_time << endl;
                        break;
                    case 7:
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