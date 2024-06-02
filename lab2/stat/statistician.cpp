/*  Yen-Jung Lu

    COEN79 - LAB2 - statistician.cpp

    04/15/2022
*/

#include "statistician.h"
using namespace coen79_lab2;

namespace coen79_lab2{
    
//this function is the constructor that initializes the values of the variables
statistician::statistician(){
        reset();
    }

/*This function adds an inputed number to the sequence.  It increments the length and adds the value of the element to the total sum.  It then checks if the inputed value is bigger than the current max, or smaller than the current min and changes the values if they are true.
*/
 void statistician::next(double x){
    
    seqLen++;
    seqSum += x;
    
    if (seqLen == 1) {
        seqMin = x;
        seqMax = x;
    }
    else if(x<seqMin){
        seqMin = x;
    }
    else if(x>seqMax){
        seqMax = x;
    }
}

//returns the sequence length
int statistician::length(){
    return seqLen;
}

//returns the sequence sum
double statistician::sum(){
    if (seqLen == 0) {
        return 0;
    }
    return seqSum;
}

//returns the sequence mean
double statistician::mean(){
    if (seqLen == 0) {
        return 0;
    }
    return (seqSum/seqLen);
}

//returns the largest element of the sequence
double statistician::maximum(){
    if (seqLen == 0) {
        return 0;
    }

    return seqMax;
}
//returns the smallest element of the sequence

double statistician::minimum(){
    if (seqLen == 0) {
        return 0;
    }
    return seqMin;
}

//resets the values of all the variables
void statistician::reset(){
    seqLen = 0;
    seqSum = 0.0;
    seqMin = 0.0;
    seqMax = 0.0;
}

//overloads the addition operator so that two statistician objects can be added together
statistician operator + (statistician a, statistician b){
    statistician c;
    c.seqLen = a.seqLen + b.seqLen;
    c.seqSum = a.seqSum + b.seqSum;
    
    if (a.seqMin<b.seqMin) {
        c.seqMin = a.seqMin;
    }
    else{
        c.seqMin = b.seqMin;
    }
    if (a.seqMax>b.seqMax) {
        c.seqMax = a.seqMax;
    }
    else{
        c.seqMax = b.seqMax;
    }
    return c;
    
    
}

//overloads the multiplication operator so that two statistician objects can be multiplied together
statistician operator * (double x, statistician a){
    statistician c;
    double temp = 0.0;
    c.seqLen=a.seqLen;
    c.seqSum=a.seqSum * x;
    c.seqMax=a.seqMax * x;
    c.seqMin=a.seqMin * x;
    
    if (c.seqMin>c.seqMax) {
        temp = c.seqMax;
        c.seqMax = c.seqMin;
        c.seqMin = temp;
    }
    return c;
    
}
    
//overloads the assignment operator so that a statistician object can be copied onto another object
bool operator == ( statistician &a, statistician &b){
    if(a.length()==b.length() && a.sum()==b.sum() && a.maximum()==b.maximum() && a.minimum() == b.minimum()){
        return true;
    }
    return false;
}

}

