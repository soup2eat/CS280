/*
 * main.cpp
 *
 * CS280 - Spring 2021
 * parser testing program
 */
#include <iostream>
#include <fstream>

#include "lex.h"
#include "parse.h"


using namespace std;

int main(int argc, char *argv[])
{
	int lineNumber = 1;

	istream *in = NULL;
	ifstream file;
		
	for( int i=1; i<argc; i++ )
    {
		string arg = argv[i];
		
		if( in != NULL ) 
        {
			cerr << "ONLY ONE FILE NAME ALLOWED" << endl;
			return 0;
		}
		else 
        {
			file.open("./PA2 Test Cases/" + arg);
			if( file.is_open() == false ) 
            {
				cerr << "CANNOT OPEN " << arg << endl;
				return 0;
			}

			in = &file;
		}
	}
    
    bool status = Prog(*in, lineNumber);
    
    if( !status )
    {
        cout << "Unsuccessful Parsing " << endl << "Number of Syntax Errors " << ErrCount() << endl;
	}
	else
    {
		cout << "Successful Parsing" << endl;
	}
}
