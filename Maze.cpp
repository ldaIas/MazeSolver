//
// Created by Admin on 6/14/2020.
//

#include "Headers.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

//Default constructor
Maze::Maze() {};

//Generates the Maze
void Maze::generateMaze() {

    //Fill in the area with walls for now
    for(int y = 0; y < yDimension; y++){
        for(int x = 0; x < xDimension; x++){
            Cell * cell = new Cell(wallChar);
            cell->setType(wallString);
            maze[x][y] = cell;
        }
    }

    printMaze();

    //Generate the solution path
    generateSolution();

    printMaze();
}

//Generates the solution path
void Maze::generateSolution() {
    int xPos = 1;
    int yPos = 1;
    maze[xPos][yPos]->setASCII(startChar);
    maze[xPos][yPos]->setType(pathString);

    cout << "Start generated" << endl;
    printMaze();

    maze[xDimension-2][yDimension-2]->setASCII(endChar);
    maze[xDimension-2][yDimension-2]->setType(pathString);
    cout << "End generated" << endl;


    bool reachEnd = false;
    srand(time(NULL));
    while(!reachEnd){
        cout << "xPos: " << xPos << "    yPos: " << yPos;
        printMaze();
        reachEnd = getPathDirection(xPos, yPos);
    }

}

//Gets a new direction for the path to go
bool Maze::getPathDirection(int& x, int& y) {

    if(checkNewSurroundings(x, y, endChar)) return true;

    bool dirIsValid = false;
    while (!dirIsValid) {

        int dirNum = rand() % 4;
        cout << "num rolled: " << dirNum << endl;
        switch (dirNum) {
            case 0:
                //Go up
                if((y-1 == 0)) break;
                else if( (maze[x][y-2]->getType() == pathString) || (maze[x][y-1]->getType() == pathString) ) break;
                else if (    (maze[x - 1][y - 1]->getASCII() == pathChar)
                          || (maze[x + 1][y - 1]->getASCII() == pathChar)
                          || (maze[x][y - 2]->getASCII() == pathChar) ) break;
                else dirIsValid = true;
                //Add the new path
                y--;
                maze[x][y]->setType(pathString);
                maze[x][y]->setASCII(pathChar);
                break;
            case 1:
                //Go down
                if((y+1 == yDimension)) break;
                else if( (maze[x][y+2]->getType() == pathString) || (maze[x][y+1]->getType() == pathString) ) break;
                else if (    (maze[x - 1][y + 1]->getASCII() == pathChar)
                          || (maze[x + 1][y + 1]->getASCII() == pathChar)
                          || (maze[x][y + 2]->getASCII() == pathChar) ) break;
                else dirIsValid = true;
                //Add the new path
                y++;
                maze[x][y]->setType(pathString);
                maze[x][y]->setASCII(pathChar);
                break;
            case 2:
                //Go left
                if((x-1 == 0 )) break;
                else if( (maze[x-2][y]->getType() == pathString) || (maze[x-1][y]->getType() == pathString) ) break;
                else if (    (maze[x - 2][y]->getASCII() == pathChar)
                          || (maze[x - 1][y - 1]->getASCII() == pathChar)
                          || (maze[x - 1][y + 1]->getASCII() == pathChar) ) break;
                else dirIsValid = true;
                //Add the new path
                x--;
                maze[x][y]->setType(pathString);
                maze[x][y]->setASCII(pathChar);
                break;
            case 3:
                //Go right
                if((x+1 == xDimension )) break;
                else if( (maze[x+2][y]->getType() == pathString) || (maze[x+1][y]->getType() == pathString) ) break;
                else if (    (maze[x + 2][y]->getASCII() == pathChar)
                          || (maze[x + 1][y - 1]->getASCII() == pathChar)
                          || (maze[x + 1][y + 1]->getASCII() == pathChar) ) break;
                else dirIsValid = true;
                //Add the new path
                x++;
                maze[x][y]->setType(pathString);
                maze[x][y]->setASCII(pathChar);
                break;
            default:
                break;
        }
    }
    return false;
}


bool Maze::checkNewSurroundings(int x, int y, char type){
    return (maze[x][y]->getASCII() == type)
           || (maze[x - 1][y]->getASCII() == type)
           || (maze[x + 1][y]->getASCII() == type)
           || (maze[x][y - 1]->getASCII() == type)
           || (maze[x][y + 1]->getASCII() == type);
}

//Prints the maze to console
void Maze::printMaze(){
    cout << endl;
    for(int y = 0; y < yDimension; y++){
        for(int x = 0; x < xDimension; x++){
            cout << maze[x][y]->getASCII() << " ";
            if(x == xDimension - 1) cout << endl;
        }
    }
    cout << endl;
}