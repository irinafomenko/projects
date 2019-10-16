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
protected:
    /*struct Data
    {
        int num;
        std::string command;
        Data* next;
        Data(): next(NULL) {};
        Data(int n, Data* head, std::string cmd)
        {
            num = n;
            next = head;
            command = cmd;
        };
        Data(Data* head, std::string cmd)
        {
            //num = n;
            next = head;
            command = cmd;
        };
    }*head, *tail;*/
    struct List
    {
        int num;
        std::pair<std::string, int> commands;
        //std::string command;
        List* next;
        List* prev;
        List(): next(NULL), prev(NULL){};
        List(int n, List* head): prev(NULL)
        {
            num = n;
            next = head;
        };
        /*---------------------------------------------*/
        List(int n, List* head, std::string com): prev(NULL)
        {
            commands.first = com;
            commands.second = n;
            //num = n;
            next = head;
            //command = com;
        };

        List(List* head, std::string com): prev(NULL)
        {
            commands.first = com;
            commands.second = 0;
            //num = n;
            next = head;
            //command = com;
        };
        /*---------------------------------------------*/
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
    virtual int begin_element() {return begin->num;};
    virtual int end_element() { return end->num;};
    virtual int size_of_queue() {return size;};
};

#endif //SPISOK_2_STRUCTURE_H
