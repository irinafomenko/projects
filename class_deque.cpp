//
// Created by ifomenko on 28.10.2019.
//
#include "class_deque.h"
#include "class_myqueue.h"

extern myexception ex2;
Logger logg_deque("log_example.txt", "Deque");

void myDeque::push(int n)
{
    logg_deque.print("push() function of deque");
    if(end != NULL)
    {
        List* temp = new List(n, NULL, end);
        end->next = temp;
        end = end->next;
        logg_deque.print("Add element " + std::to_string(n));
    }
    else
    {
        end = new List(n, NULL, NULL);
        begin = end;
        logg_deque.print("Add element " + std::to_string(n));
    }
    size++;
}

void myDeque::push_front(int n)
{
    logg_deque.print("push_front() function of deque");
    if(begin != NULL)
    {
        List* tmp = new List(n, begin, NULL);
        begin->prev = tmp;
        begin = tmp;
        logg_deque.print("Add element " + std::to_string(n));
    }
    else
    {
        begin = new List(n, NULL, NULL);
        end = begin;
        logg_deque.print("Add element " + std::to_string(n));
    }
    size++;
}

void myDeque::pop_back()
{
    logg_deque.print("pop_back() function of deque");
    if(end == NULL) {throw ex2;}
    if (begin == end) {begin = NULL;}
    List* el = end;
    end = end->prev;
    delete el;
    if(size != 1)
    {
        end->next = NULL;
    }
    size--;
    logg_deque.print("Deleted last element");
}

int myDeque::begin_element()
{
    logg_deque.print("begin_element() function of deque");
    if(begin != NULL)
    {
        logg_deque.print("Return begin element");
        return begin->num;
    }
    throw ex2;
    //return 0;
}

int myDeque::end_element()
{
    logg_deque.print("end_element() function of deque");
    if(end != NULL)
    {
        logg_deque.print("Return end element");
        return end->num;
    }
    throw ex2;
    //return 0;
}

void myDeque::pop()
{
    logg_deque.print("pop() function");
    if(begin == NULL) {throw ex2;}
    if(begin == end) {end = NULL;}
    List* el = begin;
    begin = begin->next;
    delete el;
    size--;
    logg_deque.print("Deleted first element");
}

int myDeque::size_of_queue()
{
    logg_deque.print("size_of_queue() function");
    logg_deque.print("Return size of queue");
    return size;
}

void myDeque::print()
{
    logg_deque.print("print() function");
    if(begin == NULL) {throw ex2;}
    List* temp = begin;
    std::string queue;
    while (temp != NULL)
    {
        int el = temp->num;
        std::cout << el << " ";
        queue += " " + std::to_string(el);
        temp = temp->next;
    }
    std::cout << std::endl;
    logg_deque.print("Print queue" + queue);
}