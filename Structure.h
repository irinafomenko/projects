//
// Created by dobrikov on 9/24/2019.
//

#ifndef SPISOK_2_STRUCTURE_H
#define SPISOK_2_STRUCTURE_H

#include <iostream>

class Structure {
public:
    Structure(){};     //constructor
    ~Structure(){};   //destructor
    /*int num;
    Structure* next;
    int size = 0;
    Structure* begin;
    Structure* end;*/
    virtual void push(int n) {};       //base methods
    //virtual void push_front(int n);
    virtual void pop() {};
    //virtual void pop_back();
    virtual int head_element() {return 0;};
    //virtual int end_element();
    virtual int print_size() {return 0;};
};

class myQueue: public Structure{
    struct myQueue1
    {
        int num;
        myQueue1 *next;
        myQueue1(): next(NULL) {};
    }*begin, *end;
    int size = 0;
public:
    myQueue(): begin(NULL), end(NULL){};
    /*myQueue(int n)
    {
        begin->num = n;
        begin->next = NULL;
        end = NULL;
    }*/
    ~myQueue()
    {
        while(begin)
        {
            myQueue1* tmp = begin;
            begin = begin->next;
            delete tmp;
        }
    }

    void push(int n)
    {
        if(end != NULL)
        {
            myQueue1* temp = new myQueue1;
            temp->num = n;
            temp->next = NULL;
            end->next = temp;
            end = end->next;
        }
        else
        {
            end = new myQueue1;
            end->num = n;
            end->next = NULL;
            begin = end;
        }
        size++;
    }

    void pop()
    {
        if(begin == NULL)
        {
            std::cout << "Queue have not elements!" << std:: endl;
        }
        else
        {
            if (begin == end) end = NULL;
            myQueue1* el = begin;
            begin = begin->next;
            delete el;
            size--;
        }
    }

    int head_element()
    {
        if(begin != NULL)
        {
            int el = begin->num;
            return el;
        }
        else
        {
            return 0;
        }
    }

    int print_size()
    {
        return size;
    }

    void Print()
    {
        if(begin == NULL)
        {
            std::cout << "Is empty!" << std::endl;
        }
        else
        {
            myQueue1* temp = begin;
            while (temp != NULL)
            {
                int el = temp->num;
                std::cout << el << " ";
                temp = temp->next;
            }
            std::cout << std::endl;
        }
    }
};

#endif //SPISOK_2_STRUCTURE_H
