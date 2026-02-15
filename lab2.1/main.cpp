#include <iostream>
#include <string>
#include <vector>
#include "Country.hpp"
#include <cstdlib>
#include <ctime>

using str    = std::string;
using strVec = std::vector<std::string>;

int main( )
{
        using namespace mt;
    std::srand( static_cast<unsigned int>( std::time( nullptr ) ) );

    std::cout<<"constructor calls in start"<<std::endl;

        strVec usaCities={ "NewYork","LosAngeles","Chicago" };
    Country state1{ "USA","Washington",9834000.0,usaCities };

        Country state2{ state1 };
    Country state3{ };

        strVec acities={ "a","b","r" };
    Country first( "A","a",150.0,acities );

        strVec bcities={ "v","b","m" };
    Country second( "B","v",100.0,bcities );

        Country* current=nullptr;
    int country_select;
        int option=-1;

    do
    {
        std::cout<<"\n=== MENU OPTIONS ==="<<std::endl;
        std::cout<<"1. Show + operator (first + second)"<<std::endl;
        std::cout<<"2. Show * operator (first * second)"<<std::endl;
        std::cout<<"3. Change country name"<<std::endl;
        std::cout<<"4. Change capital city"<<std::endl;
        std::cout<<"5. Show += operator (first += second or second += first)"<<std::endl;
        std::cout<<"6. Change territory size"<<std::endl;
        std::cout<<"7. Modify cities list"<<std::endl;
        std::cout<<"8. Display all values"<<std::endl;
        std::cout<<"9. Display full information"<<std::endl;
        std::cout<<"0. Quit program"<<std::endl;

        std::cout<<"Current status:"<<std::endl;
        std::cout<<"  Country first: "<<first.get_name()
                 <<" (capital: "<<first.get_capital()
                 <<", area: "<<first.get_area()<<")"<<std::endl;

        std::cout<<"  Country second: "<<second.get_name()
                 <<" (capital: "<<second.get_capital()
                 <<", area: "<<second.get_area()<<")"<<std::endl;

        std::cout<<"Make selection: ";
        std::cin>>option;

        if(option>=3 && option<=9)
        {
            std::cout<<"Choose country to work with:"<<std::endl;
            std::cout<<"1. Country first"<<std::endl;
            std::cout<<"2. Country second"<<std::endl;
            std::cin>>country_select;

            if(country_select==1)
            {
                current=&first;
                std::cout<<"Working with: first"<<std::endl;
            }
            else if(country_select==2)
            {
                current=&second;
                std::cout<<"Working with: second"<<std::endl;
            }
            else
            {
                std::cout<<"Wrong country selection!"<<std::endl;
                continue;
            }
        }

        switch(option)
        {
        case 1:
        {
            try{
                Country r=first+second;
                r.print_info();
            }catch(const str& e){
                std::cerr<<"Problem: "<<e<<std::endl;
            }
        }break;

        case 2:
        {
            try{
                Country p=first*second;
                p.print_info();
            }catch(const str& e){
                std::cerr<<"Problem: "<<e<<std::endl;
            }
        }break;

        case 3:
        {
            try{
                str v;
                std::cout<<"Input new name for "<<current->get_name()<<": ";
                std::cin>>v;
                current->set_name(v);
            }catch(const str& e){
                std::cerr<<"Problem: "<<e<<std::endl;
            }
        }break;

        case 4:
        {
            try{
                str v;
                std::cout<<"Input new capital for "<<current->get_name()<<": ";
                std::cin>>v;
                current->set_capital(v);
            }catch(const str& e){
                std::cerr<<"Problem: "<<e<<std::endl;
            }
        }break;

        case 5:
        {
            try{
                std::cout<<"Select for += operation:"<<std::endl;
                std::cout<<"1. first (will do first += second)"<<std::endl;
                std::cout<<"2. second (will do second += first)"<<std::endl;

                if(country_select==1)
                {
                    std::cout<<" Before first += second "<<std::endl;
                    first.print_info();
                    first+=second;
                    std::cout<<" After first += second "<<std::endl;
                    first.print_info();
                }
                else if(country_select==2)
                {
                    std::cout<<" Before second += first"<<std::endl;
                    second.print_info();
                    second+=first;
                    std::cout<<" After second += first "<<std::endl;
                    second.print_info();
                }
                else std::cout<<"Incorrect selection!"<<std::endl;
            }catch(const str& e){
                std::cerr<<"Problem: "<<e<<std::endl;
            }
        }break;

        case 6:
        {
            try{
                double v;
                std::cout<<"Input new area for "<<current->get_name()<<": ";
                std::cin>>v;
                current->set_area(v);
            }catch(const str& e){
                std::cerr<<"Problem: "<<e<<std::endl;
            }
        }break;

        case 7:
        {
            try{
                const strVec& lst=current->get_cities();
                if(lst.empty()){ std::cout<<"No cities in list. Add cities first."<<std::endl; break; }

                std::cout<<"Cities in "<<current->get_name()<<":"<<std::endl;
                for(size_t i=0;i<lst.size();++i) std::cout<<i+1<<". "<<lst[i]<<std::endl;

                size_t k;
                std::cout<<"Pick city number to modify: ";
                std::cin>>k;

                if(k<1||k>lst.size()){ std::cout<<"Invalid city number!"<<std::endl; break; }

                str nm;
                std::cout<<"Input new name for city "<<k<<": ";
                std::cin>>nm;
                current->set_city_at_index(k-1,nm);

                std::cout<<"City "<<k<<" updated to '"<<nm<<"'."<<std::endl;
                const strVec& nl=current->get_cities();
                for(size_t i=0;i<nl.size();++i) std::cout<<i+1<<". "<<nl[i]<<std::endl;
            }catch(const str& e){
                std::cerr<<"Problem: "<<e<<std::endl;
            }
        }break;

        case 8:
        {
            std::cout<<"All values for "<<current->get_name()<<std::endl;
            std::cout<<"Name: "<<current->get_name()<<std::endl;
            std::cout<<"Capital: "<<current->get_capital()<<std::endl;
            std::cout<<"Area: "<<current->get_area()<<std::endl;

            const strVec& t=current->get_cities();
            std::cout<<"Cities ("<<t.size()<<"): ";
            if(t.empty()) std::cout<<"empty";
            else for(size_t i=0;i<t.size();++i){ std::cout<<t[i]; if(i<t.size()-1) std::cout<<", "; }
            std::cout<<std::endl;
        }break;

        case 9:
            current->print_info();
            break;

        case 0:
            std::cout<<"Program termination"<<std::endl;
            break;

        default:
            std::cout<<"Invalid option"<<std::endl;
        }

    } while(option!=0);

    return 0;
}

// g++ main.cpp Country.cpp -o main && ./main