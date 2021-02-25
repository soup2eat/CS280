/* Sean Stephens
CS 280-002
Recitation Assignment 3
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
using namespace std;

int main(int argc, char* argv[]){
    istream *in = &cin; //I create in to have it act like cin/stdin (same thing)
    ifstream file; //My file input object that I use to read from my file
    string pathName = "./RA3 Test Cases/";
    string fileText; 
    int digitCount = 0;
    int alphaCount = 0;
    int charCount = 0;
    int lineCount = 0;
    int wordCount = 0;

if (argc >= 2){ //Checks if an argument was included
    file.open(pathName + argv[1] + ".txt");
    if (file.is_open()){
    in = &file; //If an argument is included I want in to act as file input
    }
    else{
    cerr << "File could not be opened: " << argv[1] << endl;
     exit(1);}
}

//In the case that no argument is entered if statement never runs and in still acts as stdin

while (getline(*in, fileText)){ //in can either act as stdin, or file in. Either way whatever
                                //is inputted is stored in the string fileText
    lineCount++;
    charCount++;
for (int i = 0; i < fileText.length(); i++){
    charCount++;
    if (isdigit(fileText[i])) digitCount++;
    if (isalpha(fileText[i])) alphaCount++;
    if (!isspace(fileText[i]) && isspace(fileText[i+1]) ) wordCount++;
}
if (!isspace(fileText[fileText.length() - 1])) wordCount++;
}

if ((lineCount + wordCount + charCount + digitCount + alphaCount) == 0){
    cerr << "File is empty." <<endl;
    exit(1);
}
cout << "LINES: " << lineCount << endl;
cout << "WORDS: " << wordCount << endl;
cout << "CHARS: " << charCount << endl;
cout << "DIGITS: " << digitCount  << endl;
cout << "LETTERS: " << alphaCount << endl;
}