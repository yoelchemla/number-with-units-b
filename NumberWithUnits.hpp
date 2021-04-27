#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;
namespace ariel{
        class NumberWithUnits{
        

        private:
             double size;
             string unit;
        
         
        public:
            NumberWithUnits(double value,const string& ans);
           // {
               // size=s;
             //   unit=u;
           // }

        double getsize() const{// getter
            return size;
        };
        std::string getU() const{//getter
            return unit;
        };
            static void read_units(ifstream& units_file);
            static void print();
//operator: ++,--
            NumberWithUnits& operator++();     
            NumberWithUnits& operator--();     
            NumberWithUnits operator++(int n);          
            NumberWithUnits operator--(int n);     
            
//operator: +,=,+=,-,-=
            NumberWithUnits operator+(const NumberWithUnits& n2);
            NumberWithUnits operator-(const NumberWithUnits& n2);
            NumberWithUnits& operator+=(const NumberWithUnits& num1);
            NumberWithUnits& operator-=(const NumberWithUnits& num1);
            NumberWithUnits operator+();
            NumberWithUnits operator-();
//operator: * ,*=
            friend NumberWithUnits operator*(const double num1, const NumberWithUnits& num2);
            //friend NumberWithUnits& operator*=(NumberWithUnits& num2, double num1);
            friend NumberWithUnits operator*(const NumberWithUnits& num2,const double num1);
            NumberWithUnits& operator*=(double num);     
//operator: ==,!=,<=,>=
            friend bool operator<=(const NumberWithUnits& num1, const NumberWithUnits& num2);
            friend bool operator==(const NumberWithUnits& num1, const NumberWithUnits& num2);
            friend bool operator!=(const NumberWithUnits& num1, const NumberWithUnits& num2);
            friend bool operator>=(const NumberWithUnits& num1, const NumberWithUnits& num2);
            friend bool operator<(const NumberWithUnits& num1, const NumberWithUnits& num2);
            friend bool operator>(const NumberWithUnits& num1, const NumberWithUnits& num2);
          
         

//operator:input,output
            friend ostream& operator<< (ostream& output, const NumberWithUnits& c);
            friend istream& operator>> (istream& input , NumberWithUnits& c);


    };    
    
}