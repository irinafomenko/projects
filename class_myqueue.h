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
    /*---------------------------------------------*/
    void push(std::pair<std::string, int> com);//std::string com, int n = 0);
    std::pair<std::string, int> head();
    /*---------------------------------------------*/
    void pop();
    int size_of_queue();
    void print();
};

#endif //SPISOK_2_CLASS_MYQUEUE_H
