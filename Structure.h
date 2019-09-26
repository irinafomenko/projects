//
// Created by dobrikov on 9/24/2019.
//

#ifndef SPISOK_2_STRUCTURE_H
#define SPISOK_2_STRUCTURE_H

#include <iostream>

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
    Structure(){};     //constructor
    ~Structure(){};   //destructor
    virtual void push(int n) {};       //base methods
    virtual void push_front(int n) {};
    virtual void pop() {};
    virtual void pop_back() {};
    virtual int head_element() {return 0;};
    virtual int end_element() { return 0;};
    virtual int print_size() {return 0;};
};

class myQueue: public Structure{
public:
    myQueue(){};
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
        if(begin == NULL)
        {
            std::cout << "Queue have not elements!" << std:: endl;
        }
        else
        {
            if (begin == end) end = NULL;
            List* el = begin;
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
            List* temp = begin;
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

class myDequeue: public myQueue {
public:
    myDequeue(){};
    ~myDequeue()
    {
        while(begin)
        {
            List* tmp = begin;
            begin = begin->next;
            delete tmp;
        }
    };

    void push(int n)
    {
        if(end != NULL)
        {
            List* temp = new List;
            temp->num = n;
            temp->next = NULL;
            temp->prev = end;
            end->next = temp;
            end = end->next;
        }
        else
        {
            end = new List;
            end->num = n;
            end->next = NULL;
            end->prev = NULL;
            begin = end;
        }
        size++;
    }

    void push_front(int n)
    {
        if(begin != NULL)
        {
            List* tmp = new List;
            tmp->num = n;
            tmp->prev = NULL;
            tmp->next = begin;
            begin->prev = tmp;
            begin = tmp;
        }
        else
        {
            begin = new List;
            begin->num = n;
            begin->prev = NULL;
            begin->next = NULL;
            end = begin;
        }
        size++;
    }

    void pop_back()
    {
        if(end == NULL)
        {
            std::cout << "Queue have not elements!" << std:: endl;
        }
        if (begin == end) begin = NULL;
        List* el = end;
        end = end->prev;
        delete el;
        if(size != 1)
        {
            end->next = NULL;
        }
        size--;
    }

    int end_element()
    {
        if(end!=NULL)
        {
            int el = end->num;
            return el;
        }
        else
        {
            return 0;
        }
    }
};

#endif //SPISOK_2_STRUCTURE_H
