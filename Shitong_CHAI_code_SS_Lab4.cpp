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
    for(int i=0;i<50;i++)
    {
        Rabbit *r = new FemaleRabbit();
        pop.push_back(r);
    }
    for(int i=50;i<90;i++)
    {
        Rabbit *r = new MaleRabbit();
        pop.push_back(r);
    }
    for(list<Rabbit*>::iterator i=pop.begin(); i!=pop.end();++i)
    {
        (*i)->print();
    }
    cout<<endl;
    //list<Rabbit*>::iterator old_i;
    
    for(int j=0;j<400;j++)
    {
        list<Rabbit*>::iterator i=pop.begin();
        list<Rabbit*>::iterator end=pop.end();
        while(i != end)
        {
            
            bool is_dead = (*i)->one_day_life(pop);
            (*i)->print();
            // cout<<(is_dead?"is dead":"is alive")<<endl;
            if(is_dead)
                pop.erase(i++);
            else
                i++;
        }
    }
    
    // cout<<pop.size()<<endl;
    // for(list<Rabbit*>::iterator i=pop.begin(); i!=pop.end();++i)
    // {
        // (*i)->print();
    // }

}
