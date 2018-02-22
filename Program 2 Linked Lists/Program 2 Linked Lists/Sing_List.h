#pragma once
#include "Header.h";

//Single-Linked Node class
class Sing_Node
{
private:
	int data;                        //Int read in from file
	Sing_Node* next;                 //Pointer to next Node
public:
	Sing_Node();                     //Constructor
	Sing_Node(int d);                //Parameterized Constructor
	~Sing_Node();                    //Destructor 
	void SetNext(Sing_Node* nxt);    
	Sing_Node* GetNext();            
	int GetData();
};

//Single-Linked List class
class Sing_List
{
private:
	Sing_Node* head;                  //Pointer to first Node in List
	Sing_Node* end;                   //Pointer to last Node in List
public:
	Sing_List();                      //Constructor
	~Sing_List();                     //Destructor
	void Insert(int d);               //Adds a new Node to the end of List
	Sing_Node* GetHead();
	Sing_Node* GetEnd();
	void Traverse();                  //Iterate through the Nodes in the List and print the data stored in them
};



