
#include "Header.h";

void main(void) {

	cout << "Bryson May" << endl;
	cout << "CS 2420" << endl;
	cout << "Program 2 - Linked Lists" << endl;
	cout << endl;

	string userFile;
	int fileData;
	Sing_List singList;
	Doub_List doubList;

	cout << "Enter the file name you would like to use: ";
	getline(cin, userFile);

	cout << endl;

	ifstream myfile;
	myfile.open(userFile);
	assert(myfile);

	

	while (myfile >> fileData) {

		//cout << fileData << endl;
		singList.Insert(fileData);
		//cout << singList.GetEnd()->GetData() << endl;

	}

	myfile.close();

	//for-loop that moves through the Sing_List
	//With each iteration, do what you wrote in Notepad
	//Once you exit the loop, use Traverse() methods to print both Lists

	for (Sing_Node* cursor = singList.GetHead(); cursor != nullptr; cursor = cursor->GetNext()) {
		Doub_Node* newDoubNode = new Doub_Node(cursor->GetData());
		doubList.Insert(newDoubNode);
	}

	cout << "Single-Linked List contents:" << endl;
	singList.Traverse();

	cout << endl;

	cout << "Double-Linked List contents:" << endl;
	doubList.Traverse();


	system("PAUSE");
}
