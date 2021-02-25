/*
Sean Stephens
Recitation Assignment 4
CS 280
*/

#include <iostream>
#include <fstream>
#include <map>
#include <cctype>

void digMax(const std::map<char,int> &Map, int &counter);
void letMax(const std::map<char,int> &Map, int &counter);

int main(int argv, char* argc[]){
std::ifstream myFile;
std::string fileText;
std::string type = ".txt";
std::map<char, int> charMap;
std::map<char,int>::iterator it;
int nonAlnumCount = 0; int digitCount = 0; int letterCount = 0;


if (argv >= 2){
    myFile.open(argc[1] + type);
    if (!myFile.is_open()){
        std::cerr << "File cannot be opened: " << argc[1] << std::endl;
        exit(1);
    }
}
else{
    std::cerr << "No file is found" << std::endl;
    exit(1);
}



while (myFile >> fileText)
for(int i = 0; i < fileText.length(); i++){
    charMap[toupper(fileText[i])]++;
}

if (charMap.empty()){
    std::cout << "File is empty." << std::endl;
    return 0;
}

digMax(charMap, digitCount);
letMax(charMap, letterCount);

std::cout << "List of characters seen in the file and their number of occurrences:" << std::endl;
for (it = charMap.begin(); it != charMap.end(); it++){
        std::cout << it ->first << ": " <<it->second <<std::endl;
        if (!isalnum(it->first)) nonAlnumCount++;
}
std::cout << "Number of non-alphanumeric characters seen in the file: " << nonAlnumCount <<std::endl;

}

void digMax(const std::map<char,int> &Map, int &counter){
    for (auto it: Map)
if (isdigit(it.first) && (it.second > counter)) counter = it.second;

for (auto it: Map){
if (isdigit(it.first) && (it.second == counter))
std::cout << "Digits of Largest number of occurrences: " <<it.first << ": " << it.second <<std::endl;
}
}

void letMax(const std::map<char,int> &Map, int &counter){
      for (auto it: Map)
if (isalpha(it.first) && (it.second > counter)) counter = it.second;

for (auto it: Map){
if (isalpha(it.first) && (it.second == counter))
std::cout << "Letters of Largest number of occurrences: " <<it.first << ": " << it.second <<std::endl;
}
}