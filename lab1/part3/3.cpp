/* Yen-Jung Lu
 * COEN79 lab1 part3
 * 04/08/2022
 */

#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<iomanip>

using namespace std;

/* This function convert the uppercase and display all the words from an input file 
 * length of at least 10 characters. All punctuation marks removed and do not contribute */
int main(int argc,const char *argv[])
{
	if(argc!=2){  // check is there enough argument or not
	
	cout<< "Please enter two arguments\n";

	return 1;
	}

	string word;
	ifstream file;   // input file

	file.open(argv[1]); // open the file

	int i=0;
	
	while(file>> word){

		for(i=0; i<word.length();i++)
		{
			if(ispunct(word[i]))
			{
				word.erase(i,1);
			}

		}
 		if(word.length()>9)
		{
			for(i=0;i<word.length();i++)
			{
				word[i]=toupper(word[i]);
		
			}
		
			cout<< word << endl;
		}
	
	}
}
