//
// Created by ifomenko on 27.09.2019.
//

#ifndef SPISOK_2_CLASS_MYQUEUE_H
#define SPISOK_2_CLASS_MYQUEUE_H

#include "Structure.h"

class myQueue: public Structure{
public:
    static const char* name_class;
    myQueue(){};
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
    int get_size();
    void print();
};

#endif //SPISOK_2_CLASS_MYQUEUE_H
