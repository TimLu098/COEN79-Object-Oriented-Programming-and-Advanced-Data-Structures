/* Yen-Jung LU
 * COEN79 lab1 part2
 * 04/08/2022
 */

#include<iostream>
#include<stdio.h>
#include<string>
#include<sstream>
#include<cctype>
#include<iomanip>

using namespace std;

void display(); 

//the main function that call the display function 
int main(int argc, const char* argv[])
{
	display();
	return 0;		

}


// this funciton display the stri1 and stri2 with order modified
void display()
{
	string stri1="0123456789";
	string stri2="9876543210";

	cout<< stri1 << endl;
	cout<< setw(stri1.length()+1) << stri2 << setw(stri1.length()+9)<< stri1<<endl;
	cout<< setw(stri1.length()+3) << stri2 << setw(stri1.length()+11)<< stri1<<endl; 
	cout<< setw(stri1.length()+5) << stri2 << setw(stri1.length()+13)<< stri1<<endl;
	cout<< setw(stri1.length()+7) << stri2 << setw(stri1.length()+15)<< stri1<<endl;
	cout<< setw(stri1.length()+9) << stri2 << setw(stri1.length()+17)<< stri1<<endl;


}
