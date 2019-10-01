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
        if(end != NULL)
        {
            List* temp = new List;
            temp->num = n;
            temp->next = NULL;
            temp->prev = end;
            end->next = temp;
            end = end->next;
        }
        else
        {
            end = new List;
            end->num = n;
            end->next = NULL;
            end->prev = NULL;
            begin = end;
        }
        size++;
    }

    void push_front(int n)
    {
        if(begin != NULL)
        {
            List* tmp = new List;
            tmp->num = n;
            tmp->prev = NULL;
            tmp->next = begin;
            begin->prev = tmp;
            begin = tmp;
        }
        else
        {
            begin = new List;
            begin->num = n;
            begin->prev = NULL;
            begin->next = NULL;
            end = begin;
        }
        size++;
    }

    void pop_back()
    {
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

    }

    int end_element()
    {
        if(end != NULL)
        {
            return end->num;
        }
        return 0;
    }
};

#endif //SPISOK_2_CLASS_DEQUE_H
