#include "Header.h"

Node::Node()
{
}


Node::~Node()
{
	data = 0;
	height = 1;
	balance = 0;
	parent = nullptr;
	leftChild = nullptr;
	rightChild = nullptr;
}

Node::Node(int n)
{
	data = n;
	height = 1;
	balance = 0;
	parent = nullptr;
	leftChild = nullptr;
	rightChild = nullptr;
}

int Node::GetData()
{
	return data;
}

int Node::GetBalance()
{
	return balance;
}

int Node::GetHeight()
{
	return height;
}

Node * Node::GetParent()
{
	return parent;
}

Node * Node::GetLChild()
{
	return leftChild;
}

Node * Node::GetRChild()
{
	return rightChild;
}

void Node::SetData(int dat)
{
	data = dat;
}

void Node::SetBalance(int bal)
{
	balance = bal;
}

void Node::SetHeight(int high)
{
	height = high;
}

void Node::SetParent(Node * newParent)
{
	parent = newParent;
}

void Node::SetLChild(Node * babyNode)
{
	leftChild = babyNode;
}

void Node::SetRChild(Node * babyNode)
{
	rightChild = babyNode;
}

bool Node::IsLeaf()
{
	if (leftChild == nullptr && rightChild == nullptr) {
		return true;
	}
	return false;
}


Tree::Tree()
{
	rootPtr = nullptr;
}


Tree::~Tree()
{
}

Node* Tree::GetRoot()
{
	return rootPtr;
}

void Tree::Insert(int n)
{
	Node* insertNode = new Node(n);   //creates new node

	if (rootPtr == nullptr) {    //checks for empty tree
		rootPtr = insertNode;
	}

	else {
		DeepInsert(insertNode, rootPtr);
		CheckTreeHeight();
		CheckTreeBalance();
		BalanceTree();
	}
}

void Tree::DeepInsert(Node * newNode, Node * current)
{
	if (newNode->GetData() == current->GetData()) {
		//do nothing, don't insert duplicates
	}
	else if (newNode->GetData() < current->GetData()) {  //Compares values, looking less than

		if (current->GetLChild() == nullptr) {  //checks for empty slot, inserts if true
			current->SetLChild(newNode);
			newNode->SetParent(current);
			CheckTreeHeight();
			CheckTreeBalance();
		}
		else {
			DeepInsert(newNode, current->GetLChild());  //if not empty, calls the function on child
		}

	}
	else if (newNode->GetData() > current->GetData()) {   //Compares values, looking for greater than

		if (current->GetRChild() == nullptr) {   //checks for empty slot, inserts if true
			current->SetRChild(newNode);
			newNode->SetParent(current);
			CheckTreeHeight();
			CheckTreeBalance();
		}
		else {
			DeepInsert(newNode, current->GetRChild());   //if not empty, calls the function on child
		}

	}

}

void Tree::CheckTreeHeight()
{
	if (rootPtr == nullptr) {
		//do nothing
	}

	else {
		int LRootHeight = CheckNodeHeight(rootPtr->GetLChild());  //store height of left subtree
		int RRootHeight = CheckNodeHeight(rootPtr->GetRChild());  //store height of right subtree

		if (LRootHeight > RRootHeight)
			rootPtr->SetHeight(LRootHeight + 1);
		else
			rootPtr->SetHeight(RRootHeight + 1);
	}
}

int Tree::CheckNodeHeight(Node * current)
{
	if (current == nullptr) {
		return 0;
	}

	else if (current->IsLeaf()) {  //checks to see if Node is a leaf
		current->SetHeight(1);
		return current->GetHeight();
	}

	else {
		int LHeight = CheckNodeHeight(current->GetLChild());   //store height of left subtree
		int RHeight = CheckNodeHeight(current->GetRChild());   //store height of right subtree
		 
		//Check to see which height is higher, as well as make sure the heights only get adjusted
		//when the difference is greater than 1 to prevent errors.
		//Else it just returns the current heights.
		if (LHeight > RHeight) {
			if (current->GetHeight() - LHeight != 1) {
				current->SetHeight(LHeight + 1);
			}
			return current->GetHeight();
		}

		else {
			if (current->GetHeight() - RHeight != 1) {
				current->SetHeight(RHeight + 1);
			}
			return current->GetHeight();
		}
	}
}

void Tree::CheckTreeBalance()
{
	if (rootPtr == nullptr) {
		//do nothing
	}
	else {
		CheckNodeBalance(rootPtr);
	}
}

