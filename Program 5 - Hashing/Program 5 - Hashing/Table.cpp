#include "Header.h"



Table::Table()
{
	//Initilize all elements of the array to -999
	for (int i = 0; i < 20; i++) {
		dataArr[i] = -999;
	}

}


Table::~Table()
{
}

void Table::Insert(int val)
{
	int key = Hash(val);  //First index to attempt insertion

	if (IsFull()) {  //Check if table is full
		cout << "Table is full" << endl;
	}
	else {
		
		//if element is available, innsert new value
		if (dataArr[key] == -999) {
			dataArr[key] = val;
		}
		//Collision case
		else {
			cout << "Collision detected at location " << key << " for value " << val << endl;
			ResolveCollision(key, val);
		}
	}
}

int Table::Hash(int val)
{
	return val % 20;
}

void Table::ResolveCollision(int loc, int val)
{
	
	while (true) {  //Run until val is successfully stored

		loc = (loc + 1) % 20;  //Store next index to be checked

			if (dataArr[loc] == -999) {  //Check availability
				dataArr[loc] = val;      //Store val
				break;                   //break loop
		}

	}
}

bool Table::IsFull()
{
	for (int i = 0; i < 20; i++) {  //Run through each element in array

		if (dataArr[i] == -999) {   //If an empty one is found, return false immediately
			return false;
		}
	}
	
	return true;  //No empty elements found, return true
}

void Table::Show()
{
	cout << "HASH TABLE CONTENTS" << endl;
	cout << "Elements          Value" << endl;

	for (int i = 0; i < 20; i++) {
		cout << i << "               " << dataArr[i] << endl;   //Print all elements
	}

}
