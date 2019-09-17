//
// Created by ifomenko on 17.09.2019.
//
#include <queue>
#include <ctime>
#include <iostream>

using namespace std;
/*----------STL-----------*/
unsigned int speed_test()
{
    int number;
    int indx = 0;
    cout << "Enter the numbers of items: " << endl;
    cin >> number;
    queue <int> q;
    int *array = new int[number];
    //--1--
    for (int i = 0; i < number; i++)
    {
        array[i] = 1 + rand() % 10;
    }
    unsigned int start_time =  clock(); // начальное время
    //--2--
    for(int i=0; i<number; i++)
    {
        q.push(array[i]);
    }
    //--3--
    while(!q.empty() && indx<number) {

        if(q.front() == array[indx])
        {
            //cout << "TRU: " << q.front() << " - " << array[indx] << endl;
            q.pop();
            indx++;
        }
        else
        {
            cout << "False!" << q.front() << " - " << array[indx] << endl;
            break;
        }
    }
    unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time; // искомое время
    delete [] array;
    return search_time;
}
/*------------------------*/
