
//-------------------------------- MODEL INITIALIZATION -------------------------------

//Global game info
var BLACK = 1;
var GREY = 2;
var BLACKKING = 3;
var GREYKING = 4;
var BLACKCHIPDIV = "<div class='BlkCircle'></div>";
var GREYCHIPDIV = "<div class='GryCircle'></div>";
var BLACKKINGDIV = "<div class='BlkCircle'>K</div>";
var GREYKINGDIV = "<div class='GryCircle'>K</div>";

//Game State object
var gameState = {
	turn: 1,
	checkArr: [[],[],[],[],[],[],[],[]],
	gameOver: false,
	blkChips: [],
	gryChips: [],
	liveBChips: 0,
	liveGChips: 0,
}

//Chip constructor
function Chip(color, possMoves, king, alive){
	this.color = color;
	this.possMoves = possMoves;
	this.king = king;
	this.alive = alive;
}

function initializeModel(){

	//Set data to starting values
	gameState.turn = 1;
	gameState.gameOver = false;
	gameState.liveBChips = 0;
	gameState.liveGChips = 0;

	//Initialize checkArr elements to 0
	for(var i = 0; i < 8; i++){
		for(var j = 0; j < 8; j++){

			gameState.checkArr[i][j] = 0;

		}
	}

	//Fill chip arrays with new Chips
	for(var i = 0; i < 12; i++){

		gameState.blkChips[i] = new Chip("black", 0, false, false);
		gameState.gryChips[i] = new Chip("grey", 0, false, false);

	}

}


//-------------------------------------- THE GAME BOARD ---------------------------------

//Places 12 chips on each side of the board
//Update model values
function startGame(){

	initializeModel();

	var grid = document.getElementsByTagName("table")[0];
	var chipNum = 0;
	var cell;
	var chip;


	//Black Chips
	for(var i = 0; i < 3; i++){
		for(var j = 0; j < 8; j++){

			cell = grid.rows[i].cells[j];

			if(i % 2 == 0){
				if(j % 2 == 1){
				cell.innerHTML = BLACKCHIPDIV;
				cell.dataset.checkChip = BLACK;
				chip = gameState.blkChips[chipNum];
				chip.alive = true;
				gameState.checkArr[i][j] = chip;
				gameState.liveBChips++;
				chipNum++;
				}
			}
			else{
				if(j % 2 == 0){
				cell.innerHTML = BLACKCHIPDIV;
				cell.dataset.checkChip = BLACK;
				chip = gameState.blkChips[chipNum];
				chip.alive = true;
				gameState.checkArr[i][j] = chip;
				gameState.liveBChips++;
				chipNum++;
				}
			}
		}//End j-for
	}//End i-for

	chipNum = 0; //Reset to iterate through gryChips[]

	//Grey Chips
	for(var i = 5; i < 8; i++){
		for(var j = 0; j < 8; j++){

			cell = grid.rows[i].cells[j];

			if(i % 2 == 0){
				if(j % 2 == 1){
				cell.innerHTML = GREYCHIPDIV;
				cell.dataset.checkChip = GREY;
				chip = gameState.gryChips[chipNum];
				chip.alive = true;
				gameState.checkArr[i][j] = chip;
				gameState.liveGChips++;
				chipNum++;
				}
			}
			else{
				if(j % 2 == 0){
				cell.innerHTML = GREYCHIPDIV;
				cell.dataset.checkChip = GREY;
				chip = gameState.gryChips[chipNum];
				chip.alive = true;
				gameState.checkArr[i][j] = chip;
				gameState.liveGChips++;
				chipNum++;
				}
			}
		}//End for
	}//End for
}

//Wipes the board and calls startGame
function resetGame(){

	var gridT = document.getElementsByTagName("table")[0];
	document.getElementById("winDiv").innerHTML = "";
	document.getElementById("errorDiv").innerHTML = "";
	document.getElementById("BlkPlayer").innerHTML = "";
	document.getElementById("GryPlayer").innerHTML = "";
	gameState.checkArr = [[],[],[],[],[],[],[],[]];
	gameState.blkChips = [];
	gameState.gryChips = [];
	gameState.liveBChips = 0;
	gameState.liveGChips = 0;
	gameState.turn = 1;

	for(var i = 0; i < 8; i++){
		for(var j = 0; j < 8; j++){
		gridT.rows[i].cells[j].innerHTML = "";
		gridT.rows[i].cells[j].dataset.checkChip = 0;
		}
	}


	startGame();
}

//------------------------------------- MOVEMENT AND GAME LOGIC ---------------------------------

