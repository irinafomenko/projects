//
// Created by ifomenko on 27.09.2019.
//

#ifndef SPISOK_2_CLASS_DEQUE_H
#define SPISOK_2_CLASS_DEQUE_H

#include "class_myqueue.h"

class myDeque: public myQueue {
public:
    myDeque(){};
    ~myDeque()
    {
        while(begin != NULL)
        {
            List* tmp = begin;
            begin = begin->next;
            delete tmp;
        }
    };

    void push(int n)
    {
        logg.print("push() function of deque");
        if(end != NULL)
        {
            List* temp = new List(n, NULL, end);
            end->next = temp;
            end = end->next;
            logg.print("Add element " + std::to_string(n));
        }
        else
        {
            end = new List(n, NULL, NULL);
            begin = end;
            logg.print("Add element " + std::to_string(n));
        }
        size++;
    }

    void push_front(int n)
    {
        logg.print("push_front() function of deque");
        if(begin != NULL)
        {
            List* tmp = new List(n, begin, NULL);
            begin->prev = tmp;
            begin = tmp;
            logg.print("Add element " + std::to_string(n));
        }
        else
        {
            begin = new List(n, NULL, NULL);
            end = begin;
            logg.print("Add element " + std::to_string(n));
        }
        size++;
    }

    void pop_back()
    {
        logg.print("pop_back() function of deque");
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
        logg.print("Deleted last element");
    }

    int begin_element()
    {
        logg.print("begin_element() function of deque");
        if(begin != NULL)
        {
            logg.print("Return begin element");
            return begin->num;
        }
        throw ex2;
        //return 0;
    }

    int end_element()
    {
        logg.print("end_element() function of deque");
        if(end != NULL)
        {
            logg.print("Return end element");
            return end->num;
        }
        throw ex2;
        //return 0;
    }
};

#endif //SPISOK_2_CLASS_DEQUE_H
