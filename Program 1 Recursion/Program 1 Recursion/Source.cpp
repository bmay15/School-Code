using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

int RecurFib(int n);
int IterFib(int n);

void main(void) 
{
	string userFile;
	int fibInput;

	cout << "What is the name of the file you want to retrieve data from?" << endl;
	getline(cin, userFile);
	
	ifstream myfile;
	myfile.open(userFile);
	assert(myfile);

	cout << "Recursion" << endl;
	cout << "N          Fib" << endl;
	
	while (myfile.eof() != true) {

		myfile >> fibInput;

		cout << fibInput << "          " << RecurFib(fibInput) << endl;

	}
	
	myfile.close();
	myfile.open(userFile);
	assert(myfile);

	cout << "\nNoncursion" << endl;
	cout << "N          Fib" << endl;

	while (myfile.eof() != true) {

		myfile >> fibInput;

		cout << fibInput << "          " << IterFib(fibInput) << endl;

	}


	system("PAUSE");
}

int RecurFib(int n)
{
	if (n <= 0) {
		return 0;
	}

	else if (n == 1 || n == 2) {
		return 1;
	}

	else {
		return RecurFib(n-2) + RecurFib(n-1);
	}
}

int IterFib(int n)
{
	if (n <= 0) {
		return 0;
	}

	else if (n == 1 || n == 2) {
		return 1;
	}
	
	else {
		int firstSum = 1;
		int secondSum = 1;
		int newSum = 0;
		
		for (int i = 3; i <= n; i++) {
			newSum = firstSum + secondSum;
			firstSum = secondSum;
			secondSum = newSum;
		}

		return newSum;
	}
}


