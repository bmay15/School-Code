#include "Header.h"

//Function declarations
int Count(ifstream& fileIn);
int* UnsortedArr(ifstream& fileIn, int size);
void InitializeArrs();
void InsertionSort(int usArr[], int size);
void ShellSort(int usArr[], int size);
void Partition(int usArr[], int n, int& pivotIndex);
void QuickSort(int usArr[], int n);
void SortAndTime();
void WriteOutArrs();

//Global variable declarations
ifstream myInFile;
ofstream myOutFile;
int count1;
int count2;
int count3;
int* iSorted1;
int* iSorted2;
int* iSorted3;
int* sSorted1;
int* sSorted2;
int* sSorted3;
int* qSorted1;
int* qSorted2;
int* qSorted3;

//Insertion clocks
clock_t iStart1;
clock_t iStart2;
clock_t iStart3;
clock_t iEnd1;
clock_t iEnd2;
clock_t iEnd3;
clock_t iElapsedClock1;
clock_t iElapsedClock2;
clock_t iElapsedClock3;
clock_t iElapsedTime1;
clock_t iElapsedTime2;
clock_t iElapsedTime3;

//Shell clocks
clock_t sStart1;
clock_t sStart2;
clock_t sStart3;
clock_t sEnd1;
clock_t sEnd2;
clock_t sEnd3;
clock_t sElapsedClock1;
clock_t sElapsedClock2;
clock_t sElapsedClock3;
clock_t sElapsedTime1;
clock_t sElapsedTime2;
clock_t sElapsedTime3;

//Quick clocks
clock_t qStart1;
clock_t qStart2;
clock_t qStart3;
clock_t qEnd1;
clock_t qEnd2;
clock_t qEnd3;
clock_t qElapsedClock1;
clock_t qElapsedClock2;
clock_t qElapsedClock3;
clock_t qElapsedTime1;
clock_t qElapsedTime2;
clock_t qElapsedTime3;

void main() {


	//Count the number of integers in each file and store them
	myInFile.open("p6file1.txt");
	assert(myInFile);
	count1 = Count(myInFile);
	myInFile.close();

	myInFile.open("p6file2.txt");
	assert(myInFile);
	count2 = Count(myInFile);
	myInFile.close();

	myInFile.open("p6file3.txt");
	assert(myInFile);
	count3 = Count(myInFile);
	myInFile.close();

	//Initialize 3 unsorted dynamically allocated arrays to the appropriate size
	//Fill them with the values from their corresponding file
	//Copy values from array pointers to standard arrays so they can be passed to sorting functions
	InitializeArrs();

	//Run all sorts and time them
	//Calculate elapsed clock/time
	//Output stats
	SortAndTime();

	//Write sorted arrays out to respective files
	WriteOutArrs();



	system("PAUSE");
}



//Return number of elements in a file
int Count(ifstream& fileIn) {

	int hold;
	int result = 0;

	//count number of elements in file
	while (fileIn >> hold) {
		result++;
	}

	return result;
}


//Get the original values from the file and store them in an unsorted array
int* UnsortedArr(ifstream& fileIn, int size) {

	int* OriginArr = new int[size];

	int value;
	int index = 0;

	//Read values from file into OriginArr
	while (fileIn >> value) {

		OriginArr[index] = value;
		index++;

	}

	return OriginArr;
}

void InitializeArrs() {

	//File 1 arrays
	myInFile.open("p6file1.txt");
	assert(myInFile);
	iSorted1 = UnsortedArr(myInFile, count1);  //To be Insertion Sorted
	myInFile.close();

	myInFile.open("p6file1.txt");
	assert(myInFile);
	sSorted1 = UnsortedArr(myInFile, count1);  //To be Shell Sorted
	myInFile.close();

	myInFile.open("p6file1.txt");
	assert(myInFile);
	qSorted1 = UnsortedArr(myInFile, count1);  //To be Quick Sorted
	myInFile.close();

	//File 2 arrays
	myInFile.open("p6file2.txt");
	assert(myInFile);
	iSorted2 = UnsortedArr(myInFile, count2);  //To be Insertion Sorted
	myInFile.close();

	myInFile.open("p6file2.txt");
	assert(myInFile);
	sSorted2 = UnsortedArr(myInFile, count2);  //To be Shell Sorted
	myInFile.close();

	myInFile.open("p6file2.txt");
	assert(myInFile);
	qSorted2 = UnsortedArr(myInFile, count2);  //To be Quick Sorted
	myInFile.close();

	//File 3 arrays
	myInFile.open("p6file3.txt");
	assert(myInFile);
	iSorted3 = UnsortedArr(myInFile, count3);  //To be Insertion Sorted
	myInFile.close();

	myInFile.open("p6file3.txt");
	assert(myInFile);
	sSorted3 = UnsortedArr(myInFile, count3);  //To be Shell Sorted
	myInFile.close();

	myInFile.open("p6file3.txt");
	assert(myInFile);
	qSorted3 = UnsortedArr(myInFile, count3);  //To be Quick Sorted
	myInFile.close();

}


