//
// Created by dobrikov on 9/24/2019.
//

#ifndef SPISOK_2_STRUCTURE_H
#define SPISOK_2_STRUCTURE_H

#include <iostream>
#include <windef.h>
#include "my_exceptions.h"
#include "Logger.h"

//Logger logg("log_example.txt", "Structure");

class Structure {
protected:
    struct List
    {
        int num;
        std::pair<std::string, int> commands;
        //std::sring command;
        List* next;
        List* prev;
        List(): next(NULL), prev(NULL){};
        List(int n, List* nxt): prev(NULL)
        {
            num = n;
            next = nxt;
        };
        /*---------------------------------------------*/
        List(int n, List* nxt, std::string com): prev(NULL)
        {
            commands.first = com;
            commands.second = n;
            //num = n;
            next = nxt;
            //command = com;
        };
        /*---------------------------------------------*/
        List(int n, List* nxt, List* prv)
        {
            num = n;
            next = nxt;
            prev = prv;
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
    virtual int begin_element() {return begin->num;};
    virtual int end_element() { return end->num;};
    virtual int size_of_queue() {return size;};
};

#endif //SPISOK_2_STRUCTURE_H
