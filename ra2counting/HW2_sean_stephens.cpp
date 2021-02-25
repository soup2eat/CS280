/* Sean Stephens
CS 280-002
Recitation Assignment 2
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

//Returns true if string meets integer requirements and false otherwise
bool intCheck(string xyz);
//Seperates string into parts and increments if there's a word
int countWords(string xyz);
//Seperates string into parts and increments if there's an integer
int countInt(string xyz);
//Returns true if string is a word
bool wordCheck(string xyz);
//Counts number of non-blank lines
int countNonBlank(string xyz);


int main(){

int TlineCount = -1;
int nonBlank = 0;
int wordCount = 0;
int intCount = 0;
string fileName;
ifstream fileObj;
string str;


cout << "Enter the name of a file to read from: \n";
cin >> fileName;
fileObj.open("./TestCases/" + fileName);

if (!fileObj.is_open()){
    cerr << "File could not be opened "  << fileName << endl;
    exit(1);
}

while (!fileObj.eof()){

getline(fileObj,str);
 intCount += countInt(str);
 wordCount += countWords(str);
 nonBlank += countNonBlank(str);
 TlineCount++;
}

fileObj.close();

cout << "Total Number of Lines: " << TlineCount << endl;
cout << "Number of non-blank lines: " << nonBlank <<endl;
cout << "Number of Words: " << wordCount <<endl;
cout << "Number of Integers: " << intCount << endl;


    return 0;
} //End of main


//Function definitions


bool intCheck(string xyz){

    if (!isdigit(xyz[1])){
    return false;
}

    int strLength = xyz.length(); 

    if (strLength == 1){
          if (!isdigit(xyz[0])){
        return false; 

}
    }   
    if (strLength == 0) 
    return false;    
    for(int i = 0; i <= strLength; i++){
        if (isalpha(xyz[i])){
            return false;
        }
        else if (xyz[i] == '.'){
            return false;
        }
        else if (xyz[i]== ' ')
            return false;
        }
        return true;
    }

int countInt(string xyz){
    int x = xyz.length();
    int counter = 0;
    string temp = "";
    for(int i = 0; i <= x; i++){
        if (isdigit(xyz[i])){
            temp += xyz[i];
        }
        else if (xyz[i] == '+'){
            temp += xyz[i];
        }
        else if (xyz[i] == '-'){
        temp += xyz[i];
        }
        else if (xyz[i] == '.'){
            temp += xyz[i];
        }
       else {
           if (intCheck(temp)){
           counter++;
           temp = "";
           }
           else
           {
             temp = "";
           }
            
       }
    }

return counter;
}
    
int countWords(string xyz){
     int x = xyz.length();
     int counter = 0;
     string temp = "";

     for (int i = 0;i < x; i++){
         if(isspace(xyz[i])){
             if (wordCheck(temp)){
                 counter++;
                 temp = "";
             }
             else {
 
                 temp = "";
             }
         }
         else{
             temp += xyz[i];
    
                }
         }
         if (wordCheck(temp)){
             counter++;
         }
     return counter;
}

bool wordCheck(string xyz){
    int x = xyz.length();

    if (x == 0)
    return false;

    if (x == 1){
        if (isspace(xyz[0]))
        return false;
    }

    for(int i = 0; i < x; i++){
        if(!isspace(xyz[i])){
            return true;
        }
        if (isalnum(xyz[i]))
        return true;
    }
return true;
}
int countNonBlank(string xyz){
    int x = xyz.length();
    int counter = 0;

    for(int i = 0; i<x;i++){
        if (!xyz.empty()){
            counter++;
        break;
        }
        
    }
    return counter;
}