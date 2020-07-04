//
// Created by Admin on 7/3/2020.
//

#ifndef MAZESOLVER_SDL_HANDLER_H
#define MAZESOLVER_SDL_HANDLER_H
#include <SDL2/SDL.h>
#include "Headers.h"

//This class will handle all calls and methods that use SDL
class SDL_Handler{
public:

    //Load the maze into the handler
    void loadMaze();

    //Initialize SDL Window
    int initialize();

    //Create the maze generation window
    int createLoadingScreen();

    //Display the maze generated
    int displayMaze();

    //Run the simulation
    bool runSim();

    //Close generating window
    void closeGenWindow();

    //Generate the maze to be used
    void generateMaze();

private:

    //Holds the maze generated
    Maze* maze;

    //Generating window and renderer
    SDL_Window* genWin;
    SDL_Renderer* genRen;

    //Simulation window and renderer
    SDL_Window* simWin;
    SDL_Renderer* simRen;

    //Vector of cells to draw and its generation method
    vector<vector <SDL_Rect*>> cells;
    void cellsToRect();
    void clearCellsVector();


};

#endif //MAZESOLVER_SDL_HANDLER_H
