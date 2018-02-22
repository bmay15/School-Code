#include "Header.h"



Stack::Stack()
{
	top = nullptr;
}


Stack::~Stack()
{
}

void Stack::push(int n)
{
	//Check for empty Stack, if so, make new Node top
	if (top == nullptr) {
		top = new Node(n);
		cout << "Push     Stack     " << n << "     Success" << endl;
	}

	//Add new Node to front of Stack
	else {
		Node* newNode = new Node(n);
		newNode->SetNext(top);
		top = newNode;
		cout << "Push     Stack     " << n << "     Success" << endl;
	}
}

void Stack::pop()
{   
	//Check for empty Stack
 	if (top == nullptr) {  
		cout << "Pop     Stack     ---     Underflow" << endl;
	}
	
	//Remove first Node
	else {
		Node* delNode = top;
		top = top->GetNext();
		delete delNode;
		cout << "Pop     Stack     ---     Success" << endl;
	}
	
}

void Stack::print()
{
	Node* cursor = top;

	cout << "\nStack:" << endl;

	while (cursor != nullptr) {               //Iterate through Stack until the end is reached
		cout << cursor->GetData() << endl;    //Output data of the Node pointed to by cursor
		cursor = cursor->GetNext();           //Move cursor to the next Node
	}
}

