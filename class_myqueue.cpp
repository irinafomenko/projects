//
// Created by ifomenko on 28.10.2019.
//
#include "class_myqueue.h"

myexception ex_queue;
Logger logg_queue("log_example.txt", "Queue");

void myQueue::push(std::pair<std::string,int> com)//std::string com, int n)
{
    logg_queue.print("push function of queue");
    if(end != NULL)
    {
        List* temp = new List(com.second, NULL, com.first);
        end->next = temp;
        end = end->next;
        if(com.second != 0) {logg_queue.print("Add element " + std::to_string(com.second));}
        else {logg_queue.print("Add command " + com.first);}
    }
    else
    {
        end = new List(com.second, NULL, com.first);
        begin = end;
        if(com.second != 0) {logg_queue.print("Add element " + std::to_string(com.second));}
        else {logg_queue.print("Add command " + com.first);}
    }
    size++;
}

std::pair<std::string, int> myQueue::head()
{
    logg_queue.print("head() function of queue");
    if(begin != NULL)
    {
        logg_queue.print("Return head element");
        return begin->commands;
    }
    throw ex_queue;
    //return 0;
}

void myQueue::pop()
{
    logg_queue.print("pop() function");
    if(begin == NULL) {throw ex_queue;}
    if(begin == end) {end = NULL;}
    List* el = begin;
    begin = begin->next;
    delete el;
    size--;
    logg_queue.print("Deleted first element");
}

int myQueue::get_size()
{
    logg_queue.print("size_of_queue() function");
    logg_queue.print("Return size of queue " + std::to_string(size));
    return size;
}

void myQueue::print()
{
    logg_queue.print("print() function");
    if(begin == NULL) {throw ex_queue;}
    List* temp = begin;
    std::string queue;
    while (temp != NULL)
    {
        std::pair<std::string, int> el = temp->commands;
        if(el.first == "push")
        {
            std::cout << el.first << " " << el.second << std::endl;
            queue += " " + el.first + " " + std::to_string(el.second);
        }
        else
        {
            std::cout << el.first << " ";
            queue += " " + el.first;
        }
        temp = temp->next;
    }
    std::cout << std::endl;
    logg_queue.print("Print queue" + queue);
}