#include <stdlib.h>
#include <iostream>
#include "wall.h"
#include "disjointset.h"

//Generates a list of walls that form the maze
//Accepts number of rows and columns of a maze
//Returns the number of walls in the maze
int generateMaze(int row, int col, Wall walls[]) {
	static Wall allWalls[50000]; //Static datamember to for lower memory usage

	int allWallsNum = row * (col - 1) + col * (row - 1);
	int cellNum = 0;
	int wallNum = 0;
	DisjointSet mazeSet = DisjointSet(row * col);

	//Generate maze with all possible walls
	for (int x = 0; x < row; ++x) {
		for (int y = 0; y < col; ++y) {
			int a = y + col * x;
			
			//Generating Horizontal Walls
			if (x != row - 1) {
				allWalls[wallNum++] = Wall(a, a + col);
			}
			//Generating Vertical Walls
			if (y != col - 1) {
				allWalls[wallNum++] = Wall(a, a + 1);
			}

			//Generating Cells
			mazeSet.makeSet(cellNum++);
		}
	}

	//Find and remove random walls until all cells are connected
	while (mazeSet.firstSetSize() < (row * col)) {
		int randNum = rand() % allWallsNum;
		Wall randWall = allWalls[randNum];

		if (randWall.cell1() != randWall.cell2()) {
			int cell1Rep = mazeSet.findSet(randWall.cell1());
			int cell2Rep = mazeSet.findSet(randWall.cell2());
			
			if (cell1Rep != cell2Rep && mazeSet.unionSets(cell1Rep, cell2Rep)) {
				allWalls[randNum] = Wall(); //Set wall to default state (removed)
				wallNum--;
			}
		}
	}

	//Set walls to walls that are not in default state (removed)
	for (int i = 0, j = 0; i < allWallsNum; i++) {
		if (allWalls[i].cell1() != allWalls[i].cell2()) {
			walls[j++] = allWalls[i];
		}
	}

	return wallNum;
}