//Globals for click event
var chipSelected = false; //Used to determine whether or not the user has already selected a chip to move
var prevRow;
var prevCol;
var prevCell;
var prevColor;
var prevChip;
var selectedColor = "#fcfc5f";
var firstClickMovesArr;
//Set the click handlers for all cells
//When they are clicked they toggle between two styles
function setCellClickHandlers(){

	var cells = document.getElementsByTagName("td");

	for(var i = 0; i < cells.length; i++){

		cells[i].onclick = function(){

			var row = this.dataset.row;
			var col = this.dataset.column;
			var gridTable = document.getElementsByTagName("table")[0];
			var cell = gridTable.rows[row].cells[col];
			document.getElementById("errorDiv").innerHTML = "";

			//First click
			if(chipSelected == false){

				//Black turn
				if(gameState.turn == BLACK){

					if(this.dataset.checkChip == BLACK || this.dataset.checkChip == BLACKKING){

						prevColor = this.style.background;
						prevRow = row;
						prevCol = col;
						prevCell = cell;
						prevChip = this.dataset.checkChip;
						this.style.background = selectedColor;
						chipSelected = true;
						//Call chipPossMoves and store in firstClickPossMovesArr
						var selectedChip = gameState.checkArr[this.dataset.row][this.dataset.column];
						firstClickMovesArr = chipPossMoves(selectedChip, cell);

					}
					else{
						//Error message
						document.getElementById("errorDiv").innerHTML = "ERROR: Please select a Black Chip";
					}
				}

				//Grey turn
				else{

					if(this.dataset.checkChip == GREY || this.dataset.checkChip == GREYKING){

						prevColor = this.style.background;
						prevRow = row;
						prevCol = col;
						prevCell = cell;
						prevChip = this.dataset.checkChip;
						this.style.background = selectedColor;
						chipSelected = true;
						//Call chipPossMoves and store in firstClickPossMovesArr
						var selectedChip = gameState.checkArr[this.dataset.row][this.dataset.column];
						firstClickMovesArr = chipPossMoves(selectedChip, cell);

					}
					else{
						document.getElementById("errorDiv").innerHTML = "ERROR: Please select a Grey Chip";
					}
				}
			}

			//Second click
			else{

				//Check to see if selected cell is in the firstClickPossMovesArr[]
				var validMove = false;
				var normMovesLength = firstClickMovesArr[0].length;
				var jumpMovesLength = firstClickMovesArr[1].length;

				for(var i = 0; i < normMovesLength; i++){

					if(firstClickMovesArr[0][i] == cell){

						validMove = true;

						//Black chip hitting King row
						if(cell.dataset.row == 7 && prevCell.dataset.checkChip == 1){

							cell.innerHTML = BLACKKINGDIV;
							prevCell.innerHTML = "";
							prevCell.style.background = prevColor;
							prevCell.dataset.checkChip = 0;
							this.dataset.checkChip = BLACKKING;

							gameState.checkArr[this.dataset.row][this.dataset.column] =
							gameState.checkArr[prevCell.dataset.row][prevCell.dataset.column];
							gameState.checkArr[prevCell.dataset.row][prevCell.dataset.column] = 0;
							gameState.checkArr[this.dataset.row][this.dataset.column].king = true;



							chipSelected = false;
							if(gameState.turn == BLACK) gameState.turn = GREY;
							else gameState.turn = BLACK;
							break;

						}
						//Grey chip hitting King row
						else if(cell.dataset.row == 0 && prevCell.dataset.checkChip == 2){

							cell.innerHTML = GREYKINGDIV;
							prevCell.innerHTML = "";
							prevCell.style.background = prevColor;
							prevCell.dataset.checkChip = 0;
							this.dataset.checkChip = GREYKING;

							gameState.checkArr[this.dataset.row][this.dataset.column] =
							gameState.checkArr[prevCell.dataset.row][prevCell.dataset.column];
							gameState.checkArr[prevCell.dataset.row][prevCell.dataset.column] = 0;
							gameState.checkArr[this.dataset.row][this.dataset.column].king = true;


							chipSelected = false;
							if(gameState.turn == BLACK) gameState.turn = GREY;
							else gameState.turn = BLACK;
							break;

						}
						//Normal movement
						else{

						cell.innerHTML = prevCell.innerHTML;
						prevCell.innerHTML = "";
						prevCell.style.background = prevColor;
						prevCell.dataset.checkChip = 0;
						this.dataset.checkChip = prevChip;

						gameState.checkArr[this.dataset.row][this.dataset.column] =
						gameState.checkArr[prevCell.dataset.row][prevCell.dataset.column];
						gameState.checkArr[prevCell.dataset.row][prevCell.dataset.column] = 0;

						//Need to update chipSelected no matter where they click
						chipSelected = false;
						if(gameState.turn == BLACK) gameState.turn = GREY;
						else gameState.turn = BLACK;
						break;

						}
					}
				}//End for

				//Second for-loop to test jump cells
				for(var i = 0; i < jumpMovesLength; i++){

					if(firstClickMovesArr[1][i] == cell){

						validMove = true;

						//Black chip jumping and hitting King row
						if(cell.dataset.row == 7 && prevCell.dataset.checkChip == 1){

							cell.innerHTML = BLACKKINGDIV;
							prevCell.innerHTML = "";
							prevCell.style.background = prevColor;
							prevCell.dataset.checkChip = 0;
							this.dataset.checkChip = BLACKKING;

							gameState.checkArr[this.dataset.row][this.dataset.column] =
							gameState.checkArr[prevCell.dataset.row][prevCell.dataset.column];
							gameState.checkArr[prevCell.dataset.row][prevCell.dataset.column] = 0;
							gameState.checkArr[this.dataset.row][this.dataset.column].king = true;

						    var currChip = gameState.checkArr[this.dataset.row][this.dataset.column];
						    jump(firstClickMovesArr[1][i], firstClickMovesArr[1][i-1], currChip);


							chipSelected = false;
							if(gameState.turn == BLACK) gameState.turn = GREY;
							else gameState.turn = BLACK;
							break;

						}
						//Grey chip hitting King row
						else if(cell.dataset.row == 0 && prevCell.dataset.checkChip == 2){

							cell.innerHTML = GREYKINGDIV;
							prevCell.innerHTML = "";
							prevCell.style.background = prevColor;
							prevCell.dataset.checkChip = 0;
							this.dataset.checkChip = GREYKING;

							gameState.checkArr[this.dataset.row][this.dataset.column] =
							gameState.checkArr[prevCell.dataset.row][prevCell.dataset.column];
							gameState.checkArr[prevCell.dataset.row][prevCell.dataset.column] = 0;
							gameState.checkArr[this.dataset.row][this.dataset.column].king = true;

						    var currChip = gameState.checkArr[this.dataset.row][this.dataset.column];
						    jump(firstClickMovesArr[1][i], firstClickMovesArr[1][i-1], currChip);


							chipSelected = false;
							if(gameState.turn == BLACK) gameState.turn = GREY;
							else gameState.turn = BLACK;
							break;

						}
						//Normal jump movement
						else{

						cell.innerHTML = prevCell.innerHTML;
						prevCell.innerHTML = "";
						prevCell.style.background = prevColor;
						prevCell.dataset.checkChip = 0;
						this.dataset.checkChip = prevChip;

						gameState.checkArr[this.dataset.row][this.dataset.column] =
						gameState.checkArr[prevCell.dataset.row][prevCell.dataset.column];
						gameState.checkArr[prevCell.dataset.row][prevCell.dataset.column] = 0;

						var currChip = gameState.checkArr[this.dataset.row][this.dataset.column];
						jump(firstClickMovesArr[1][i], firstClickMovesArr[1][i-1], currChip);

						chipSelected = false;
						if(gameState.turn == BLACK) gameState.turn = GREY;
						else gameState.turn = BLACK;
						break;

						}

					}

				}//End for

				if(validMove == false){
					document.getElementById("errorDiv").innerHTML = "ERROR: Invalid move";
					prevCell.style.background = prevColor;
					chipSelected = false;
				}

				firstClickMovesArr = null;

                endGame();

			}//End Second Click

		}//End onclick

	}//End for

}



