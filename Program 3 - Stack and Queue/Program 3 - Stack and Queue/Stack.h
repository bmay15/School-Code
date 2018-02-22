#pragma once
#include "Header.h"
#include "Node.h"

class Stack
{
private:
	Node* top;

public:
	Stack();
	~Stack();
	void push(int n);   //Add a Node to the Stack
	void pop();         //Remove a Node from the Stack
	void print();       //Output contents of Stack
};

