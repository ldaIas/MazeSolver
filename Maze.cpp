//
// Created by Admin on 6/14/2020.
//

#include "Headers.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
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
            cout << "not valid move else entered" << endl;
            int randPathBranch = rand() % (paths.size() - 1);
            xPos = paths.at(randPathBranch)->getPositionX();
            yPos = paths.at(randPathBranch)->getPositionY();
            validMove = true;
            expandFromCell(findCell(endChar));
            resetTypes();
            bool verified = verifySolution(findCell(endChar));
            resetTypes();
            cout << "Verified value: " << verified << endl;
            if (verified) break;

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
                if((y+1 == yDimension - 2)) break;
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
                if((x+1 == xDimension - 2)) break;
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
bool Maze::expandFromCell( Cell* cell, int x, int y){
    cout << "expand from cell entered" << endl;

    if(cell != nullptr) {
        x = cell->getPositionX();
        y = cell->getPositionY();
    }

    cout << "Cell coords: x = " << x << "   y: " << y << endl;

    if(cell->getType() == wallString){
        cell->setType("traversed");
        cell->setASCII(pathChar);
        return true;
    }
    else cell->setType("traversed");

    if(( x+1 < xDimension - 2 ) && ( maze[x+1][y]->getType() != "traversed" )) {
        if (expandFromCell(maze[x + 1][y])) return true;
    }

    if(( x-1 > 0 ) && ( maze[x-1][y]->getType() != "traversed" )) {
        if(expandFromCell(maze[x-1][y])) return true;
    }

    if(( y+1 < yDimension - 2 ) && ( maze[x][y+1]->getType() != "traversed" )) {
        if(expandFromCell(maze[x][y+1])) return true;
    }
    if(( y-1 > 0 )  && ( maze[x][y-1]->getType() != "traversed" )) {
        if( expandFromCell(maze[x][y-1])) return true;
    }
    return false;
}

//Finds a cell by character type. Returns the start cell by default. If improper maze made, returns the last cell in the array
Cell* Maze::findCell(char type = ' ') {

    if(type == ' ') type = startChar;

    for(int x = 0; x < xDimension; x++){
        for(int y = 0; y < yDimension; y++){
            if(maze[x][y]->getASCII() == type) return maze[x][y];
        }
    }
    return maze[xDimension-1][yDimension-1];

}

//Verify the solution of the maze. Temporarily changes path type to 'checked'
bool Maze::verifySolution(Cell* cell){
    printMaze();
    cout << "Cell's char: " << cell->getASCII() << endl;
    cout << "Start's char: " << findCell(startChar)->getASCII() << endl;
    bool verified = false;
    if(cell->getASCII() == findCell(startChar)->getASCII()){
        cell->setASCII('@');
        verified = true;
    }
    else{
        cell->setASCII('@');
        //Check the cell one above this space
        if(( cell->getPositionY() > 1 ) && ( maze[cell->getPositionX()][cell->getPositionY()-1]->getType() == pathString )) {
            cell->setType("checked");
            Cell* newCell = maze[cell->getPositionX()][cell->getPositionY()-1];
            verified = verifySolution(newCell);
            if(verified) return verified;
        }

        //Check the cell one below this space
        if(( cell->getPositionY() < yDimension - 2 ) && ( maze[cell->getPositionX()][cell->getPositionY()+1]->getType() == pathString )) {
            cell->setType("checked");
            Cell* newCell = maze[cell->getPositionX()][cell->getPositionY()+1];
            verified = verifySolution(newCell);
            if(verified) return verified;
        }

        //Check the cell one left this space
        if(( cell->getPositionX() > 1 ) && ( maze[cell->getPositionX()-1][cell->getPositionY()]->getType() == pathString )) {
            cell->setType("checked");
            Cell* newCell = maze[cell->getPositionX()-1][cell->getPositionY()];
            verified = verifySolution(newCell);
            if(verified) return verified;
        }

        //Check the cell one right this space
        if(( cell->getPositionX() < xDimension - 2 ) && ( maze[cell->getPositionX()+1][cell->getPositionY()]->getType() == pathString )) {
            cell->setType("checked");
            Cell* newCell = maze[cell->getPositionX()+1][cell->getPositionY()];
            verified = verifySolution(newCell);
            if(verified) return verified;
        }
    }
    return verified;
}

void Maze::resetTypes() {

    for(int x = 0; x < xDimension; x++){
        for(int y = 0; y < yDimension; y++){
            if(( maze[x][y]->getType() == "checked" ) || (maze[x][y]->getType() == "traversed" )) maze[x][y]->setType(pathString);
            if( maze[x][y]->getASCII() == '@' ) maze[x][y]->setASCII(pathChar);
            maze[startX][startY]->setASCII(startChar);
            maze[endX][endY]->setASCII(endChar);
        }
    }

}

int Maze::getMazeWidth() {
    if(maze[0][0] != nullptr) {
        int cellWidth = maze[0][0]->getPixelWidth();
        return cellWidth * (xDimension);
    }
    else return -1;
}

int Maze::getMazeHeight() {
    if(maze[0][0] != nullptr) {
        int cellHeight = maze[0][0]->getPixelHeight();
        return cellHeight * (yDimension);
    }
    else return -1;
}

int Maze::getSizeX() { return xDimension; }
int Maze::getSizeY() { return yDimension; }

Cell* Maze::getCell(int x, int y){
    return maze[x][y];
}

char Maze::getStartChar() { return startChar; }
char Maze::getEndChar() { return endChar; }
char Maze::getPathChar() { return pathChar; }