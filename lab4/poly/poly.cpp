/*  Yen-Jung Lu

    COEN79 - LAB4 - poly.cpp

    04/29/2022

*/


#include <iostream>
#include <cassert>
#include <cmath>                
#include "poly.h"
#include <climits>             
#include <iomanip>

using namespace std;

namespace coen79_lab4 {
    
    // Constructor: creates a polynomial of all zero coefficients except for c with specified exponent
    polynomial::polynomial(double c, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        for(int i = 0; i < CAPACITY; i++) {
            data[i] = 0;
        }
        data[exponent] = c;
    }
    
    // Sets the coefficient for the specified exponent
    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        data[exponent] = coefficient;
    }
    
    // Adds amount to existing coefficient at exponent
    void polynomial::add_to_coef(double amount, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        data[exponent] += amount;
    }

    // All coefficients of `this` polynomial are set to zero
    void polynomial::clear() {
        for(int i = 0; i < CAPACITY; i++) {
            data[i] = 0;
        }
    }
    
    // Return value is the antiderivative of the polynomial
    polynomial polynomial::antiderivative() const {
        assert(degree() < MAXIMUM_DEGREE);          
        polynomial a(0,0);                          
        a.data[0] = 0;                              
        for(int i = 0; i < MAXIMUM_DEGREE; i++) {   
            a.data[i+1] = (data[i]/(i+1));
        }
        return a;
    }
    
    // Returns coefficient at specified exponent
    double polynomial::coefficient(unsigned int exponent) const {
        if(exponent > MAXIMUM_DEGREE)               
            return 0;
        else
            return data[exponent];                  
    }
    
    // Returns the value of the definite integral from x0 to x1
    double polynomial::definite_integral(double x0, double x1) const {
        double upper, lower = 0.0;                
        polynomial a;                              
        a = antiderivative();                       
        for(int i = 0; i < MAXIMUM_DEGREE; i++) {   
            lower += (a.data[i] * pow(x0,i));     
            upper += (a.data[i] * pow(x1,i));      
        }
        return upper - lower;                     
    }
    
    // Returns the highest exponent with a nonzero coefficient
    unsigned int polynomial::degree() const {
        for(int i = CAPACITY-1; i >= 0; i--) {  
            if(data[i] != 0)
                return i;
        }
        return 0;                              
    }
    
    // Returns the polynomial of the first derivative of polynomial `this`
    polynomial polynomial::derivative() const {
        polynomial a;                                  
        for(int i = 1; i < MAXIMUM_DEGREE; ++i) {       
            a.data[i-1] = (data[i] * i);                
        }
        return a;
    }
    
    // Returns the value of the polynomial for given x
    double polynomial::eval(double x) const {
        double sum = 0.0;
        for(int i = 0; i < CAPACITY; i++) {
            sum += (data[i] * pow(x, i));
        }
        return sum;
    }

    // Returns true when polynomial is all zero
    bool polynomial::is_zero() const {
        for(int i = 0; i < MAXIMUM_DEGREE; i++) {
            if(data[i] != 0) {
                return false;                   
            }
        }
        return true;                            
    }
    
    // Returns the next exponent that is larger than e with nonzero coefficient
    unsigned int polynomial::next_term(unsigned int e) const {
        for(int i = e+1; e < MAXIMUM_DEGREE; i++) {       
            if(data[i] != 0)                        
                    return i;                       
        }
        return 0;                                   
    }
    
    // Returns the next exponent that is smaller than e with nonzero coefficient
    unsigned int polynomial::previous_term(unsigned int e ) const {
        for(int i = e-1; i >= 0; i--) {             
            if(data[i] != 0)                        
                return i;                           
        }
        return UINT_MAX;                           
    }

    // Same as eval member function
    double polynomial::operator()(double x) const {
        return eval(x);                             
    }
    
    /* NON MEMBER BINARY OPERATORS */

    // Returns a polynomial with each coefficient equal to p1+p2
    polynomial operator+(const polynomial& p1, const polynomial& p2) {
        polynomial tmp;                                                 
        for(int i = 0; i < polynomial::CAPACITY; i++)                   
            tmp.assign_coef(p1.coefficient(i)+p2.coefficient(i), i);    
        return tmp;
    }
    
    // Returns a polynomial with each coefficient equal to p1-p2
    polynomial operator-(const polynomial& p1, const polynomial& p2) {
        polynomial tmp;
        for(int i = 0; i < polynomial::CAPACITY; i++)
            tmp.assign_coef(p1.coefficient(i)-p2.coefficient(i), i);    
        return tmp;
    }
    
    // Returns a polynomial with each polynomial multiplication
    polynomial operator*(const polynomial& p1, const polynomial& p2) {
        assert( (p1.degree() + p2.degree()) <= polynomial::MAXIMUM_DEGREE);  
        polynomial tmp;                                                      
        for(int i = 0; i <= p1.degree(); i++)
            for(int j = 0; j <= p2.degree(); j++)
                tmp.add_to_coef(p1.coefficient(i)*p2.coefficient(j), i+j); 
        return tmp;
    }
    
    // Nonmember output function
    // The polynomial is printed to ostream which has specific formatting
    std::ostream& operator<<(ostream& out, const polynomial& p) {
        unsigned int i = p.degree();
        streamsize s = out.precision();
        out << fixed;
        out << setprecision(1);
        for(int i = p.degree(); i >= 0; i--) {              
            if(p.degree() == 0) 
                out << p.coefficient(0);
            else if(p.coefficient(i) != 0) {        
                if(i == p.degree())                             
                    out << p.coefficient(i) << "x^" << i << ' ';   
                else if(i < p.degree() && i > 1) {              
                    if(p.coefficient(i) < 0)
                        out << "- ";                            
                    else    
                        out << "+ ";                            
                    out << fabs(p.coefficient(i)) << "x^" << i << ' ';   
                }
                else if(i == 1) {
                    if(p.coefficient(i) < 0)
                        out << "- ";                           
                    else
                        out << "+ ";                           
                    out << fabs(p.coefficient(i)) << "x ";            
                }
                else if(i == 0) {
                    if(p.coefficient(i) < 0)
                        out << "- ";                            
                    else
                        out << "+ ";                            
                    out << fabs(p.coefficient(i));                    
                }
            }
        }
        out.unsetf(ios_base::floatfield);
        out << setprecision(s);
        return out;
    }
}
