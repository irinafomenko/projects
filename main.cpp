#include <iostream>
#include "Logger.h"
#include "class_deque.h"
#include "server.h"
#include "client.h"

using namespace std;

#define CLIENT "client"

/*---------------------------------------------*/
Logger log("log_example.txt"); // класс Logger
/*---------------------------------------------*/

int main(int argc, char *argv[])
{
    if(argc>1)
    {
        if(! strcmp(argv[1],CLIENT)) {main_client();}
        else {main_server();}
    }

    return 0;
}