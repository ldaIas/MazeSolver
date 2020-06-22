#include "Headers.h"
#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

int main(int argc, char* args[]) {

    //The window we'll be rendering to
    SDL_Window* window = NULL;

    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
    {
        cout << "SDL Init Error: " << SDL_GetError << endl;
        return 1;
    }


	Maze maze;
	maze.generateMaze();

	return 0;
}