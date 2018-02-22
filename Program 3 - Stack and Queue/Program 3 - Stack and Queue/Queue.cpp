#include "Header.h"



Queue::Queue()
{

}


Queue::~Queue()
{
}

void Queue::append(int n)
{
	Node* newNode = new Node(n);

	//Check for empty Queue, if so, make front and rear both point to new Node
	if (front == nullptr) {
		front = newNode;
		rear = newNode;
		cout << "Append     Queue     " << n << "     Success" << endl;
	}

	//Add new Node to rear
	else {
		rear->SetNext(newNode);
		rear = newNode;
		cout << "Append     Queue     " << n << "     Success" << endl;
	}
}

void Queue::serve()
{
	//Check for empty Queue, output error message
	if (front == nullptr) {
		cout << "Serve     Queue     ---     Underflow" << endl;
	}

	//Delete front Node
	else {
		Node* delNode = front;
		front = front->GetNext();
		delete delNode;
		cout << "Serve     Queue     ---     Success" << endl;
	}
}

void Queue::print()
{
	Node* cursor = front;

	cout << "\nQueue:" << endl;

	while (cursor != nullptr) {             //Iterate through Queue until end is reached
		cout << cursor->GetData() << endl;  //Output data stored in Node pointed to by cursor
		cursor = cursor->GetNext();         //Move cursor forward one Node (or to nullptr)
	}
}
