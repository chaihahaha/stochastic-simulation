/*****************************************************
* Shitong_CHAI_code_SS_Lab4.c                        *
*                                                    *
* The Lab #4 experiment program source code.         *
* To compile: g++ -O2 Shitong_CHAI_code_SS_Lab4.cpp  *
* Rabbit.h mt19937ar.h mt19937ar.c                   *
*                                                    *
*****************************************************/
#include "Rabbit.h"
int main()
{
    list<Rabbit*> pop;
    for(int i=0;i<5;i++)
    {
        Rabbit *r = new MaleRabbit(i);
        pop.push_back(r);
    }
    for(int i=5;i<9;i++)
    {
        Rabbit *r = new FemaleRabbit(i);
        pop.push_back(r);
    }
    for(list<Rabbit*>::iterator i=pop.begin(); i!=pop.end();++i)
    {
        (*i)->print();
    }

}