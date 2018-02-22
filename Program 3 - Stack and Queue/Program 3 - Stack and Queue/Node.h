#pragma once

class Node
{
private:
	int data;
	Node* next = nullptr;     //Pointer to next Node in Stack/Queue

public:
	Node();
	Node(int n);
	~Node();
	int GetData();            //Return data
	Node* GetNext();          //Return next
	void SetNext(Node* nxt);  //Set next
};

