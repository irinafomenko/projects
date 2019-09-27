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
        while(begin)
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
            List* temp = new List;
            temp->num = n;
            temp->next = NULL;
            end->next = temp;
            end = end->next;
        }
        else
        {
            end = new List;
            end->num = n;
            end->next = NULL;
            begin = end;
        }
        size++;
    }

    void pop()
    {
        try{
            if(begin == NULL) {throw ex2;}
            if (begin == end) end = NULL;
            List* el = begin;
            begin = begin->next;
            delete el;
            size--;
        }
        catch(std::exception& e){
            std::cout << e.what() << std::endl;
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
        try{
            List* temp = begin;
            if(temp == NULL)
            {
                throw ex2;
            }
            while (temp != NULL)
            {
                int el = temp->num;
                std::cout << el << " ";
                temp = temp->next;
            }
            std::cout << std::endl;
        }
        catch (std::exception& e){
            std::cout << e.what() << std::endl;
        }

    }
};

#endif //SPISOK_2_CLASS_MYQUEUE_H
