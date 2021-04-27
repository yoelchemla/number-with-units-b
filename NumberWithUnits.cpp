#include "NumberWithUnits.hpp"
#include <map>
#include <iostream>
#include <fstream>
using namespace std;
using namespace ariel;

const double EPSILON = 0.00001;  //define a final variable

namespace ariel{
            static map<string,map<string,double>> con; // a map
           

     NumberWithUnits :: NumberWithUnits(double value, const string & ans){
        con.at(ans); // check if ans in the map.
        this->size = value;
        this->unit = ans;
    }


    double conversion(double value, const string& src, const string& dst){
        if(src == dst) 
        {
            return value;
        }
        if(con[src][dst] == 0)
        {
            throw invalid_argument{"unmatch, impssible to change from - ["+src+"] to ["+dst+"]"};
        }
        return value * con[src][dst];
    };

    void NumberWithUnits ::read_units(ifstream& units_file){
        double number_1=0; 
        double number_2=0;
        string u1, u2, eq;
        while(units_file >> number_1 >> u1 >> eq >> number_2 >> u2){

            con[u1][u2] = number_2;
            con[u2][u1]= number_1/number_2;
            
            // Update u1
            for(auto &pair : con[u1]) {
                double v = con[u2][u1] * pair.second;
                con[u2][pair.first] = v;
                con[pair.first][u2] = 1/v;
            }
            // Update u2
            for(auto &pair : con[u2]) {
                double v = con[u1][u2] * pair.second;
                con[u1][pair.first] = v;
                con[pair.first][u1] = 1/v;
            }
        }
    }
  void NumberWithUnits :: print(){

        for(auto& u1 : con){// for each on u1
            for (auto& u2 : u1.second)// for each on u2
            {
               cout<< u1.first << "  " << u2.first << "  "<<u2.second<< endl;
            }
        }
    }

//the operators:

 NumberWithUnits& NumberWithUnits::operator++(){// pre 
        ++(this->size);
        return *this;
}
NumberWithUnits& NumberWithUnits::operator--(){ //pre
     --(this->size);
     return *this ;
} 
NumberWithUnits NumberWithUnits::operator++(int n){ // post
      return NumberWithUnits((this->size)++, this->unit);
}
NumberWithUnits NumberWithUnits:: operator--(int n){//post
    return NumberWithUnits((this->size)--, this->unit);
}

////
NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& n2) {
        double change = conversion(n2.size, n2.unit, this->unit);
        NumberWithUnits res(this->size + change, this->unit);
        return res;
}
NumberWithUnits NumberWithUnits:: operator-(const NumberWithUnits& n2){
         double change = conversion(n2.size, n2.unit, this->unit);
        NumberWithUnits res(this->size - change, this->unit);
        return res;
}
NumberWithUnits& NumberWithUnits:: operator+=(const NumberWithUnits& num1){
    this->size+= conversion(num1.size, num1.unit, this->unit);
    return *this;;
}
NumberWithUnits& NumberWithUnits:: operator-=(const NumberWithUnits& num1){
    this->size-= conversion(num1.size, num1.unit, this->unit);
    return *this;
}
  NumberWithUnits NumberWithUnits::operator+(){
        NumberWithUnits res(+this->size , this->unit);
        return res;
}
NumberWithUnits NumberWithUnits:: operator-(){
    NumberWithUnits res(-this->size, this->unit);
    return res;
}

////
NumberWithUnits operator*(const double num1, const NumberWithUnits& num2){
    return NumberWithUnits(num2.size*num1, num2.unit);
}
NumberWithUnits operator*(const NumberWithUnits& num2,const double num1){
    return NumberWithUnits(num2.size*num1, num2.unit);
}
 NumberWithUnits& NumberWithUnits:: operator*=(double num){
      this->size*=num;
        return *this;
}


////
bool operator==(const NumberWithUnits& num1, const NumberWithUnits& num2){
    return (abs(num1.size- conversion(num2.size, num2.unit, num1.unit)) <= EPSILON);
}
bool operator!=(const NumberWithUnits& num1, const NumberWithUnits& num2){
    return !(num1==num2);
}
bool operator<(const NumberWithUnits& num1, const NumberWithUnits& num2){
    return (num1.size < conversion(num2.size, num2.unit, num1.unit));
 
}
bool operator<=(const NumberWithUnits& num1, const NumberWithUnits& num2){
    return ((num1<num2) || (num1==num2));
}
bool operator>(const NumberWithUnits& num1, const NumberWithUnits& num2){
    return !(num1<num2)&&(!(num1==num2));
}
bool operator>=(const NumberWithUnits& num1, const NumberWithUnits& num2){
    return (num1>num2 || num1==num2);
}



std::ostream& operator<< (std::ostream& output, const NumberWithUnits& c){
    output << c.size << "[" << c.unit << ']';
        return output;
}
 
std::istream &operator>>(std::istream &is, NumberWithUnits &n) {// check
        double val=0;
        std::string type;
        char c=' ';
        is >> val;
        is >> c ;
        while(c!=']'){
            if(c!='['){
                type.insert(type.end(),c);
            }
            is>>c;
        }
       if(con[type].empty()){throw invalid_argument{"unit doesnt exist"};};
        n.size=val;
        n.unit=type;
        return is;
    }

}