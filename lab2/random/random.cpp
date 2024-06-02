/* Yen-Jung Lu
 *
 * Coen79 lab2 - random.cpp
 *  Friday lab 
 * 04/15/2022
 */

#include "random.h"
#include <iostream>
#include<stdio.h>


using namespace std;
using namespace coen79_lab2;
//this is tp implement a class that can generate a sequence 
//of  pseudorandom  integers,  which  is  a  sequence  that  appears  random  in  many 
//ways.  
namespace coen79_lab2{
    void rand_gen::set_seed(int newSeed){
        seed=newSeed;
    }
    int rand_gen::next(){
        seed=(multiplier *seed+increment) % modulus;
        
        return seed;
    }
    
    void rand_gen::print_info(){
        printf("Seed: %d\n", seed);
	printf( "Multiplier: %d\n", multiplier);
	printf("Increment:%d \n", increment);
	printf(	"Modulus:%d\n",modulus);
              
    }
}

