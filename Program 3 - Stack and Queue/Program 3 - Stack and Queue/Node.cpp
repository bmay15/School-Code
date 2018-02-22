#include "Node.h"



Node::Node()
{

}

Node::Node(int n)
{
	data = n;
}


Node::~Node()
{
}

int Node::GetData()
{
	return data;
}

Node * Node::GetNext()
{
	return next;
}

void Node::SetNext(Node* nxt)
{
	next = nxt;
}
