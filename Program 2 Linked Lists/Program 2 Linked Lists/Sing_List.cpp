#include "Header.h";


//Default Constructor
Sing_List::Sing_List()
{
	head = nullptr;
	end = nullptr;
}


Sing_List::~Sing_List()
{
}

//Default Constructor
Sing_Node::Sing_Node()
{
	data = 0;
	next = nullptr;
}

//Parameterized Constructor - Sets data to passed in int
Sing_Node::Sing_Node(int d)
{
	data = d;
	next = nullptr;
}


Sing_Node::~Sing_Node()
{
}

//Set next
void Sing_Node::SetNext(Sing_Node * nxt)
{
	next = nxt;
}

//Get next
Sing_Node* Sing_Node::GetNext()
{
	return next;
}

int Sing_Node::GetData()
{
	return data;
}

//Inserts a new Node onto the end of the List
void Sing_List::Insert(int d)
{
	//Check for empty List
	if (head == nullptr) {
		head = new Sing_Node(d);
		end = head;
	} 

	else {
		//List isn't empty, so add a new Node to the end with given value
		end->SetNext(new Sing_Node(d));
		//Set end to point to the new last Node
		end = end->GetNext();
	}
}

Sing_Node* Sing_List::GetHead()
{
	return head;
}

Sing_Node* Sing_List::GetEnd()
{
	return end;
}

void Sing_List::Traverse()
{
	for (Sing_Node* cursor = head; cursor != nullptr; cursor = cursor->GetNext()) {
		cout << cursor->GetData() << endl;
	}
}
