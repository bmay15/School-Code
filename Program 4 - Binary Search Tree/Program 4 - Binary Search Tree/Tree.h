#pragma once
#include "Header.h"

class Node
{
private:
	int data;            //Store value
	int height;          //Height of node from nearest leaf
	int balance;         //Balance of Node (Height of left subtree - Height of right subtree)
	Node* parent;        //Pointer to Noed parent
	Node* leftChild;     //Pointer to Left Child
	Node* rightChild;    //Pointer to Right Child

public:
	Node();
	~Node();
	Node(int n);
	int GetData();
	int GetBalance();
	int GetHeight();
	Node* GetParent();
	Node* GetLChild();
	Node* GetRChild();
	void SetData(int dat);
	void SetBalance(int bal);
	void SetHeight(int high);
	void SetParent(Node* newParent);
	void SetLChild(Node* babyNode);
	void SetRChild(Node* babyNode);
	bool IsLeaf();  //Check if this Node is a leaf

};


class Tree
{
private:
	Node* rootPtr;
	
public:
	Tree();
	~Tree(); 
	Node* GetRoot();
	void Insert(int n);                              //Insert new Node into the tree with given value
	void DeepInsert(Node* newNode, Node* current);   //Helper function for Insert
	void CheckTreeHeight();                          //Checks and adjusts height of root and calls CheckNodeHeight()
	int CheckNodeHeight(Node* current);              //Checks and adjusts height of each individual Node
	void CheckTreeBalance();                         //Checks and adjusts balance of root and calls CheckNodeBalance()
	void CheckNodeBalance(Node* current);            //Checks and adjusts balance of each individual Node
	void BalanceTree();                              //Moves Nodes around so tree is balanced
	void BalanceNode(Node* current);                 //Called by BalanceTree() to adjust each Node
	void InorderPrint(Node* current);                //Outputs stored values inorder
	void PreorderPrint(Node* current);               //Outputs stored values preorder

};

