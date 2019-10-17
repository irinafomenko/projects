//
// Created by ifomenko on 27.09.2019.
//

#ifndef SPISOK_2_CLASS_MYQUEUE_H
#define SPISOK_2_CLASS_MYQUEUE_H

#include "Structure.h"


class myQueue: public Structure{
public:
    myQueue() {};
    ~myQueue()
    {
        while(begin != NULL)
        {
            List* tmp = begin;
            begin = begin->next;
            delete tmp;
        }
    }
    /*
    void push(int n)
    {
        logg.print("push() function");
        if(end != NULL)
        {
            List* temp = new List(n, NULL);
            end->next = temp;
            end = end->next;
            logg.print("Add element");
        }
        else
        {
            end = new List(n, NULL);
            begin = end;
            logg.print("Add element");
        }
        size++;
    }*/
    /*---------------------------------------------*/
    void push(std::string com, int n = 0)
    {
        logg.print("push function of queue");
        if(end != NULL)
        {
            List* temp = new List(n, NULL, com);
            end->next = temp;
            end = end->next;
            logg.print("Add element " + std::to_string(n));
        }
        else
        {
            end = new List(n, NULL, com);
            begin = end;
            logg.print("Add element " + std::to_string(n));
        }
        size++;
    }

    std::pair<std::string, int> head()
    {
        logg.print("head() function of queue");
        if(begin != NULL)
        {
            logg.print("Return head element");
            return begin->commands;
        }
        throw ex2;
        //return 0;
    }
    /*---------------------------------------------*/
    void pop()
    {
        logg.print("pop() function");
        if(begin == NULL) {throw ex2;}
        if(begin == end) {end = NULL;}
        List* el = begin;
        begin = begin->next;
        delete el;
        size--;
        logg.print("Deleted first element");
    }

    int size_of_queue()
    {
        logg.print("size_of_queue() function");
        logg.print("Return size of queue");
        return size;
    }

    void print()
    {
        logg.print("print() function");
        if(begin == NULL) {throw ex2;}
        List* temp = begin;
        while (temp != NULL)
        {
            int el = temp->num;
            std::cout << el << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
        logg.print("Print queue");
    }


};

#endif //SPISOK_2_CLASS_MYQUEUE_H