//Insertion sort the array usArr
void InsertionSort(int usArr[], int size) {

	for (int i = 1; i < size; i++) {

		int current = usArr[i];

		for (int j = i - 1; j >= 0; j--) {

			if (current <= usArr[j]) {
				usArr[j + 1] = usArr[j];
				usArr[j] = current;
			}
			else {
				break;
			}
		}
	}
}


//Shell Sort the array usArr
 void ShellSort(int usArr[], int size) {

	int key = floor((size / 3) + 1);
	int* newArr = new int[size];  //Array to be filled with semi-sorted values, then copied back to shellArr
								  
	//Run loop until final sort
	while (key > 1) {

		int index = 0;

		for (int i = 0; i < key; i++) {

			int subSize = 0; //Tracks size of chunk in newArr to be Insertion Sorted

			//Place semi-sorted values into newArr from usArr
			//Increment subSize and index
			for (int j = i; j < size; j += key) {

				newArr[index] = usArr[j];
				subSize++;
				index++;
			}

			int start = index - subSize;  //Beginning index of subarray to be sorted
			InsertionSort(&newArr[start], subSize);  //Sort the subarray

		}

		//Copy values from newArr into shellArr to preserve progress while the while-loop iterates
		for (int i = 0; i < size; i++) {
			usArr[i] = newArr[i];
		}

		key--;
	}

	InsertionSort(usArr, size);  //Final sort

}

 void Partition(int usArr[], int n, int& pivotIndex) {

	 int holdSwap;                  //hold value being swapped
	 pivotIndex = ceil(n / 2);      //select pivot value
	 holdSwap = usArr[0];
	 usArr[0] = usArr[pivotIndex];
	 usArr[pivotIndex] = holdSwap;
	 pivotIndex = 0;
	 int tooBigIndex = 1;	       //second element
	 int tooSmallIndex = n - 1;       //last element
	 int pivot = usArr[pivotIndex]; //pivot value

	 //Run until they cross
	 while (tooBigIndex <= tooSmallIndex) {

		 //Scan for next element that is too big
		 //Break when element is found, or end of the array is reached
		 while (usArr[tooBigIndex] <= pivot && tooBigIndex < n) {
			 tooBigIndex++;
		 }

		 //Scan for next element that is too small
		 //Break when element is found or pivot is reached
		 while (usArr[tooSmallIndex] > pivot) {
			 tooSmallIndex--;
		 }

		 //If tooBigIndex is less than tooSmallIndex, then there are still more
		 //elements to be sorted, so swap the two values at the saved indices 
		 if (tooBigIndex < tooSmallIndex) {
			 holdSwap = usArr[tooBigIndex];
			 usArr[tooBigIndex] = usArr[tooSmallIndex];
			 usArr[tooSmallIndex] = holdSwap;
			 tooBigIndex++;
			 tooSmallIndex--;
		 }
	 }

	 //All elements are now sorted as either bigger or smaller than the pivot value
	 //Swap the pivot (at index 0) and the element at tooSmallIndex and adjust pivotIndex
	 usArr[0] = usArr[tooSmallIndex];
	 usArr[tooSmallIndex] = pivot;
	 pivotIndex = tooSmallIndex;

 }

 void QuickSort(int usArr[], int n)
 {
	 int pivotIndex = 0;
	 int n1;
	 int n2;

	 if (n > 1) {

		 Partition(usArr, n, pivotIndex);

		 //Calculate size of subarrays
		 int n1 = pivotIndex;
		 int n2 = n - n1 - 1;

		 //Recursive calls on subarrays
		 QuickSort(usArr, n1);
		 QuickSort((usArr + pivotIndex + 1), n2);

	 }
 }


 void SortAndTime() {

	 //Insertion Sorts
	 iStart1 = clock();
	 InsertionSort(iSorted1, count1);
	 iEnd1 = clock();
	 iElapsedClock1 = iEnd1 - iStart1;
	 iElapsedTime1 = iElapsedClock1 / CLK_TCK;

	 iStart2 = clock();
	 InsertionSort(iSorted2, count2);
	 iEnd2 = clock();
	 iElapsedClock2 = iEnd2 - iStart2;
	 iElapsedTime2 = iElapsedClock2 / CLK_TCK;

	 iStart3 = clock();
	 InsertionSort(iSorted3, count3);
	 iEnd3 = clock();
	 iElapsedClock3 = iEnd3 - iStart3;
	 iElapsedTime3 = iElapsedClock3 / CLK_TCK;


	 //Shell Sorts
	 sStart1 = clock();
	 ShellSort(sSorted1, count1);
	 sEnd1 = clock();
	 sElapsedClock1 = sEnd1 - sStart1;
	 sElapsedTime1 = sElapsedClock1 / CLK_TCK;

	 sStart2 = clock();
	 ShellSort(sSorted2, count2);
	 sEnd2 = clock();
	 sElapsedClock2 = sEnd2 - sStart2;
	 sElapsedTime2 = sElapsedClock2 / CLK_TCK;

	 sStart3 = clock();
	 ShellSort(sSorted3, count3);
	 sEnd3 = clock();
	 sElapsedClock3 = sEnd3 - sStart3;
	 sElapsedTime3 = sElapsedClock3 / CLK_TCK;

	 //Quick Sorts
	 qStart1 = clock();
	 QuickSort(qSorted1, count1);
	 qEnd1 = clock();
	 qElapsedClock1 = qEnd1 - qStart1;
	 qElapsedTime1 = qElapsedClock1 / CLK_TCK;

	 qStart2 = clock();
	 QuickSort(qSorted2, count2);
	 qEnd2 = clock();
	 qElapsedClock2 = qEnd2 - qStart2;
	 qElapsedTime2 = qElapsedClock2 / CLK_TCK;

	 qStart3 = clock();
	 QuickSort(qSorted3, count3);
	 qEnd3 = clock();
	 qElapsedClock3 = qEnd3 - qStart3;
	 qElapsedTime3 = qElapsedClock3 / CLK_TCK;

	 //Output time stats to console
	 cout << "Sort          File     Count     Clock     Time     Sorted File" << endl;
	 cout << "Insertion     p6file1  " << count1 << "        " << iElapsedClock1 << "         " << iElapsedTime1 << "        I1.txt" << endl;
	 cout << "Shellsort     p6file1  " << count1 << "        " << sElapsedClock1 << "         " << sElapsedTime1 << "        S1.txt" << endl;
	 cout << "Quicksort     p6file1  " << count1 << "        " << qElapsedClock1 << "         " << qElapsedTime1 << "        Q1.txt" << endl;
	 cout << endl;
	 cout << "Insertion     p6file2  " << count2 << "     " << iElapsedClock2 << "         " << iElapsedTime2 << "        I2.txt" << endl;
	 cout << "Shellsort     p6file2  " << count2 << "     " << sElapsedClock2 << "      " << sElapsedTime2 << "        S2.txt" << endl;
	 cout << "Quicksort     p6file2  " << count2 << "     " << qElapsedClock2 << "         " << qElapsedTime2 << "        Q2.txt" << endl;
	 cout << endl;
	 cout << "Insertion     p6file3  " << count3 << "    " << iElapsedClock3 << "      " << iElapsedTime3 << "        I3.txt" << endl;
	 cout << "Shellsort     p6file3  " << count3 << "    " << sElapsedClock3 << "    " << sElapsedTime3 << "      S3.txt" << endl;
	 cout << "Quicksort     p6file3  " << count3 << "    " << qElapsedClock3 << "        " << qElapsedTime3 << "        Q3.txt" << endl;
	 cout << endl;


 }

 void WriteOutArrs()
 {

	 //Insertion arrays to files
	 myOutFile.open("I1.txt");
	 assert(myOutFile);
	 for (int i = 0; i < count1; i++) {
		 myOutFile << iSorted1[i] << endl;
	 }
	 myOutFile.close();

	 myOutFile.open("I2.txt");
	 assert(myOutFile);
	 for (int i = 0; i < count2; i++) {
		 myOutFile << iSorted2[i] << endl;
	 }
	 myOutFile.close();

	 myOutFile.open("I3.txt");
	 assert(myOutFile);
	 for (int i = 0; i < count3; i++) {
		 myOutFile << iSorted3[i] << endl;
	 }
	 myOutFile.close();

	 //Shell arrays to files
	 myOutFile.open("S1.txt");
	 assert(myOutFile);
	 for (int i = 0; i < count1; i++) {
		 myOutFile << sSorted1[i] << endl;
	 }
	 myOutFile.close();

	 myOutFile.open("S2.txt");
	 assert(myOutFile);
	 for (int i = 0; i < count2; i++) {
		 myOutFile << sSorted2[i] << endl;
	 }
	 myOutFile.close();

	 myOutFile.open("S3.txt");
	 assert(myOutFile);
	 for (int i = 0; i < count3; i++) {
		 myOutFile << sSorted3[i] << endl;
	 }
	 myOutFile.close();

	 //Quick arrays to files
	 myOutFile.open("Q1.txt");
	 assert(myOutFile);
	 for (int i = 0; i < count1; i++) {
		 myOutFile << qSorted1[i] << endl;
	 }
	 myOutFile.close();

	 myOutFile.open("Q2.txt");
	 assert(myOutFile);
	 for (int i = 0; i < count2; i++) {
		 myOutFile << qSorted2[i] << endl;
	 }
	 myOutFile.close();

	 myOutFile.open("Q3.txt");
	 assert(myOutFile);
	 for (int i = 0; i < count3; i++) {
		 myOutFile << qSorted3[i] << endl;
	 }
	 myOutFile.close();

 }
