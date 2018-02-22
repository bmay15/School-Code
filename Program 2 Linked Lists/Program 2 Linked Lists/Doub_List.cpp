#include "Header.h";



Doub_List::Doub_List()
{
}


Doub_List::~Doub_List()
{
}

void Doub_List::Insert(Doub_Node* newNode)
{
	if (head == nullptr) {
		head = newNode;
		end = head;
	}
	else {
		Doub_Node* marker = head;

		for (Doub_Node* cursor = head; cursor != nullptr; cursor = cursor->GetNext()) {
			if (cursor->GetData() <= newNode->GetData() && marker->GetData() <= cursor->GetData()) {
				marker = cursor;
			}
		}

		if (marker->GetNext() == nullptr) {
			marker->SetNext(newNode);
			newNode->SetPrev(marker);
		}
		else if (marker == head) {
			if (marker->GetData() < newNode->GetData()) {
				marker->GetNext()->SetPrev(newNode);
				newNode->SetNext(marker->GetNext());
				marker->SetNext(newNode);
				newNode->SetPrev(marker);
			}
			else {
				newNode->SetNext(marker);
				marker->SetPrev(newNode);
				head = newNode;
			}
		}
		else {
			marker->GetNext()->SetPrev(newNode);
			newNode->SetNext(marker->GetNext());
			marker->SetNext(newNode);
			newNode->SetPrev(marker);
		}
	}	
}

Doub_Node * Doub_List::GetHead()
{
	return head;
}

Doub_Node * Doub_List::GetEnd()
{
	return end;
}

void Doub_List::Traverse()
{
	for (Doub_Node* cursor = head; cursor != nullptr; cursor = cursor->GetNext()) {
		cout << cursor->GetData() << endl;
	}
}


Doub_Node::Doub_Node()
{
	data = 0;
	next = nullptr;
	prev = nullptr;
}

Doub_Node::Doub_Node(int d)
{
	data = d;
	next = nullptr;
	prev = nullptr;
}


Doub_Node::~Doub_Node()
{
}

int Doub_Node::GetData()
{
	return data;
}

Doub_Node * Doub_Node::GetPrev()
{
	return prev;
}

Doub_Node * Doub_Node::GetNext()
{
	return next;
}

void Doub_Node::SetData(int d)
{
	data = d;
}

void Doub_Node::SetPrev(Doub_Node * p)
{
	prev = p;
}

void Doub_Node::SetNext(Doub_Node * n)
{
	next = n;
}
