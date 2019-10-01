//
// Created by dobrikov on 9/24/2019.
//

#ifndef SPISOK_2_STRUCTURE_H
#define SPISOK_2_STRUCTURE_H

#include <iostream>
#include "my_exceptions.h"

myexception ex2;

class Structure {
protected:
    struct List
    {
        int num;
        List* next;
        List* prev;
        List(): next(NULL), prev(NULL){};
    }*begin, *end;
    int size = 0;
public:
    Structure(): begin(NULL), end(NULL){};     //constructor
    ~Structure(){};   //destructor
    virtual void push(int n) {};       //base methods
    virtual void push_front(int n) {};
    virtual void pop() {};
    virtual void pop_back() {};
    virtual int head_element() {return begin->num;};
    virtual int end_element() { return end->num;};
    virtual int size_of_queue() {return size;};
};

#endif //SPISOK_2_STRUCTURE_H
