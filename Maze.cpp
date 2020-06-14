//
// Created by Admin on 6/14/2020.
//

#include "Headers.h"
#include <iostream>
#include <vector>
using namespace std;

//Default constructor
Maze::Maze() {};

//Generates the Maze
void Maze::generateMaze() {

    //Generate the solution path
    generateSolution();

}

//Generates the solution path
void Maze::generateSolution() {

    Cell start ('*');
    maze[0][0] = start;

    cout << start.getASCII() << endl;
}