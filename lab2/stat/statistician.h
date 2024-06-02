#ifndef statistician_h
#define statistician_h

#include <stdio.h>
#include<iostream>
namespace coen79_lab2{
    
class statistician{
    
public:
    statistician();
    void next(double x);
    int length();
    double sum();
    double mean();
    double maximum();
    double minimum();
    void reset();
    friend statistician operator + (statistician, statistician);
    friend statistician operator * (double, statistician);
    private:
    int seqLen{0};
    double seqSum{0.0};
    double seqMin{0.0};
    double seqMax{0.0};
    
    
};
bool operator == ( statistician &a, statistician &b);
    


}

#endif 