function chipPossMoves(chip, cell){

	var possMovesArr = [[],[]];
	var grid = document.getElementsByTagName("table")[0];
	var cellRow = parseInt(cell.dataset.row);
	var cellCol = parseInt(cell.dataset.column);

	//Regular Black Chip
	if(cell.dataset.checkChip == BLACK){

		//if there is a left cell, and it's open, push into array
		if((cellRow + 1) < 8 && (cellCol - 1) >= 0){

			var leftCell = grid.rows[cellRow + 1].cells[cellCol - 1];
			if(leftCell.dataset.checkChip == 0) possMovesArr[0].push(leftCell);

			//if LeftCell has a Grey Chip/King, test for jump cell, push into array if open
			if(leftCell.dataset.checkChip == GREY || leftCell.dataset.checkChip == GREYKING){

				var LCellRow = parseInt(leftCell.dataset.row);
				var LCellCol = parseInt(leftCell.dataset.column);

				//if there is a jump cell, and it's open, push into array
				if((LCellRow + 1) < 8 && (LCellCol - 1) >= 0){
					var LJumpCell = grid.rows[LCellRow + 1].cells[LCellCol - 1];

					if(LJumpCell.dataset.checkChip == 0){
						possMovesArr[1].push(leftCell);
						possMovesArr[1].push(LJumpCell);
					}

				}

			}

		}
		//if there is a right cell, and it's open, push into array
		if((cellRow + 1) < 8 && (cellCol + 1) < 8){

			var rightCell = grid.rows[cellRow + 1].cells[cellCol + 1];
			if(rightCell.dataset.checkChip == 0) possMovesArr[0].push(rightCell);

			//if rightCell has a Grey Chip/King, test for jump cell, push into array if open
			if(rightCell.dataset.checkChip == GREY || rightCell.dataset.checkChip == GREYKING){

				var RCellRow = parseInt(rightCell.dataset.row);
				var RCellCol = parseInt(rightCell.dataset.column);

				//if there is a jump cell, and it's open, push into array
				if((RCellRow + 1) < 8 && (RCellCol + 1) >= 0){
					var RJumpCell = grid.rows[RCellRow + 1].cells[RCellCol + 1];
					if(RJumpCell.dataset.checkChip == 0){
						possMovesArr[1].push(rightCell);
						possMovesArr[1].push(RJumpCell);
					}

				}

			}

		}

	}
	//Regular Grey Chip
	else if(cell.dataset.checkChip == GREY){

		//if there is a left cell, and it's open, push into array
		if((cellRow - 1) >= 0 && (cellCol - 1) >= 0){

			var leftCell = grid.rows[cellRow - 1].cells[cellCol - 1];
			if(leftCell.dataset.checkChip == 0) possMovesArr[0].push(leftCell);

			//if leftCell has a Black Chip/King, check for jump cell, push into array if open
			if(leftCell.dataset.checkChip == BLACK || leftCell.dataset.checkChip == BLACKKING){

				var LCellRow = parseInt(leftCell.dataset.row);
				var LCellCol = parseInt(leftCell.dataset.column);

				//if there is a jump cell, and it's open, push into array
				if((LCellRow - 1) >= 0 && (LCellCol - 1) >= 0){
					var LJumpCell = grid.rows[LCellRow - 1].cells[LCellCol - 1];

					if(LJumpCell.dataset.checkChip == 0){
						possMovesArr[1].push(leftCell);
						possMovesArr[1].push(LJumpCell);
					}

				}

			}

		}

		//if there is a right cell, and it's open, push into array
		if((cellRow - 1) >= 0 && (cellCol + 1) < 8){

			var rightCell = grid.rows[cellRow - 1].cells[cellCol + 1];
			if(rightCell.dataset.checkChip == 0) possMovesArr[0].push(rightCell);

			//if rightCell has a Black Chip/King, test for jump cell, push into array if open
			if(rightCell.dataset.checkChip == BLACK || rightCell.dataset.checkChip == BLACKKING){

				var RCellRow = parseInt(rightCell.dataset.row);
				var RCellCol = parseInt(rightCell.dataset.column);

				//if there is a jump cell, and it's open, push into array
				if((RCellRow - 1) >= 0 && (RCellCol + 1) < 8){
					var RJumpCell = grid.rows[RCellRow - 1].cells[RCellCol + 1];
					if(RJumpCell.dataset.checkChip == 0){
						possMovesArr[1].push(rightCell);
						possMovesArr[1].push(RJumpCell);
					}

				}

			}

		}

	}
	//Black King
	else if(cell.dataset.checkChip == BLACKKING){

		//if there is a bottom left cell, and it's open, push into array
		if((cellRow + 1) < 8 && (cellCol - 1) >= 0){

			var bottomLeftCell = grid.rows[cellRow + 1].cells[cellCol - 1];
			if(bottomLeftCell.dataset.checkChip == 0) possMovesArr[0].push(bottomLeftCell);

			//if bottomLeftCell has a Grey Chip/King, test for jump cell, push into array if open
			if(bottomLeftCell.dataset.checkChip == GREY || bottomLeftCell.dataset.checkChip == GREYKING){

				var BLCellRow = parseInt(bottomLeftCell.dataset.row);
				var BLCellCol = parseInt(bottomLeftCell.dataset.column);

				//if there is a jump cell, and it's open, push into array
				if((BLCellRow + 1) < 8 && (BLCellCol - 1) >= 0){
					var BLJumpCell = grid.rows[BLCellRow + 1].cells[BLCellCol - 1];
					if(BLJumpCell.dataset.checkChip == 0){
						possMovesArr[1].push(bottomLeftCell);
						possMovesArr[1].push(BLJumpCell);
					}

				}

			}

		}
		//if there is a bottom right cell, and it's open, push into array
		if((cellRow + 1) < 8 && (cellCol + 1) < 8){

			var bottomRightCell = grid.rows[cellRow + 1].cells[cellCol + 1];
			if(bottomRightCell.dataset.checkChip == 0) possMovesArr[0].push(bottomRightCell);

			//if bottomRightCell has a Grey Chip/King, test for jump cell, push into array if open
			if(bottomRightCell.dataset.checkChip == GREY || bottomRightCell.dataset.checkChip == GREYKING){

				var BRCellRow = parseInt(bottomRightCell.dataset.row);
				var BRCellCol = parseInt(bottomRightCell.dataset.column);

				//if there is a jump cell, and it's open, push into array
				if((BRCellRow + 1) < 8 && (BRCellCol + 1) < 8){
					var BRJumpCell = grid.rows[BRCellRow + 1].cells[BRCellCol + 1];
					if(BRJumpCell.dataset.checkChip == 0){
						possMovesArr[1].push(bottomRightCell);
						possMovesArr[1].push(BRJumpCell);
					}

				}

			}

		}
		//if there is a top left cell, and it's open, push into array
		if((cellRow - 1) >= 0 && (cellCol - 1) >= 0){

			var topLeftCell = grid.rows[cellRow - 1].cells[cellCol - 1];
			if(topLeftCell.dataset.checkChip == 0) possMovesArr[0].push(topLeftCell);

			//if topLeftCell has a Grey Chip/King, test for jump cell, push into array if open
			if(topLeftCell.dataset.checkChip == GREY || topLeftCell.dataset.checkChip == GREYKING){

				var TLCellRow = parseInt(topLeftCell.dataset.row);
				var TLCellCol = parseInt(topLeftCell.dataset.column);

				//if there is a jump cell, and it's open, push into array
				if((TLCellRow - 1) >= 0 && (TLCellCol - 1) >= 0){
					var TLJumpCell = grid.rows[TLCellRow - 1].cells[TLCellCol - 1];
					if(TLJumpCell.dataset.checkChip == 0){
						possMovesArr[1].push(topLeftCell);
						possMovesArr[1].push(TLJumpCell);
					}

				}

			}

		}
		//if there is a top right cell, and it's open, push into array
		if((cellRow - 1) >= 0 && (cellCol + 1) < 8){

			var topRightCell = grid.rows[cellRow - 1].cells[cellCol + 1];
			if(topRightCell.dataset.checkChip == 0) possMovesArr[0].push(topRightCell);

			//if topRightCell has a Grey Chip/King, test for jump cell, push into array if open
			if(topRightCell.dataset.checkChip == GREY || topRightCell.dataset.checkChip == GREYKING){

				var TRCellRow = parseInt(topRightCell.dataset.row);
				var TRCellCol = parseInt(topRightCell.dataset.column);

				//if there is a jump cell, and it's open, push into array
				if((TRCellRow - 1) >= 0 && (TRCellCol + 1) < 8){
					var TRJumpCell = grid.rows[TRCellRow - 1].cells[TRCellCol + 1];
					if(TRJumpCell.dataset.checkChip == 0){
						possMovesArr[1].push(topRightCell);
						possMovesArr[1].push(TRJumpCell);
					}

				}

			}

		}

	}
	//Grey King
	else if(cell.dataset.checkChip == GREYKING){
		//if there is a bottom left cell, and it's open, push into array
		if((cellRow + 1) < 8 && (cellCol - 1) >= 0){

			var bottomLeftCell = grid.rows[cellRow + 1].cells[cellCol - 1];
			if(bottomLeftCell.dataset.checkChip == 0) possMovesArr[0].push(bottomLeftCell);

			//if bottomLeftCell has a Black Chip/King, test for jump cell, push into array if open
			if(bottomLeftCell.dataset.checkChip == BLACK || bottomLeftCell.dataset.checkChip == BLACKKING){

				var BLCellRow = parseInt(bottomLeftCell.dataset.row);
				var BLCellCol = parseInt(bottomLeftCell.dataset.column);

				//if there is a jump cell, and it's open, push into array
				if((BLCellRow + 1) < 8 && (BLCellCol - 1) >= 0){
					var BLJumpCell = grid.rows[BLCellRow + 1].cells[BLCellCol - 1];
					if(BLJumpCell.dataset.checkChip == 0){
						possMovesArr[1].push(bottomLeftCell);
						possMovesArr[1].push(BLJumpCell);
					}

				}

			}

		}
		//if there is a bottom right cell, and it's open, push into array
		if((cellRow + 1) < 8 && (cellCol + 1) < 8){

			var bottomRightCell = grid.rows[cellRow + 1].cells[cellCol + 1];
			if(bottomRightCell.dataset.checkChip == 0) possMovesArr[0].push(bottomRightCell);

			//if bottomRightCell has a Black Chip/King, test for jump cell, push into array if open
			if(bottomRightCell.dataset.checkChip == BLACK || bottomRightCell.dataset.checkChip == BLACKKING){

				var BRCellRow = parseInt(bottomRightCell.dataset.row);
				var BRCellCol = parseInt(bottomRightCell.dataset.column);

				//if there is a jump cell, and it's open, push into array
				if((BRCellRow + 1) < 8 && (BRCellCol + 1) >= 0){
					var BRJumpCell = grid.rows[BRCellRow + 1].cells[BRCellCol + 1];
					if(BRJumpCell.dataset.checkChip == 0){
						possMovesArr[1].push(bottomRightCell);
						possMovesArr[1].push(BRJumpCell);
					}

				}

			}

		}
		//if there is a top left cell, and it's open, push into array
		if((cellRow - 1) >= 0 && (cellCol - 1) >= 0){

			var topLeftCell = grid.rows[cellRow - 1].cells[cellCol - 1];
			if(topLeftCell.dataset.checkChip == 0) possMovesArr[0].push(topLeftCell);

			//if topLeftCell has a Black Chip/King, test for jump cell, push into array if open
			if(topLeftCell.dataset.checkChip == BLACK || topLeftCell.dataset.checkChip == BLACKKING){

				var TLCellRow = parseInt(topLeftCell.dataset.row);
				var TLCellCol = parseInt(topLeftCell.dataset.column);

				//if there is a jump cell, and it's open, push into array
				if((TLCellRow - 1) >= 0 && (TLCellCol - 1) >= 0){
					var TLJumpCell = grid.rows[TLCellRow - 1].cells[TLCellCol - 1];
					if(TLJumpCell.dataset.checkChip == 0){
						possMovesArr[1].push(topLeftCell);
						possMovesArr[1].push(TLJumpCell);
					}

				}

			}

		}
		//if there is a top right cell, and it's open, push into array
		if((cellRow - 1) >= 0 && (cellCol + 1) < 8){

			var topRightCell = grid.rows[cellRow - 1].cells[cellCol + 1];
			if(topRightCell.dataset.checkChip == 0) possMovesArr[0].push(topRightCell);

			//if topRightCell has a Black Chip/King, test for jump cell, push into array if open
			if(topRightCell.dataset.checkChip == BLACK || topRightCell.dataset.checkChip == BLACKKING){

				var TRCellRow = parseInt(topRightCell.dataset.row);
				var TRCellCol = parseInt(topRightCell.dataset.column);

				//if there is a jump cell, and it's open, push into array
				if((TRCellRow - 1) >= 0 && (TRCellCol + 1) < 8){
					var TRJumpCell = grid.rows[TRCellRow - 1].cells[TRCellCol + 1];
					if(TRJumpCell.dataset.checkChip == 0){
						possMovesArr[1].push(topRightCell);
						possMovesArr[1].push(TRJumpCell);
					}

				}

			}

		}

	}

	return possMovesArr;

}

