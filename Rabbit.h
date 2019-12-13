/*****************************************************
* Rabbit.h                                           *
*                                                    *
* The Lab #4 experiment program source code.         *
* To compile: g++ -O2 Shitong_CHAI_code_SS_Lab4.cpp  *
* Rabbit.h mt19937ar.h mt19937ar.c                   *
*                                                    *
*****************************************************/

#include<iostream>
#include<cmath>
#include<list>
#include<iterator>
#include "mt19937ar.h"
#define YEAR 365
#define MONTH 30
using namespace std;
double uniform(double a, double b)
{
    /*
     * :argument 
     *       a,b are the endpoints of an interval [a,b]. 
     * :return  
     *       A random number in the interval [a,b].
     * :usage
     *       To generate a uniformly distributed 
     *       random number.
     */

    return (b - a) * genrand_real2() + a;
}


class Rabbit
{
    public:
        int age;
        int id;
        bool is_female;
        int mature_age;
        Rabbit():age(0), is_female(false){}

        bool is_mature(void)
        {
            if(age<mature_age)
                return false;
            else
                return true;
        }
        bool one_day_life(list<Rabbit> population)
        {
            age++;
            return die();
        }
        double survival_rate()
        {
            if(!is_mature())
                return 0.2;
            else if(is_mature() && age <= 10 * YEAR)
                return 0.5;
            else
                return max(0.5 - (age/YEAR - 10)*0.1, 0.0);
        }
        bool die()
        {
            if(genrand_real2()<survival_rate())
                return false;
            else
                return true;
        }
        virtual void print() {}
        
};
class MaleRabbit: public Rabbit
{
    public:
        MaleRabbit(int identity)
        {
            is_female=false;
            id=identity;
            mature_age = (genrand_int31()%3 + 5)*MONTH;
        }
        void print() 
        {
            cout<<"Age: "<<age<<",\tID: "<<id<<",\t"<<(is_female?"Female":"Male")<<",\tMature age: "<<mature_age<<endl;
        }
};
class FemaleRabbit: public Rabbit
{
    public:
        FemaleRabbit(int identity)
        {
            is_female=true;
            id=identity;
            mature_age = (genrand_int31()%3 + 5)*MONTH;
        }
        bool one_day_life(list<Rabbit> &population)
        {
            // return true if dead
            age++;
            
            if(can_give_birth())
            {
                days_after_parturition++;
                days_after_pregnant++;
            }
            get_pregnant();
            give_birth(population);
            return die();
            
        }
        void print() 
        {
            cout<<"Age: "<<age<<",\tID: "<<id<<",\t"<<(is_female?"Female":"Male")<<",\tMature age: "<<mature_age<<", days after parturition:"<<days_after_parturition<<",\tdays after pregnant:"<<days_after_pregnant<<",\t"<<(is_pregnant()?"Pregnant":"Not Pregnant")<<",\t"<<(can_give_birth()?"Can give birth":"Cannot give birth")<<endl;
        }
    private:
        int days_after_parturition=-1;
        int days_after_pregnant=-1;
        bool _is_pregnant=false;
        bool female_birth(double gender_ratio_female)
        {
            //give birth to a female rabbit, influenced by gender ratio
            if(genrand_real2()<=gender_ratio_female)
                return true;
            else
                return false;
        }
        int fertility()
        {
            // give birth to 1 to 6 baby rabbits
            return (int)(pow(genrand_real2(),2)/(1.0/6))+1;
        }
        void get_pregnant()
        {
            if(can_give_birth() && days_after_parturition >= 3)
            {
                days_after_pregnant=0;
                _is_pregnant = true;
            }
        }
        bool is_pregnant()
        {
            return _is_pregnant; //Amenorrhea
        }
        bool can_give_birth()
        {
            //Lactational Amenorrhea, Immature
            if((!is_pregnant()) && is_mature())
                return true; 
            else
                return false;
        }
        void give_birth(list<Rabbit> population)
        {
            if(can_give_birth() && days_after_pregnant >= 27)
            {
                //can give birth if not in amenorrhea
                int number_of_birth = fertility();
                for(int i=0; i<number_of_birth; i++)
                {
                    Rabbit baby;
                    if(female_birth(0.5))
                        baby = FemaleRabbit(population.size());
                    else
                        baby = MaleRabbit(population.size());
                    population.push_front(baby);
                }
            }
            days_after_parturition=0;
            _is_pregnant=false;
            return;
        }
        
};
