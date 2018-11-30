//Values to be passed into the functions
var numRows = 8;
var numCols = 8;
var divId = "tableDiv";
var blueTile = "BlueCell";
var greenTile = "GreenCell";


//Generates a blank grid
function genGrid(rows, columns){

	var myTable = "<table>";   //Holds entire table

	//Iterates through each row
	for(var i = 0; i < rows; i++){

		var currRow = i;
		var row = currRow.toString();
		myTable += "<tr>";

		//Iterates through each column and adds contents to myTable
		//Each cell has a unique Id to mark its position on the grid
		for(var j = 0; j < columns; j++){

			var currCol = j;
			var column = currCol.toString();
			myTable += "<td id=R" + row + "C" + column + " data-row=" + row + " data-column=" + column + " data-check-chip='0'></td>";

		}

		myTable += "</tr>"

	}

	myTable += "</table>";
	return myTable;
}

//Sets the class of each cell so it can have the appropriate coloring
function setClasses(rows, columns, blue, green){

	for(var i = 0; i < rows; i++){

		var currRow = i;
		var row = currRow.toString();

		for(var j = 0; j < columns; j++){

			//Generates and stores the target cell's id so it can be altered
			var currCol = j;
			var column = currCol.toString();
			var cellId = "R" + row + "C" + column;
			var cell = document.getElementById(cellId);

			//Alters the cell's class based on whether the first tile of the row
			//was blue or green
			if(i % 2 == 1){

				if(j % 2 == 1) cell.className = blue;
				else cell.className = green;

			}

			else{

				if(j % 2 == 1) cell.className = green;
				else cell.className = blue;

			}
		}
	}
}

//Inserts previously generated table into the HTML
//Calls two helper functions
function insertTable(id, table, rows, columns, blue, green){

	var element = document.getElementById(id);  //Gets div to be altered
	element.innerHTML = table(rows, columns);   //Inserts blank table
	setClasses(rows, columns, blue, green);     //Sets css classes to color the table

}

//Finally, call the function to generate the colored table and
//display it on the web page
insertTable(divId, genGrid, numRows, numCols, blueTile, greenTile);














