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

    void push(int n)
    {
        if(end != NULL)
        {
            List* temp = new List(n, NULL);
            end->next = temp;
            end = end->next;
        }
        else
        {
            end = new List(n, NULL);
            begin = end;
        }
        size++;
    }
    /*---------------------------------------------*/
    void push(std::string com, int n = 0)
    {
        if(end != NULL)
        {
            List* temp = new List(n, NULL, com);
            end->next = temp;
            end = end->next;
        }
        else
        {
            end = new List(n, NULL, com);
            begin = end;
        }
        size++;
    }
    
    std::pair<std::string, int> head()
    {
        if(begin != NULL)
        {
            return begin->commands;
        }
        throw ex2;
        //return 0;
    }
    /*---------------------------------------------*/
    void pop()
    {
            if(begin == NULL) {throw ex2;}
            if(begin == end) {end = NULL;}
            List* el = begin;
            begin = begin->next;
            delete el;
            size--;
    }

    int size_of_queue()
    {
        return size;
    }

    void print()
    {
            if(begin == NULL) {throw ex2;}
            List* temp = begin;
            while (temp != NULL)
            {
                int el = temp->num;
                std::cout << el << " ";
                temp = temp->next;
            }
            std::cout << std::endl;

    }


};

#endif //SPISOK_2_CLASS_MYQUEUE_H
