#include "Headers.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "SDL_Handler.h"
using namespace std;

int main(int argc, char* args[]) {

    //Create our SDL handler to do all of the SDL stuff for us
    SDL_Handler SDL_Handle;

    //Initialize SDL
    int init = SDL_Handle.initialize();
    if(init != 0) return init;

    //Create the maze generation loading screen
    int loadingCode = SDL_Handle.createLoadingScreen();
    if(loadingCode != 0){
        cout << "Error while creating initial window: " << loadingCode << endl;
        return loadingCode;
    }

    Maze maze;
    maze.generateMaze();

    SDL_Handle.loadMaze(&maze);

    int displayMazeCode = SDL_Handle.displayMaze();
    if( displayMazeCode != 0){
        cout << "Error while creating maze window: " << displayMazeCode << endl;
        return displayMazeCode;
    }



	return 0;
}