function jump(currCell, deadCell, chip){

	//Remove the dead chip
	//Call this shiz when reg chips land on King Row inside if-statement
	var grid = document.getElementsByTagName("table")[0];
	var cellRow = parseInt(currCell.dataset.row);
	var cellCol = parseInt(currCell.dataset.column);
	var deadCellRow = deadCell.dataset.row;
	var deadCellCol = deadCell.dataset.column;
	var deadChip = gameState.checkArr[deadCellRow][deadCellCol];
	gameState.checkArr[deadCellRow][deadCellCol] = 0;
	deadCell.innerHTML = "";
	deadCell.dataset.checkChip = 0;
	deadChip.alive = false;
	if(deadChip.color == "black") gameState.liveBChips--;
	else gameState.liveGChips--;

	//Regular Black Chip
	if(currCell.dataset.checkChip == 1){

		if((cellRow + 1) < 8 && (cellCol - 1) >= 0){

			var leftCell = grid.rows[cellRow + 1].cells[cellCol - 1];

			//if LeftCell has a Grey Chip/King, test for jump cell
			if(leftCell.dataset.checkChip == GREY || leftCell.dataset.checkChip == GREYKING){

				var LCellRow = parseInt(leftCell.dataset.row);
				var LCellCol = parseInt(leftCell.dataset.column);

				//if there is a jump cell, and it's open, jump
				if((LCellRow + 1) < 8 && (LCellCol - 1) >= 0){
					var LJumpCell = grid.rows[LCellRow + 1].cells[LCellCol - 1];

					if(LJumpCell.dataset.checkChip == 0){

						LJumpCell.innerHTML = currCell.innerHTML;
						LJumpCell.dataset.checkChip = currCell.dataset.checkChip;
						currCell.innerHTML = "";
						currCell.dataset.checkChip = 0;

						gameState.checkArr[LJumpCell.dataset.row][LJumpCell.dataset.column] =
						gameState.checkArr[currCell.dataset.row][currCell.dataset.column];
						gameState.checkArr[currCell.dataset.row][currCell.dataset.column] = 0;

						if(LJumpCell.dataset.row == 7){
							gameState.checkArr[LJumpCell.dataset.row][LJumpCell.dataset.column].king = true;
							LJumpCell.innerHTML = BLACKKINGDIV;
							LJumpCell.dataset.checkChip = 3;

						}
						else{
						    jump(LJumpCell, leftCell, chip);
						}

					}

				}

			}

			if((cellRow + 1) < 8 && (cellCol + 1) < 8){

				var rightCell = grid.rows[cellRow + 1].cells[cellCol + 1];

				//if rightCell has a Grey Chip/King, test for jump cell
				if(rightCell.dataset.checkChip == GREY || rightCell.dataset.checkChip == GREYKING){

					var RCellRow = parseInt(rightCell.dataset.row);
					var RCellCol = parseInt(rightCell.dataset.column);

					//if there is a jump cell, and it's open, jump
					if((RCellRow + 1) < 8 && (RCellCol + 1) < 8){
						var RJumpCell = grid.rows[RCellRow + 1].cells[RCellCol + 1];

						if(RJumpCell.dataset.checkChip == 0){

							RJumpCell.innerHTML = currCell.innerHTML;
							RJumpCell.dataset.checkChip = currCell.dataset.checkChip;
							currCell.innerHTML = "";
							currCell.dataset.checkChip = 0;

							gameState.checkArr[RJumpCell.dataset.row][RJumpCell.dataset.column] =
							gameState.checkArr[currCell.dataset.row][currCell.dataset.column];
							gameState.checkArr[currCell.dataset.row][currCell.dataset.column] = 0;

							if(RJumpCell.dataset.row == 7){
								gameState.checkArr[RJumpCell.dataset.row][RJumpCell.dataset.column].king = true;
								RJumpCell.innerHTML = BLACKKINGDIV;
								RJumpCell.dataset.checkChip = 3;
						    }
						    else{
						        jump(LJumpCell, leftCell, chip);
						    }

						}

					}

				}

			}

		}

	}

	//Regular Grey Chip
	if(currCell.dataset.checkChip == 2){

		if((cellRow - 1) >= 0 && (cellCol - 1) >= 0){

			var leftCell = grid.rows[cellRow - 1].cells[cellCol - 1];

			//if LeftCell has a Black Chip/King, test for jump cell
			if(leftCell.dataset.checkChip == BLACK || leftCell.dataset.checkChip == BLACKKING){

				var LCellRow = parseInt(leftCell.dataset.row);
				var LCellCol = parseInt(leftCell.dataset.column);

				//if there is a jump cell, and it's open, jump
				if((LCellRow - 1) >= 0 && (LCellCol - 1) >= 0){
					var LJumpCell = grid.rows[LCellRow - 1].cells[LCellCol - 1];

					if(LJumpCell.dataset.checkChip == 0){

						LJumpCell.innerHTML = currCell.innerHTML;
						LJumpCell.dataset.checkChip = currCell.dataset.checkChip;
						currCell.innerHTML = "";
						currCell.dataset.checkChip = 0;

						gameState.checkArr[LJumpCell.dataset.row][LJumpCell.dataset.column] =
						gameState.checkArr[currCell.dataset.row][currCell.dataset.column];
						gameState.checkArr[currCell.dataset.row][currCell.dataset.column] = 0;

						if(LJumpCell.dataset.row == 0){
							gameState.checkArr[LJumpCell.dataset.row][LJumpCell.dataset.column].king = true;
							LJumpCell.innerHTML = GREYKINGDIV;
							LJumpCell.dataset.checkChip = 4;
						}
						else{
						    jump(LJumpCell, leftCell, chip);
						}

					}

				}

			}

			if((cellRow - 1) >= 0 && (cellCol + 1) < 8){

				var rightCell = grid.rows[cellRow - 1].cells[cellCol + 1];

				//if rightCell has a Black Chip/King, test for jump cell
				if(rightCell.dataset.checkChip == BLACK || rightCell.dataset.checkChip == BLACKKING){

					var RCellRow = parseInt(rightCell.dataset.row);
					var RCellCol = parseInt(rightCell.dataset.column);

					//if there is a jump cell, and it's open, jump
					if((RCellRow - 1) >= 0 && (RCellCol + 1) < 8){
						var RJumpCell = grid.rows[RCellRow - 1].cells[RCellCol + 1];

						if(RJumpCell.dataset.checkChip == 0){

							RJumpCell.innerHTML = currCell.innerHTML;
							RJumpCell.dataset.checkChip = currCell.dataset.checkChip;
							currCell.innerHTML = "";
							currCell.dataset.checkChip = 0;

							gameState.checkArr[RJumpCell.dataset.row][RJumpCell.dataset.column] =
							gameState.checkArr[currCell.dataset.row][currCell.dataset.column];
							gameState.checkArr[currCell.dataset.row][currCell.dataset.column] = 0;

							if(RJumpCell.dataset.row == 0){
								gameState.checkArr[RJumpCell.dataset.row][RJumpCell.dataset.column].king = true;
								RJumpCell.innerHTML = GREYKINGDIV;
								RJumpCell.dataset.checkChip = 4;
							}
							else{

							    jump(RJumpCell, rightCell, chip);

							}

						}

					}

				}

			}

		}

	}
	//Black King
	if(currCell.dataset.checkChip == 3){

		//Bottom Left
		if((cellRow + 1) < 8 && (cellCol - 1) >= 0){

			var leftCell = grid.rows[cellRow + 1].cells[cellCol - 1];

			//if LeftCell has a Grey Chip/King, test for jump cell
			if(leftCell.dataset.checkChip == GREY || leftCell.dataset.checkChip == GREYKING){

				var LCellRow = parseInt(leftCell.dataset.row);
				var LCellCol = parseInt(leftCell.dataset.column);

				//if there is a jump cell, and it's open, jump
				if((LCellRow + 1) < 8 && (LCellCol - 1) >= 0){
					var LJumpCell = grid.rows[LCellRow + 1].cells[LCellCol - 1];

					if(LJumpCell.dataset.checkChip == 0){

						LJumpCell.innerHTML = currCell.innerHTML;
						LJumpCell.dataset.checkChip = currCell.dataset.checkChip;
						currCell.innerHTML = "";
						currCell.dataset.checkChip = 0;

						gameState.checkArr[LJumpCell.dataset.row][LJumpCell.dataset.column] =
						gameState.checkArr[currCell.dataset.row][currCell.dataset.column];
						gameState.checkArr[currCell.dataset.row][currCell.dataset.column] = 0;

						jump(LJumpCell, leftCell, chip);

					}

				}

			}

		}

		//Bottom Right
		if((cellRow + 1) < 8 && (cellCol + 1) < 8){

			var rightCell = grid.rows[cellRow + 1].cells[cellCol + 1];

			//if rightCell has a Grey Chip/King, test for jump cell
			if(rightCell.dataset.checkChip == GREY || rightCell.dataset.checkChip == GREYKING){

				var RCellRow = parseInt(rightCell.dataset.row);
				var RCellCol = parseInt(rightCell.dataset.column);

				//if there is a jump cell, and it's open, jump
				if((RCellRow + 1) < 8 && (RCellCol + 1) < 8){
					var RJumpCell = grid.rows[RCellRow + 1].cells[RCellCol + 1];

					if(RJumpCell.dataset.checkChip == 0){

						RJumpCell.innerHTML = currCell.innerHTML;
						RJumpCell.dataset.checkChip = currCell.dataset.checkChip;
						currCell.innerHTML = "";
						currCell.dataset.checkChip = 0;

						gameState.checkArr[RJumpCell.dataset.row][RJumpCell.dataset.column] =
						gameState.checkArr[currCell.dataset.row][currCell.dataset.column];
						gameState.checkArr[currCell.dataset.row][currCell.dataset.column] = 0;

						jump(RJumpCell, rightCell, chip);

					}

				}

			}

		}

		//Top Left
		if((cellRow - 1) >= 0 && (cellCol - 1) >= 0){

			var leftCell = grid.rows[cellRow - 1].cells[cellCol - 1];

			//if LeftCell has a Grey Chip/King, test for jump cell
			if(leftCell.dataset.checkChip == GREY || leftCell.dataset.checkChip == GREYKING){

				var LCellRow = parseInt(leftCell.dataset.row);
				var LCellCol = parseInt(leftCell.dataset.column);

				//if there is a jump cell, and it's open, jump
				if((LCellRow - 1) >= 0 && (LCellCol - 1) >= 0){

					var LJumpCell = grid.rows[LCellRow - 1].cells[LCellCol - 1];

					if(LJumpCell.dataset.checkChip == 0){

						LJumpCell.innerHTML = currCell.innerHTML;
						LJumpCell.dataset.checkChip = currCell.dataset.checkChip;
						currCell.innerHTML = "";
						currCell.dataset.checkChip = 0;

						gameState.checkArr[LJumpCell.dataset.row][LJumpCell.dataset.column] =
						gameState.checkArr[currCell.dataset.row][currCell.dataset.column];
						gameState.checkArr[currCell.dataset.row][currCell.dataset.column] = 0;

						jump(LJumpCell, leftCell, chip);

					}

				}

			}

		}

		//Top Right
		if((cellRow - 1) >= 0 && (cellCol + 1) < 8){

		    var rightCell = grid.rows[cellRow - 1].cells[cellCol + 1];

			//if rightCell has a Grey Chip/King, test for jump cell
			if(rightCell.dataset.checkChip == GREY || rightCell.dataset.checkChip == GREYKING){

				var RCellRow = parseInt(rightCell.dataset.row);
				var RCellCol = parseInt(rightCell.dataset.column);

				//if there is a jump cell, and it's open, jump
				if((RCellRow - 1) >= 0 && (RCellCol + 1) < 8){
					var RJumpCell = grid.rows[RCellRow - 1].cells[RCellCol + 1];

					if(RJumpCell.dataset.checkChip == 0){

						RJumpCell.innerHTML = currCell.innerHTML;
						RJumpCell.dataset.checkChip = currCell.dataset.checkChip;
						currCell.innerHTML = "";
						currCell.dataset.checkChip = 0;

						gameState.checkArr[RJumpCell.dataset.row][RJumpCell.dataset.column] =
						gameState.checkArr[currCell.dataset.row][currCell.dataset.column];
						gameState.checkArr[currCell.dataset.row][currCell.dataset.column] = 0;

				    	jump(RJumpCell, rightCell, chip);

					}

				}

			}

		}

	}

    //Grey King
	if(currCell.dataset.checkChip == 4){

    	//Bottom Left
    	if((cellRow + 1) < 8 && (cellCol - 1) >= 0){

    		var leftCell = grid.rows[cellRow + 1].cells[cellCol - 1];

    		//if LeftCell has a Black Chip/King, test for jump cell
   			if(leftCell.dataset.checkChip == BLACK || leftCell.dataset.checkChip == BLACKKING){

    			var LCellRow = parseInt(leftCell.dataset.row);
    			var LCellCol = parseInt(leftCell.dataset.column);

    			//if there is a jump cell, and it's open, jump
    			if((LCellRow + 1) < 8 && (LCellCol - 1) >= 0){
    				var LJumpCell = grid.rows[LCellRow + 1].cells[LCellCol - 1];

    				if(LJumpCell.dataset.checkChip == 0){

    					LJumpCell.innerHTML = currCell.innerHTML;
    					LJumpCell.dataset.checkChip = currCell.dataset.checkChip;
    					currCell.innerHTML = "";
    					currCell.dataset.checkChip = 0;

    					gameState.checkArr[LJumpCell.dataset.row][LJumpCell.dataset.column] =
    					gameState.checkArr[currCell.dataset.row][currCell.dataset.column];
    			    	gameState.checkArr[currCell.dataset.row][currCell.dataset.column] = 0;

    					jump(LJumpCell, leftCell, chip);

    				}

    			}

    		}

    	}

    	//Bottom Right
    	if((cellRow + 1) < 8 && (cellCol + 1) < 8){

    		var rightCell = grid.rows[cellRow + 1].cells[cellCol + 1];

    		//if rightCell has a Black Chip/King, test for jump cell
    		if(rightCell.dataset.checkChip == BLACK || rightCell.dataset.checkChip == BLACKKING){

    			var RCellRow = parseInt(rightCell.dataset.row);
    			var RCellCol = parseInt(rightCell.dataset.column);

    			//if there is a jump cell, and it's open, jump
    			if((RCellRow + 1) < 8 && (RCellCol + 1) < 8){
    				var RJumpCell = grid.rows[RCellRow + 1].cells[RCellCol + 1];

    				if(RJumpCell.dataset.checkChip == 0){

    					RJumpCell.innerHTML = currCell.innerHTML;
    					RJumpCell.dataset.checkChip = currCell.dataset.checkChip;
    					currCell.innerHTML = "";
    					currCell.dataset.checkChip = 0;

    					gameState.checkArr[RJumpCell.dataset.row][RJumpCell.dataset.column] =
    					gameState.checkArr[currCell.dataset.row][currCell.dataset.column];
    					gameState.checkArr[currCell.dataset.row][currCell.dataset.column] = 0;

    					jump(RJumpCell, rightCell, chip);

    				}

    			}

    		}

    	}

    	//Top Left
    	if((cellRow - 1) >= 0 && (cellCol - 1) >= 0){

    		var leftCell = grid.rows[cellRow - 1].cells[cellCol - 1];

    		//if LeftCell has a Black Chip/King, test for jump cell
    		if(leftCell.dataset.checkChip == BLACK || leftCell.dataset.checkChip == BLACKKING){

    			var LCellRow = parseInt(leftCell.dataset.row);
    			var LCellCol = parseInt(leftCell.dataset.column);

    			//if there is a jump cell, and it's open, jump
    			if((LCellRow - 1) >= 0 && (LCellCol - 1) >= 0){

    				var LJumpCell = grid.rows[LCellRow - 1].cells[LCellCol - 1];

    				if(LJumpCell.dataset.checkChip == 0){

    					LJumpCell.innerHTML = currCell.innerHTML;
    					LJumpCell.dataset.checkChip = currCell.dataset.checkChip;
    					currCell.innerHTML = "";
    					currCell.dataset.checkChip = 0;

    					gameState.checkArr[LJumpCell.dataset.row][LJumpCell.dataset.column] =
    					gameState.checkArr[currCell.dataset.row][currCell.dataset.column];
    					gameState.checkArr[currCell.dataset.row][currCell.dataset.column] = 0;

    					jump(LJumpCell, leftCell, chip);

    				}

    			}

    		}

    	}

    	//Top Right
    	if((cellRow - 1) >= 0 && (cellCol + 1) < 8){

    	    var rightCell = grid.rows[cellRow - 1].cells[cellCol + 1];

    		//if rightCell has a Black Chip/King, test for jump cell
    		if(rightCell.dataset.checkChip == BLACK || rightCell.dataset.checkChip == BLACKKING){

    			var RCellRow = parseInt(rightCell.dataset.row);
    			var RCellCol = parseInt(rightCell.dataset.column);

    			//if there is a jump cell, and it's open, jump
    			if((RCellRow - 1) >= 0 && (RCellCol + 1) < 8){
    				var RJumpCell = grid.rows[RCellRow - 1].cells[RCellCol + 1];

    				if(RJumpCell.dataset.checkChip == 0){

    					RJumpCell.innerHTML = currCell.innerHTML;
    					RJumpCell.dataset.checkChip = currCell.dataset.checkChip;
    					currCell.innerHTML = "";
    					currCell.dataset.checkChip = 0;

    					gameState.checkArr[RJumpCell.dataset.row][RJumpCell.dataset.column] =
    					gameState.checkArr[currCell.dataset.row][currCell.dataset.column];
    					gameState.checkArr[currCell.dataset.row][currCell.dataset.column] = 0;

    			    	jump(RJumpCell, rightCell, chip);

    				}

    			}

    		}

    	}

   	}

}


