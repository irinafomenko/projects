//
// Created by dobrikov on 9/24/2019.
//

#ifndef SPISOK_2_STRUCTURE_H
#define SPISOK_2_STRUCTURE_H

#include <iostream>
#include <windef.h>
#include "my_exceptions.h"

myexception ex2;
class Structure {
public:
    struct List
    {
        int num;
        std::string command;
        List* next;
        List* prev;
        List(): next(NULL), prev(NULL){};
        List(int n, List* head): prev(NULL)
        {
            num = n;
            next = head;
        };
        List(int n, List* head, std::string com): prev(NULL)
        {
            num = n;
            next = head;
            command = com;
        };
        List(List* head, std::string com): prev(NULL)
        {
            //num = n;
            next = head;
            command = com;
        };
        List(int n, List* head, List* tail)
        {
            num = n;
            next = head;
            prev = tail;
        };
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
    virtual List* head_element_queue() {return begin;}
    virtual int end_element() { return end->num;};
    virtual int size_of_queue() {return size;};
};

#endif //SPISOK_2_STRUCTURE_H
