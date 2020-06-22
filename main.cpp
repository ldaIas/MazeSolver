#include "Headers.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
using namespace std;

int createLoadingScreen() {
    //Create Window
    SDL_Window* genWin = SDL_CreateWindow("Maze Solver", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if(genWin == nullptr){
        cout << "SDL_CreateWindow Error: " << SDL_GetError << endl;
        SDL_Quit();
        return 2;
    }

    //Create SDL renderer
    SDL_Renderer* ren = SDL_CreateRenderer(genWin, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(ren == nullptr){
        SDL_DestroyWindow(genWin);
        cout << "SDL_CreateRenderer Error: " << SDL_GetError << endl;
        SDL_Quit();
        return 3;
    }

    //Load the path to the maze generation bmp
    string generateBMPPath = "C:\\Users\\Admin\\CLionProjects\\MazeSolver\\textures\\generatemazetxt.bmp";
    //Load the bmp
    SDL_Surface *bmp = SDL_LoadBMP(generateBMPPath.c_str());
    if(bmp == nullptr){
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(genWin);
        cout << "SDL_LoadBMP Error: " << SDL_GetError << endl;
        SDL_Quit();
        return 4;
    }

    //Create the loading texture
    SDL_Texture *genText = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if(genText == nullptr){
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(genWin);
        cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError << endl;
        return 5;
    }

    //Draw the loading texture
    SDL_RenderCopy(ren, genText, NULL, NULL);
    SDL_RenderPresent(ren);

    return 0;
}

int displayMaze(Maze* maze){

    //Create the window to display the maze
    SDL_Window* win = SDL_CreateWindow("Maze Solver", 100, 100, maze->getMazeWidth(), maze->getMazeHeight(), SDL_WINDOW_SHOWN);
    if(win == nullptr){
        cout << "SDL_CreateWindow Error: " << SDL_GetError << endl;
        SDL_Quit();
        return 6;
    }

    //Create SDL renderer
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(ren == nullptr){
        SDL_DestroyWindow(win);
        cout << "SDL_CreateRenderer Error: " << SDL_GetError << endl;
        SDL_Quit();
        return 7;
    }




}



int main(int argc, char* args[]) {

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
    {
        cout << "SDL Init Error: " << SDL_GetError << endl;
        return 1;
    }

    int loadingCode = createLoadingScreen();
    if(loadingCode != 0){
        cout << "Error while creating initial window: " << loadingCode << endl;
        return loadingCode;
    }

    Maze maze;
    maze.generateMaze();

    /*
    int displayMazeCode = displayMaze(&maze);
    if( displayMazeCode != 0){
        cout << "Error while creating maze window: " << displayMazeCode << endl;
        return displayMazeCode;
    }
    */

	return 0;
}