setCellClickHandlers();

//Add an alert saying "---- player won! Play again?" and call reset() if yes
function endGame(){

    if(gameState.liveBChips == 0){
        document.getElementById("winDiv").innerHTML = "Grey Player won!";
    }
    else if(gameState.liveGChips == 0){
        document.getElementById("winDiv").innerHTML = "BlackPlayer won!";
    }

}

//------------------------------------- USER INFO AND INTERFACE ---------------------------

//Allows players to select a name for themselves
//Attached to the "Submit Name" button
function submitNames(){
	var blackOpt = document.getElementById("Black");
	var greyOpt = document.getElementById("Grey");
	var userIn = document.getElementById("playerName").value;

	if(blackOpt.selected == true){
		document.getElementById("BlkPlayer").innerHTML = "Black Player: " + userIn;
	}
	else if(greyOpt.selected == true){
		document.getElementById("GryPlayer").innerHTML = "Grey Player: " + userIn;
	}

	document.getElementById("playerName").value = "";

}


//Uses XMLHttpRequest to load data from a local JSON file and use it
//to place a chip on the game board
//Get rid of this and all other JSON stuff entirely
function getJsonObj(){

	var localRequest = new XMLHttpRequest();

	localRequest.open("GET", "Checkers.json", false);
	localRequest.setRequestHeader("Content-Type", "application/json");
	localRequest.send(null);

	var jsonObj = JSON.parse(localRequest.responseText);

	var row = jsonObj.rowNum;
	var col = jsonObj.colNum;
	var chipColor = jsonObj.GryChip;
	var grid = document.getElementsByTagName("table")[0];

	grid.rows[row].cells[col].innerHTML = chipColor;

}








