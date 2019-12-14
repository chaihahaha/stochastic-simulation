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

class Rabbit
{
    public:
        static int counter;
        static int mature_male_counter;
        int age;
        int id;
        int mature_age;
        double female_ratio=0.5;
        bool is_female;
        bool is_dead;
        Rabbit():age(0), is_female(false), is_dead(false)
        {
            id=counter++;
        }

        bool is_mature(void)
        {
            if(age<mature_age)
                return false;
            else
                return true;
        }
        virtual bool n_days_life(list<Rabbit*> &population, int step){}
        
        bool die(int step)
        {
            if(genrand_real2()<survival_rate(step))
                return false;
            else
            {
                is_dead=true;
                return true;
            }
        }
        virtual void print() {}
    private:
        double survival_rate_per_year()
        {
            
            if(!is_mature())
                return 0.2;
            else if(age <= 2 * YEAR)
                return 0.5;
            else
            {
                return max(0.5 - (age/YEAR - 2)*0.25, 0.0);
            }
        }
        double survival_rate(int step)
        {
            return pow(survival_rate_per_year()*0.4, 1.0/YEAR*(double)step);
        }
        
};
int Rabbit::counter = 0;
int Rabbit::mature_male_counter = 0;

class MaleRabbit: public Rabbit
{
    public:
        MaleRabbit()
        {
            is_female=false;
            mature_age = (genrand_int31()%3 + 5)*MONTH;
        }
        bool n_days_life(list<Rabbit*> &population, int step)
        {
            die(step);
            if(!is_dead)
            {
                bool not_mature=!is_mature();
                age+=step;
                bool mature = is_mature();
                if(not_mature && mature)
                    mature_male_counter++;
            }
            else 
            {
                if(is_mature())
                    mature_male_counter--;
            }
            return is_dead;
        }
        void print() 
        {
            cout<<"Age: "<<age<<",\tID: "<<id<<",\t"<<(is_female?"Female":"Male")<<",\t"<<(is_dead?"Dead":"Alive")<<",\t"<<(is_mature()?"Is Mature":"Not Mature")<<",\tMature Male number: "<<mature_male_counter<<endl;
        }
};
class FemaleRabbit: public Rabbit
{
    public:
        FemaleRabbit()
        {
            is_female=true;
            mature_age = (genrand_int31()%3 + 5)*MONTH;
            pregnant_cycle = genrand_int31()%10 + 27;
            lactational_amenorrhea = genrand_int31()%3;
        }
        bool n_days_life(list<Rabbit*> &population, int step)
        {
            // return true if dead
            
            if(!is_dead)
            {
                
                age+=step;
                if(is_mature())
                    days_after_pregnant+=step;
                give_birth(population);
            }
            return die(step);
            
        }
        void print() 
        {
            cout<<"Age: "<<age<<",\tID: "<<id<<",\t"<<(is_female?"Female":"Male")<<",\t"<<(is_dead?"Dead":"Alive")<<",\t"<<(is_mature()?"Is Mature":"Not Mature")<<",\tdays after pregnant:"<<days_after_pregnant<<endl;
        }
    private:
        int days_after_pregnant=0;
        int pregnant_cycle; //least time of pregnancy needed before giving birth
        int lactational_amenorrhea; //least time of Lactational Amenorrhea
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
        

        void give_birth(list<Rabbit*> &population)
        {
            if(is_mature() && mature_male_counter>0)
            {
                //can give birth if not in amenorrhea
                int cycles = days_after_pregnant/(pregnant_cycle + lactational_amenorrhea);
                int number_of_birth = 0;
                for(int i=0; i<cycles; i++)
                {
                    number_of_birth += fertility();
                }
                days_after_pregnant -= cycles*(pregnant_cycle + lactational_amenorrhea);
                for(int i=0; i<number_of_birth; i++)
                {
                    Rabbit *baby;
                    if(female_birth(female_ratio))
                        baby = new FemaleRabbit();
                    else
                        baby = new MaleRabbit();
                    population.push_front(baby);
                }
            }
            
            return;
        }
        
};