void Tree::CheckNodeBalance(Node * current)
{
	//Base case, if current is a leaf just set the balance to 0
	if (current->IsLeaf()) {
		current->SetBalance(0);
	}
	
	//if there is a left child but no right child, set current balance to the height of the left child
	//Call CheckNodeBalance on the left child
	else if (current->GetLChild() != nullptr && current->GetRChild() == nullptr) {
		current->SetBalance(current->GetLChild()->GetHeight());
		CheckNodeBalance(current->GetLChild());
	}

	//if there is a right child but no left child, set current balance to the height of the right child
	//Call CheckNodeBalance on the right child
	else if (current->GetLChild() == nullptr && current->GetRChild() != nullptr) {
		current->SetBalance(0 - current->GetRChild()->GetHeight());
		CheckNodeBalance(current->GetRChild());
	}
	
	//if current has both children, set current balance to the height of the left minus the height of the right
	//Call CheckNodeBalance on both of them
	else if (current->GetLChild() != nullptr && current->GetRChild() != nullptr) {
		current->SetBalance(current->GetLChild()->GetHeight() - current->GetRChild()->GetHeight());
		CheckNodeBalance(current->GetLChild());
		CheckNodeBalance(current->GetRChild());

	}
}

void Tree::BalanceTree()
{
	if (rootPtr == nullptr) {
		//do nothing
	}
	else if (rootPtr->IsLeaf()) {
		//do nothing
	}
	else {
		BalanceNode(rootPtr);
	}
}

//If the balance is outside of the acceptable range, move in the appropriate direction
//Look for the first node that has an acceptable balance and take the appropriate action
void Tree::BalanceNode(Node * current)
{
	if (current->GetBalance() > 1) {
		BalanceNode(current->GetLChild());
	}

	else if (current->GetBalance() < -1) {
		BalanceNode(current->GetRChild());
	}

	else if (current != rootPtr) {

		if (current->GetBalance() == 1 && current->GetParent()->GetBalance() == 2) {

			if (current->GetParent() == rootPtr) {
				current->SetRChild(rootPtr);
				rootPtr->SetParent(current);
				rootPtr->SetLChild(nullptr);
				rootPtr = current;
				current->SetParent(nullptr);
				CheckTreeHeight();
				CheckTreeBalance();

			}

			else {
				current->SetRChild(current->GetParent());
				current->SetParent(current->GetParent()->GetParent());
				current->GetRChild()->SetParent(current);
				current->GetRChild()->SetLChild(nullptr);
				current->GetParent()->SetLChild(current);
				CheckTreeHeight();
				CheckTreeBalance();
			}

		}

		else if (current->GetBalance() == 1 && current->GetParent()->GetBalance() == -2) {

			if (current->GetParent() == rootPtr) {
				rootPtr->SetRChild(current->GetLChild());
				current->GetLChild()->SetParent(rootPtr);
				current->SetParent(current->GetLChild());
				current->SetLChild(nullptr);
				current->GetParent()->SetRChild(current);
				CheckTreeHeight();
				CheckTreeBalance();
				BalanceNode(current->GetParent());
			}

			else {
				current->GetLChild()->SetParent(current->GetParent());
				current->GetParent()->SetRChild(current->GetLChild());
				current->SetParent(current->GetLChild());
				current->SetLChild(nullptr);
				CheckTreeHeight();
				CheckTreeBalance();
				BalanceNode(current->GetParent());
			}


		}

		else if (current->GetBalance() == -1 && current->GetParent()->GetBalance() == 2) {

			if (current->GetParent() == rootPtr) {
				rootPtr->SetLChild(current->GetRChild());
				current->GetRChild()->SetParent(rootPtr);
				current->SetParent(current->GetRChild());
				current->SetRChild(nullptr);
				current->GetParent()->SetLChild(current);
				CheckTreeHeight();
				CheckTreeBalance();
				BalanceNode(current->GetParent());
			}

			else {
				current->GetRChild()->SetParent(current->GetParent());
				current->GetParent()->SetRChild(current->GetRChild());
				current->SetParent(current->GetRChild());
				current->SetLChild(nullptr);
				CheckTreeHeight();
				CheckTreeBalance();
				BalanceNode(current->GetParent());
			}
		}

		else if (current->GetBalance() == -1 && current->GetParent()->GetBalance() == -2) {

			if (current->GetParent() == rootPtr) {
				current->SetLChild(rootPtr);
				rootPtr->SetParent(current);
				rootPtr->SetRChild(nullptr);
				rootPtr = current;
				current->SetParent(nullptr);
				CheckTreeHeight();
				CheckTreeBalance();

			}
			else {

				current->SetLChild(current->GetParent());
				current->SetParent(current->GetParent()->GetParent());
				current->GetLChild()->SetParent(current);
				current->GetLChild()->SetRChild(nullptr);
				current->GetParent()->SetRChild(current);
				CheckTreeHeight();
				CheckTreeBalance();
			}
		}

		else {
			//do nothing
		}
	}
}

void Tree::InorderPrint(Node* current)
{

	if (current != nullptr) {

		InorderPrint(current->GetLChild());
		cout << current->GetData() << endl;
		InorderPrint(current->GetRChild());

	}

}

void Tree::PreorderPrint(Node* current)
{

	if (current != nullptr) {

		cout << current->GetData() << endl;
		InorderPrint(current->GetLChild());
		InorderPrint(current->GetRChild());

	}

}
