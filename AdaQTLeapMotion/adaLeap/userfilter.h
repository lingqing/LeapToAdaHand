#ifndef USERFILTER_H
#define USERFILTER_H

#define CON_SIZE 100
#define FILGER_PARA 5

#include <iostream>

using namespace std;

class UserFilter
{
public:
    UserFilter();

    bool addItem(float item);

    float getResult();

private:
    float data[CON_SIZE];
    int begin;
    int end;
    int count;

    float result;
    double sum;
};

#endif // USERFILTER_H
