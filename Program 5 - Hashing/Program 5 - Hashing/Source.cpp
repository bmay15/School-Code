#include "Header.h"



void main() {


	string anotherFile;

	while (anotherFile != "n") {  //Loop for multiple files

		Table test;

		string userFile; //File to be read in

		cout << "\nPlease enter a file name: " << endl;

		cin >> userFile;

		cout << "Values extraced from file: " << endl;

		ifstream myFile;
		myFile.open(userFile);
		assert(myFile);

		int inputVal;

		while (myFile >> inputVal) {  //run til end of file is reached

			test.Insert(inputVal);

		}

		test.Show();  //print values

		cout << "\nWould you like to evaluate another file? (enter y for yes, or n to terminate the program)" << endl;
		cin >> anotherFile;

	}



	system("PAUSE");
}