/* 
 * Yen-Jung Lu
 * COEN79 lab1 part 1
 *
 * 04/08/2022
 */



#include<iostream>
#include<cctype>
#include<string>
#include<iomanip>
#include<sstream>

using namespace std;

/* This function is in order to check the word is alphanumeric or non-alphanumeric */
int main(int argc, const char *argv[])
{
	int alphaNum; // the alphanumeric 

        int non_al;   // the non-alphanumeric characters

        alphaNum = 0;   //initialize both of them

        non_al=0;

        int i; 

        string word= "";

	cout<< "enter words"<< endl;


        getline(cin, word);  // input word in 

        int j= word.length();

        for(i=0;i<j;i++)
        {

		if(word[i]!= ' '){      // if it encounter space , it will neglect

                	if(isalnum(word[i]))
                	{	
                        	alphaNum++;
                	}

                	else if(isalnum(word[i])==0)
                	{
                        	non_al++;
                	}
        	}

	}

	cout<< "There has "<< alphaNum << " alphanumeric characters and "<< non_al<< " non-alphanumeric characters\n";
	
	return 0;


}
