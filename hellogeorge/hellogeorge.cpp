/*Student Name: Sean Stephens
Section Number: CS 280-002
Assignment Title: Recitation Assignment 1 */

#include <iostream>
#include <string>
using namespace std;

int main() {
	string firstname,lastname;
	cout << "Welcome to CS 280.\nWhat is your name?" << endl;
	cin >> firstname >> lastname;
	cout << "Hello, " + firstname + " " + lastname <<endl;
	return 0;
}