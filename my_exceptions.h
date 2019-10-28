//
// Created by ifomenko on 26.09.2019.
//

#ifndef SPISOK_2_MY_EXCEPTIONS_H
#define SPISOK_2_MY_EXCEPTIONS_H

#include <exception>
#include "Logger.h"

extern Logger logg_deque;

/*----------exception---------------*/
class myexception: public std::exception
{
    virtual const char* what() const throw()
    {
        logg_deque.print("Deque have not elements!");
        return "Queue have not elements!";
    }
public:
    myexception(){};
    ~myexception(){};
};
/*----------------------------------*/

#endif //SPISOK_2_MY_EXCEPTIONS_H
