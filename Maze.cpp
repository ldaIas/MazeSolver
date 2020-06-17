//
// Created by Admin on 6/14/2020.
//

#include "Headers.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <queue>
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
            cell->setPosition(x, y);
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

    maze[xDimension - 2][yDimension - 2]->setASCII(endChar);
    maze[xDimension - 2][yDimension - 2]->setType(pathString);
    cout << "End generated" << endl;


    bool validMove = true;
    srand(time(NULL));
    while (validMove) {
        cout << "xPos: " << xPos << "    yPos: " << yPos;
        printMaze();
        validMove = getPathDirection(xPos, yPos);
        //If the last made path is next to the end, stop drawing
        if (checkNewSurroundings(xPos, yPos, endChar)) break;
            //If not, and no other "move" for the path is valid, start a new path branch and add a new path directly
            //touching the end to allow paths to meet
        else if (!validMove) {
            int randPathBranch = rand() % paths.size();
            xPos = paths.at(randPathBranch)->getPositionX();
            yPos = paths.at(randPathBranch)->getPositionY();
            validMove = true;

        }
    }
}

//Gets a new direction for the path to go
bool Maze::getPathDirection(int& x, int& y) {

    set<int> numsRolled;
    bool dirIsValid = false;
    while (!dirIsValid) {

        //Roll a new number. If it's already been rolled, start a new loop
        int dirNum = rand() % 4;
        cout << "num rolled: " << dirNum << endl;
        if(numsRolled.find(0) != numsRolled.end()
            && numsRolled.find(1) != numsRolled.end()
            && numsRolled.find(2) != numsRolled.end()
            && numsRolled.find(3) != numsRolled.end()) return false;
        else if(numsRolled.find(dirNum) != numsRolled.end()) continue;
        numsRolled.insert(dirNum);

        cout << "num chosen: " << dirNum << endl;
        switch (dirNum) {
            case 0:
                //Go up
                if((y-1 == 0)) break;
                else if( (maze[x][y-2]->getType() == pathString) || (maze[x][y-1]->getType() == pathString) ) break;
                else if (    (maze[x - 1][y - 1]->getASCII() == pathChar)
                          || (maze[x + 1][y - 1]->getASCII() == pathChar)
                          || (maze[x][y - 2]->getASCII() == pathChar) ) break;
                else dirIsValid = true;
                y--;
                //Add the new path
                maze[x][y]->setType(pathString);
                maze[x][y]->setASCII(pathChar);
                //Add the new path to the path array
                paths.push_back(maze[x][y]);
                break;
            case 1:
                //Go down
                if((y+2 == yDimension)) break;
                else if( (maze[x][y+2]->getType() == pathString) || (maze[x][y+1]->getType() == pathString) ) break;
                else if (    (maze[x - 1][y + 1]->getASCII() == pathChar)
                          || (maze[x + 1][y + 1]->getASCII() == pathChar)
                          || (maze[x][y + 2]->getASCII() == pathChar) ) break;
                else dirIsValid = true;
                y++;
                //Add the new path
                maze[x][y]->setType(pathString);
                maze[x][y]->setASCII(pathChar);
                //Add the new path to the path array
                paths.push_back(maze[x][y]);
                break;
            case 2:
                //Go left
                if((x-1 == 0 )) break;
                else if( (maze[x-2][y]->getType() == pathString) || (maze[x-1][y]->getType() == pathString) ) break;
                else if (    (maze[x - 2][y]->getASCII() == pathChar)
                          || (maze[x - 1][y - 1]->getASCII() == pathChar)
                          || (maze[x - 1][y + 1]->getASCII() == pathChar) ) break;
                else dirIsValid = true;
                x--;
                //Add the new path
                maze[x][y]->setType(pathString);
                maze[x][y]->setASCII(pathChar);
                //Add the new path to the path array
                paths.push_back(maze[x][y]);
                break;
            case 3:
                //Go right
                if((x+1 == xDimension )) break;
                else if( (maze[x+2][y]->getType() == pathString) || (maze[x+1][y]->getType() == pathString) ) break;
                else if (    (maze[x + 2][y]->getASCII() == pathChar)
                          || (maze[x + 1][y - 1]->getASCII() == pathChar)
                          || (maze[x + 1][y + 1]->getASCII() == pathChar) ) break;
                else dirIsValid = true;
                x++;
                //Add the new path
                maze[x][y]->setType(pathString);
                maze[x][y]->setASCII(pathChar);
                //Add the new path to the path array
                paths.push_back(maze[x][y]);
                break;
            default:
                break;
        }
    }
    return true;
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

//Make a path spiraling out from a certain cell
/*void Maze::expandFromCell(int x, int y){
    queue<Cell*> cells;

    if(x+1 != xDimension - 2) cells.push(maze[x+1][y]);
    if(x-1 != xDimension - 1) cells.push(maze[x-1][y]);
    if(y+1 != yDimension - 2) cells.push(maze[x][y+1]);
    if(y-1 != xDimension - 1) cells.push(maze[x][y-1]);






}*/