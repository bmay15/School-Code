#include "Header.h"


int insert(string[], int, string);
bool isCity(string[], int, string);
int cityIndex(string[], int, string);
bool isFull(int[], int, int);
bool markIsFull(string[], int);
void shortestPaths(string[], int[][8], int[][8], const int, int, string);
void printDirectPaths(string[], int[][8], int[][8], const int, int);

void main() {

	ifstream myFile;
	string inFile;
	cout << "Please enter the name of data file  ";
	cin >> inFile;
	myFile.open(inFile);

	//Check that file opened correctly
	if (myFile.fail()) {
		cout << "Error opening " << inFile << endl;
		return;
	}

	const int size = 8;             //Assumed necessary size for graphs
	int miles[size][size];          //Graph for miles
	int costs[size][size];          //Graph for costs
	int infinity = 5000;

	//Initialize all elements in graphs to infinity
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			miles[i][j] = infinity;
			costs[i][j] = infinity;
		}
	}

	string airports[size];  //Array to hold airport abbreviations

	//Initialize all elements in the array to whitespace
	for (int i = 0; i < size; i++) {
		airports[i] = " ";
	}

	string departure, destination;
	int mile, cost;
	int i, j;
	while (myFile >> departure >> destination >> mile >> cost) {

		i = insert(airports, size, departure);    //Insert departure into the array and store index
		j = insert(airports, size, destination);  //Insert destination into the array and store index
		miles[i][j] = mile;                       //Insert mile into graph where i and j correspond
		costs[i][j] = cost;                       //Insert cost into graph where i and j correspond

	}
	myFile.close();

	printDirectPaths(airports, costs, miles, size, infinity);

	string source;
	cout << "Please enter a source city: " << endl;
	cin >> source;
	
	//Breaks whole program, need to handle incorrect input
	if (!isCity(airports, size, source)) {
		cout << "Invalid input" << endl;
		return;
	}
	
	shortestPaths(airports, miles, costs, size, infinity, source);


	system("PAUSE");

}

//Inserts new airports into the airports array
//Returns the index where the new airport was inserted
//If the airport already exists, just return it's index
int insert(string airports[], int size, string newAP) {

	int i = 0;

	while (i < size) {

		if (airports[i] == " ") {
			airports[i] = newAP;
			return i;
		}
		else if (airports[i] == newAP) {
			return i;
		}
		 
		i++;
	}

}

//Checks if abbreviation given for city is a valid input
bool isCity(string airports[], int size, string city) {

	for (int i = 0; i < size; i++) {

		if (airports[i] == city) {
			return true;
		}

	}
	return false;
}

//Returns the index of a city's abbreviation
int cityIndex(string airports[], int size, string city) {

	for (int i = 0; i < size; i++) {

		if (airports[i] == city) {
			return i;
		}

	}
}

//Checks to see if distance[] is full
bool isFull(int distance[], int size, int infinity) {

	for (int i = 0; i < size; i++) {
		if (distance[i] == infinity) {
			return false;
		}
	}
	return true;
}

//Checks to see if marked[] is full
bool markIsFull(string marked[], int size) {

	for (int i = 0; i < size; i++) {
		if (marked[i] == " ") {
			return false;
		}
	}
	return true;
}

