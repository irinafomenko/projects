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

    void push(int n);
    void push_front(int n);
    void pop_back();
    int begin_element();
    int end_element();
    void pop();
    int size_of_queue();
    void print();
};

#endif //SPISOK_2_CLASS_DEQUE_H
