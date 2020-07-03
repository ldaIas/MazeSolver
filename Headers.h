//
// Created by Admin on 6/14/2020.
//

#include <string>
#include <vector>
#include <set>
using namespace std;
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

    void setType(string);

    string getType();

    //Set their position
    void setPosition(int, int);

    //Get their positions
    int getPositionX();
    int getPositionY();

    //Get dimensions
    int getPixelWidth();
    int getPixelHeight();

private:

    //The cells representation in ASCII characters
    char ASCIIrep;

    //What type it is
    string cellType;

    //Their individual position
    int posX;
    int posY;

    //Where the cell originated from, if it's a path (start or end)
    char origin;

    //Dimensions of the cell for displaying
    int pixelWidth = 30;
    int pixelHeight = 30;

};

class Maze
{
public:
    //Add public variables/methods

    //Default Constructor
    Maze();

    //Generate the maze's structure
    void generateMaze();

    //Print maze to console
    void printMaze();

    //Get pixel dimensions of maze
    int getMazeWidth();
    int getMazeHeight();

    //Get actual sizes of maze
    int getSizeX();
    int getSizeY();

    //Get cell at location
    Cell* getCell(int, int);

    //Get characters for different cells
    char getStartChar();
    char getEndChar();
    char getPathChar();


private:
    //Add private variables/methods
    /*
    Private variables
    */
    //The sizes of the array
    const static int xDimension = 15;
    const static int yDimension = 10;

    //Positions of the start and end points
    int startX = 1;
    int startY = 1;

    int endX = xDimension - 2;
    int endY = yDimension - 2;

    //The array that holds the maze size
    //Accessed: x, y
    Cell* maze[xDimension][yDimension];

    //This vector holds every path cell
    vector<Cell*> paths;

    //ASCII character representations for each cell type
    char wallChar = '|';
    char pathChar = '_';
    char startChar = '*';
    char endChar = 'E';

    //Names for cell types
    string pathString = "path";
    string wallString = "wall";

    /*
    Private methods
    */

    //Generates the solution path through the maze
    //For the purpose of this program, all mazes will start at (1,1) and end at (xDim-1, yDim-1)
    void generateSolution();

    //Gets a new direction for the maze path to go
    bool getPathDirection(int&, int&);

    //Checks surroundings from input coords looking for the type of cell
    bool checkNewSurroundings(int, int, char);

    //Expand a path outwards from the cell passed in. Can either pass in cell coords or the cell itself
    bool expandFromCell(Cell* = nullptr, int = -1, int = -1);

    //Finds a certain cell by type. Returns the first one found. Char is optional, leave empty to find the start
    Cell* findCell(char type);

    //Verifies the solution of the maze
    bool verifySolution(Cell*);

    //Resets the types of paths to pathString
    void resetTypes();


};


#endif //MAZESOLVER_HEADERS_H
