#pragma once
class Table
{
private:
	static const int capacity = 20;   //size of array
	int dataArr[capacity];            //array to hold values

public:
	Table();
	~Table();
	void Insert(int val);                      //Insert val into the table
	int Hash(int val);                         //Returns index where insertion will be attempted
	void ResolveCollision(int loc, int val);   //Called upon failed insertion, finds next open slot
	bool IsFull();                             //Checks if the table is full
	void Show();                               //Print contents of table
};

