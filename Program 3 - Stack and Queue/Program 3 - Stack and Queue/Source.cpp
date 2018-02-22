#include "Header.h"



void main() {

	Queue MyQueue;
	Stack MyStack;
	string userFile;
	string userIn;

	cout << "Bryson May" << endl;
	cout << "CS 2420" << endl;
	cout << "Program 3 - Stack and Queue" << endl;
	cout << endl;

	while (userIn != "n") {
		cout << "\nPlease enter a file name: " << endl;

		cin >> userFile;  //Get the name of the file the user wants to open

		cout << "Operation     Stack     Value     Result" << endl;

		ifstream myFile;
		myFile.open(userFile);
		assert(myFile);

		while (!(myFile.eof())) {

			string command;
			myFile >> command;

			if (command == "pop") {
				MyStack.pop();                  //Remove the top Node from the Stack
			}
			else if (command == "serve") {
				MyQueue.serve();                //Remove the front Node from the Queue
			}
			else if (command == "push") {
				myFile >> command;
				int input = stoi(command);      //Convert command from a string to an int
				MyStack.push(input);            //Pass input into push() function to add it to Stack
			}
			else if (command == "append") {
				myFile >> command;
				int input = stoi(command);      //Convert command from a string to an int
				MyQueue.append(input);          //Pass input into append() function to add it to Queue
			}
		}

		MyStack.print();  //Output contents of Stack
		MyQueue.print();  //Output contents of Queue

		cout << "\nWould you like to evaluate another file? (enter y for yes, or n to terminate the program)" << endl;
		cin >> userIn;

	}
	
	system("PAUSE");
}