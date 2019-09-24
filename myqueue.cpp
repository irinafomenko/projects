//
// Created by ifomenko on 17.09.2019.
//
#include <iostream>
#include <ctime>
#include <exception>

using namespace std;

/*----------exception---------------*/
class myexception: public exception
{
    virtual const char* what() const throw()
    {
        return "Queue have not elements!";
    }
public:
    const char* not_empty()
    {
        return "Queue is not empty!";
    }
} myex;
/*----------------------------------*/

struct Data
{
    int data;
};

struct List
{

    List() : next(NULL), prev(NULL){}
    List(int n) : next(NULL), prev(NULL)
    {
        num.data = n;
    }
    Data num;
    List* next;
    List* prev;
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
    /*if(queue_v1.begin==NULL)
    {
        cout << "Is empty!" << endl;
    }
    else
    {*/
    try{
        List* tmp = queue_v1.begin;
        if(tmp == NULL)
        {
            throw myex;
        }
        while (tmp!=NULL)
        {
            int el = tmp->num.data;
            cout << el << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }
    catch (exception& e){
        cout << e.what() << endl;
    }
    //}
}


void push(int n)
{
    if(queue_v1.end!=NULL)
    {
        List* temp = new List(n);
        temp->next = NULL;
        temp->prev = queue_v1.end;
        queue_v1.end->next = temp;
        queue_v1.end = queue_v1.end->next;
    }
    else
    {
        queue_v1.end = new List(n);
        queue_v1.end->prev = NULL;
        queue_v1.end->next = NULL;
        queue_v1.begin = queue_v1.end;
    }
    queue_v1.size++;
}

void push_front(int n)
{
    if(queue_v1.begin != NULL)
    {
        List* tmp = new List(n);
        tmp->prev = NULL;
        tmp->next = queue_v1.begin;
        queue_v1.begin->prev = tmp;
        queue_v1.begin = tmp;
        /*
        if(queue_v1.size == 1)
        {
            queue_v1.end->prev = tmp;
        }*/
    }
    else
    {
        queue_v1.begin = new List(n);
        queue_v1.begin->prev = NULL;
        queue_v1.begin->next = NULL;
        queue_v1.end = queue_v1.begin;
    }
    queue_v1.size++;
}

void pop()
{
    try{
        if(queue_v1.begin == NULL) {throw myex;}
        if (queue_v1.begin == queue_v1.end) queue_v1.end = NULL;
        List* el = queue_v1.begin;
        queue_v1.begin = queue_v1.begin->next;
        delete el;
        queue_v1.size--;
    }
    catch(exception& e){
        cout << e.what() << endl;
    }/*
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
    }*/
}

void pop_back()
{
    try{
        if(queue_v1.end == NULL) {throw myex;}
        if (queue_v1.begin == queue_v1.end) queue_v1.begin = NULL;
        List* el = queue_v1.end;
        queue_v1.end = queue_v1.end->prev;
        delete el;
        if(queue_v1.size != 1)
        {
            queue_v1.end->next = NULL;
        }
        queue_v1.size--;
    }
    catch(exception& e){
        cout << e.what() << endl;
    }
    /*if (queue_v1.end!=NULL)
    {
        if (queue_v1.begin == queue_v1.end) queue_v1.begin = NULL;
        List* el = queue_v1.end;
        queue_v1.end = queue_v1.end->prev;
        delete el;
        if(queue_v1.size != 1)
        {
            queue_v1.end->next = NULL;
        }
        queue_v1.size--;
    }
    else
    {
        cout << "List have not elements!" << endl;
    }*/
}

int head_element()
{
    if(queue_v1.begin!=NULL)
    {
        int el = queue_v1.begin->num.data;
        return el;
    }
    else
    {
        //cout << "List have not elements!" << endl;
        return 0;
    }
}

int end_element()
{
    if(queue_v1.end!=NULL)
    {
        int el = queue_v1.end->num.data;
        return el;
    }
    else
    {
        //cout << "List have not elements!" << endl;
        return 0;
    }
}

int print_size()
{
    int size = queue_v1.size;
    return size;
}

unsigned int speed_test_mylist()
{
    try{
        if(queue_v1.size != 0) {throw myex;}
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
        cout << "Time: " << search_time << endl;
        return search_time;
    }
    catch(myexception e){
        cout << e.not_empty() << endl;
        return 0;
    }
}