//Finds the shortest path from a source airport to every other airport
//Records the paths in a graph
//Records total miles and cost in arrays
//Outputs Best Price Report
void shortestPaths(string airports[], int miles[][8], int costs[][8], const int size, int infinity, string source)
{
	const int size1 = 8;
	int distance[size1];          //Track total costs to each destination
	int totMiles[size1];          //Track total mileage to each destination
	int shortPaths[size1][size1];  //Track shortest paths by cost
	int marked[size1];            //Mark vertices so they're only evaluated once

	int start = cityIndex(airports, size, source);  //Index of source city

	//Initialize arrays and graph
	for (int i = 0; i < size; i++) {
		distance[i] = infinity;
		totMiles[i] = infinity;
		marked[i] = infinity;

		for (int j = 0; j < size; j++) {
			shortPaths[i][j] = infinity;
		}
	}

	//Initialize the first index for all paths to the start index
	for (int i = 0; i < size; i++) {
		shortPaths[i][0] = start;
	}

	distance[start] = 0;  //Starting distance is zero
	totMiles[start] = 0;  //Starting mileage is zero

	while (!(isFull(distance, size, infinity))) {

		int lowest = infinity;
		int lowIndex;

		//Find the closest unevaluated vertex to source
		for (int i = 0; i < size; i++) {

			if (distance[i] < lowest && marked[i] == infinity) {
				lowIndex = i;
				lowest = distance[lowIndex];
			}
		}

		//Check and update distance array for each possible destination of lowIndex
		for (int i = 0; i < size; i++) {

			//if there is a value
			if (costs[lowIndex][i] != infinity) {

				//if that element in distance is empty, fill it and
				//update shortPaths
				if (distance[i] == infinity) {
					distance[i] = distance[lowIndex] + costs[lowIndex][i];
					totMiles[i] = totMiles[lowIndex] + miles[lowIndex][i];

					//Copy the shortest path to previous vertex into the
					//Shortest path for the i vertex
					for (int j = 0; j < size; j++) {
						shortPaths[i][j] = shortPaths[lowIndex][j];
					}

					//Add i vertex onto the end of its own shortest path
					for (int j = 0; j < size; j++) {
						if (shortPaths[i][j] == infinity) {
							shortPaths[i][j] = i;
							break;
						}
					}

				}
				//if total distance to the vertex is less than it's existing
				//distance, then we have a new path, update paths
				else if (costs[lowIndex][i] + distance[lowIndex] < distance[i]) {

					distance[i] = distance[lowIndex] + costs[lowIndex][i];
					totMiles[i] = totMiles[lowIndex] + miles[lowIndex][i];

					//Copy the shortest path to previous vertex into the
					//Shortest path for the i vertex
					for (int k = 0; k < size; k++) {
						shortPaths[i][k] = shortPaths[lowIndex][k];
					}

					//Add i vertex onto the end of its own shortest path
					for (int k = 0; k < size; k++) {
						if (shortPaths[i][k] == infinity) {
							shortPaths[i][k] = i;
							break;
						}

					}

				}//End else-if

			}//End if

			 //Update marked array
			marked[lowIndex] = lowIndex;

		}//End of updating distances and shortest paths

			
	}//End while

	
	//Finally, output Best Price Report
	cout << "\n********Best Price Report********" << endl;
	cout << "                                         Connecting Flight Information" << endl;
	cout << "Source     Dest     Cost     Mileage     Src  Dest  Cost  Mileage" << endl;
	cout << "------------------------------------------------------------------" << endl;

	//Cycle through all airports
	for (int i = 0; i < size; i++) {

		//Skip going from start to start
		if (i != start) {

			//Output full trip totals
			cout << airports[start] << "       " << airports[i] << "       " << distance[i] << "        " << totMiles[i] << "        ";

			int j = 0;

			//Loop through shortPaths graph
			while(j < size && shortPaths[i][j + 1] != infinity){

				int depart = shortPaths[i][j];
				int arrive = shortPaths[i][j + 1];

				//Output each connecting flight
				if (j == 0) {
					cout << airports[depart] << "-->" << airports[arrive] << "  ";
					cout << costs[depart][arrive] << "  " << miles[depart][arrive] << endl;
				}
				else {
					cout << "                                            " << airports[depart] << "-->" << airports[arrive] << "  ";
					cout << costs[depart][arrive] << "  " << miles[depart][arrive] << endl;
				}
				

				j++;
			} //End while

		}//End if
		 
	}//End for

}

//Outputs all the direct paths read in from the text file alphabetically
void printDirectPaths(string airports[], int costs[][8], int miles[][8], const int size, int infinity) {

	cout << "********Direct Paths********" << endl;

	const int size1 = 8;
	string marked[size1];

	for (int i = 0; i < size; i++) {
		marked[i] = " ";
	}


	while (!(markIsFull(marked, size))) {

		int lowIndex = 0;
		string lowest = "ZZZ";

		//Pick the next airport alphabetically
		for (int i = 0; i < size; i++) {

			if (airports[i] < lowest && marked[i] == " ") {
				lowIndex = i;
				lowest = airports[i];
			}
		}

		//Output all direct flights from chosen airport
		for (int i = 0; i < size; i++) {

			//if there is a value, output stats
			if (costs[lowIndex][i] != infinity) {

				cout << airports[lowIndex] << "  " << airports[i] << " ";
				cout << miles[lowIndex][i] << "  " << costs[lowIndex][i] << endl;

			}

		}

		//Update marked array
		marked[lowIndex] = airports[lowIndex];

	}//End while

}