//
// Created by dobrikov on 9/24/2019.
//

#ifndef SPISOK_2_STRUCTURE_H
#define SPISOK_2_STRUCTURE_H

class Structure {
    Structure();            //constructor
    virtual ~Structure();   //destructor
public:
    virtual void push(int n);       //base methods
    virtual void push_front(int n);
    virtual void pop();
    virtual void pop_back();
    virtual int head_element();
    virtual int end_element();
    virtual int print_size();
};

#endif //SPISOK_2_STRUCTURE_H
