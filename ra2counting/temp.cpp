#include <iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include <cstdlib>
using namespace std;

int main() {
  ifstream myFile;
  string filename, str, word;
  int lineCount = 0, nonBlankLineCount = 0, wordCount = 0, integerCount = 0, i = 0;
  bool isInt = true;

  cout << "Enter the name of a file to read from: ";
  cin >> filename;

  myFile.open("./TestCases/" + filename);

  if (!myFile) {
    cout << "File could not be opened" << filename << endl;
    exit(1);
  }
  lineCount = 1;
  while (getline(myFile, str)) {
    lineCount++;
    if (str.length() != 0){
      nonBlankLineCount++;
    }
    str += "\n";
    istringstream ss(str);
    ss >> word;
    while (ss.good()) {
      wordCount++;
      i = 0;
      if (i == 0 && (isdigit(word.at(0)) || word[0] == '-' || word[0] == '+')) {
        isInt = true;
        i++;
      }
      while (i < word.length() && isInt) {
        if (!isdigit(word[i])) {
          isInt = false;
          break;
        }
        i++;
      }
      if (word.length() == 1 && !isdigit(word[0])){
        integerCount--;
      }
      ss >> word;
    }
  }

  cout << "Total Number of Lines: " << lineCount << endl;
  cout << "Number of non-blank lines: " << nonBlankLineCount << endl; 
  cout << "Number of Words: " << wordCount << endl;
  cout << "Number of Integers: " << integerCount << endl;

  return 0; 
}