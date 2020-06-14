//
// Created by Admin on 6/14/2020.
//

#ifndef MAZESOLVER_HEADERS_H
#define MAZESOLVER_HEADERS_H

class Cell
{
public:

    //Default Constructor
    Cell();

    //Constructor taking in a character to represent it
    Cell(char c);

    //Set the ASCII character
    void setASCII(char c);

    //Get the ASCII character
    char getASCII();


private:

    //The cells representation in ASCII characters
    char ASCIIrep;

};

class Maze
{
public:
    //Add public variables/methods

    //Default Constructor
    Maze();

    //Generate the maze's structure
    void generateMaze();


private:
    //Add private variables/methods
    /*
    Private variables
    */
    //The sizes of the array
    const static int xDimension = 15;
    const static int yDimension = 10;

    //The array that holds the maze size
    //Accessed: x, y
    Cell maze[xDimension][yDimension];

    /*
    Private methods
    */

    //Generates the solution path through the maze
    //For the purpose of this program, all mazes will start at (0,0) and end at (xDim, yDim)
    void generateSolution();

};


#endif //MAZESOLVER_HEADERS_H
