#pragma once
#include "Header.h";


//Double-linked Node class
class Doub_Node
{
	int data;                            //Int read in from file
	Doub_Node* prev;                     //Pointer to prvious Node
	Doub_Node* next;                     //Pointer to next Node
public:
	Doub_Node();                         //Default Constructor
	Doub_Node(int d);                    //Parameterized Constructor
	~Doub_Node();                        //Destructor
	int GetData();
	Doub_Node* GetPrev();
	Doub_Node* GetNext();
	void SetData(int d);
	void SetPrev(Doub_Node* p);
	void SetNext(Doub_Node* n);
};


//Double-linked List class
class Doub_List
{
private:
	Doub_Node* head;
	Doub_Node* end;
public:
	Doub_List();                            //Default Constructor
	~Doub_List();                           //Destructor
	void Insert(Doub_Node* newNode);        //Searches for the appropriate place to put a new Node and inserts it there
	Doub_Node* GetHead();
	Doub_Node* GetEnd();
	void Traverse();                        //Iterate through the Nodes in the List and print the data stored in them
};


