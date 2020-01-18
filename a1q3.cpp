#include "wall.h"
#include "maze.h"

//Find a path from cell number startCell to cell number endCell
//Path is returned throught the parameter path and marked as visited in the maze
int runMaze(Maze& theMaze, int path[], int startCell, int endCell){
	
	//Temp cell to switch startcell and endcell to reverse path
	//Prioritizing cleaner code over memory usage
	int tempCell = startCell;
	startCell = endCell;
	endCell = tempCell;

	//Check if reached the end
	if (startCell == endCell) {
		path[0] = startCell;
		return 1;
	}

	//Check if cell already visited
	if (theMaze.isMarked(startCell)) {
		return 0;
	}

	//Mark cell as visited
	theMaze.mark(startCell);

	//Check if you can go up, left, right or down,
	//Then recursively call runMaze itself from that cell to the end
	//If path is non-zero, add this cell to the path and increment num of cells in the path
	if (theMaze.canGo(startCell, startCell + 1)) {
		int numPath = runMaze(theMaze, path, endCell, startCell + 1);
		
		if (numPath != 0) {
			path[numPath] = startCell;
			return numPath + 1;
		}
	}
	if (theMaze.canGo(startCell, startCell - 1)) {
		int numPath = runMaze(theMaze, path, endCell, startCell - 1);
		
		if (numPath != 0) {
			path[numPath] = startCell;
			return numPath + 1;
		}
	}
	if (theMaze.canGo(startCell, startCell + theMaze.numCols())) {
		int numPath = runMaze(theMaze, path, endCell, startCell + theMaze.numCols());
		
		if (numPath != 0) {
			path[numPath] = startCell;
			return numPath + 1;
		}
	}
	if (theMaze.canGo(startCell, startCell - theMaze.numCols())) {
		int numPath = runMaze(theMaze, path, endCell, startCell - theMaze.numCols());
		
		if (numPath != 0) {
			path[numPath] = startCell;
			return numPath + 1;
		}
	}
	return 0;
}
