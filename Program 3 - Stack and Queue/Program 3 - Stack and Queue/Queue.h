#pragma once
#include "Header.h"
#include "Node.h"

class Queue
{
private:
	Node* front;
	Node* rear;

public:
	Queue();
	~Queue();
	void append(int n);   //Add new Node to back of Queue
	void serve();         //Remove Node from front of Queue
	void print();         //Output contents of Queue
};

