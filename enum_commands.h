//
// Created by ifomenko on 12.11.2019.
//

#ifndef SPISOK_2_ENUM_COMMANDS_H
#define SPISOK_2_ENUM_COMMANDS_H

#include <iostream>

enum myCmd
{
    PUSH,
    PUSH_FRONT,
    POP,
    POP_BACK,
    BEGIN_ELEMENT,
    END_ELEMENT,
    GET_SIZE,
    PRINT
} cmd;

myCmd str_to_enum(std::string str)
{
    myCmd result;
    if(str == "push") {result = PUSH;}
    else if(str == "push_front") {result = PUSH_FRONT;}
    else if(str == "pop") {result = POP;}
    else if(str == "pop_back") {result = POP_BACK;}
    else if(str == "begin_element") {result = BEGIN_ELEMENT;}
    else if(str == "end_element") {result = END_ELEMENT;}
    else if(str == "get_size") {result = GET_SIZE;}
    else if(str == "print") {result = PRINT;}
    return result;
}
#endif //SPISOK_2_ENUM_COMMANDS_H
