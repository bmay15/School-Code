#include "Header.h"


void main() {

	cout << "Bryson May" << endl;
	cout << "CS 2420" << endl;
	cout << "Program 4 - Binary Search Tree" << endl;
	cout << endl;

	string anotherFile;

	while (anotherFile != "n") {  //Loop for multiple files

		Tree test;
		string userFile; //File to be read in

		cout << "\nPlease enter a file name: " << endl;

		cin >> userFile;

		cout << "Values extraced from file: " << endl;

		ifstream myFile;
		myFile.open(userFile);
		assert(myFile);

		while (!(myFile.eof())) {       //Run until end of file

			int inputVal;               //Value to add to Tree

			myFile >> inputVal;         //Get value

			cout << inputVal << endl;   //Output value
			test.Insert(inputVal);      //Insert value into Tree

		}

		cout << "Inorder Traversal Output: " << endl;
		test.InorderPrint(test.GetRoot());  //Print Inorder values

		cout << "Preorder Traversal Output: " << endl;
		test.PreorderPrint(test.GetRoot()); //Print Preorder values

		cout << "\nWould you like to evaluate another file? (enter y for yes, or n to terminate the program)" << endl;
		cin >> anotherFile;
	}

	system("PAUSE");

}