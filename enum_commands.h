//
// Created by ifomenko on 12.11.2019.
//

#ifndef SPISOK_2_ENUM_COMMANDS_H
#define SPISOK_2_ENUM_COMMANDS_H

#include <iostream>

enum myCmd
{
    PUSH = 1,
    PUSH_FRONT,
    POP,
    POP_BACK,
    BEGIN_ELEMENT,
    END_ELEMENT,
    GET_SIZE,
    PRINT
};

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

std::string enum_to_str(int enm)
{
    std::string result;
    if(enm == PUSH) {result = "push";}
    else if(enm == PUSH_FRONT) {result = "push_front";}
    else if(enm == POP) {result = "pop";}
    else if(enm == POP_BACK) {result = "pop_back";}
    else if(enm == BEGIN_ELEMENT) {result = "begin_element";}
    else if(enm == END_ELEMENT) {result = "end_element";}
    else if(enm == GET_SIZE) {result = "get_size";}
    else if(enm == PRINT) {result = "print";}
    return result;
}
#endif //SPISOK_2_ENUM_COMMANDS_H
