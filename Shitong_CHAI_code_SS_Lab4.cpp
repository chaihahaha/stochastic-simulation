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
    unsigned long     init[4] = {0x123, 0x234, 0x345, 0x456};
    unsigned long     length  = 4;
    init_by_array(init, length);
    
    list<Rabbit*> pop;
    for(int i=0;i<5;i++)
    {
        Rabbit *r = new FemaleRabbit();
        pop.push_back(r);
    }
    for(int i=5;i<9;i++)
    {
        Rabbit *r = new MaleRabbit();
        pop.push_back(r);
    }
    // for(list<Rabbit*>::iterator i=pop.begin(); i!=pop.end();++i)
    // {
        // (*i)->print();
    // }
    // cout<<endl;
    
    
    for(int j=0;j<200;j++)
    {
        list<Rabbit*>::iterator i=pop.begin();
        list<Rabbit*>::iterator end=pop.end();
        // cout<<"Years: "<<j/YEAR<<"\tMonths: "<<(j%YEAR)/MONTH<<"\tDays: "<<j%MONTH<<"\tPopulation: "<<pop.size()<<endl;
        cout<<pop.size()<<","<<endl;
        while(i != end)
        {
            
            bool is_dead = (*i)->n_days_life(pop, MONTH);
            //(*i)->print();
            
            if(is_dead)
                pop.erase(i++);
            else
                i++;
        }
    }
    


}
