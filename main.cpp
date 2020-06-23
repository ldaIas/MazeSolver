#include "Headers.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
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

//Convert the cells in the maze to rectangles to be rendered
vector<vector <SDL_Rect*>> cellsToRect(Maze* maze){

    if(maze != nullptr) {
        vector<vector<SDL_Rect *>> cellsAsRectangles;

        for (int x = 0; x < maze->getSizeX(); x++) {
            vector<SDL_Rect *> rectCols;
            for (int y = 0; y < maze->getSizeY(); y++) {
                SDL_Rect *rect = new SDL_Rect();
                rect->x = maze->getCell(x, y)->getPixelWidth() * x;
                rect->y = maze->getCell(x, y)->getPixelHeight() * y;
                rect->w = maze->getCell(x, y)->getPixelWidth();
                rect->h = maze->getCell(x, y)->getPixelHeight();
                rectCols.push_back(rect);
            }
            cellsAsRectangles.push_back(rectCols);
        }
    }
    else{
        //TODO: Do something
    }
}


int displayMaze(Maze* maze){

    int mazeWidth = maze->getMazeWidth();
    int mazeHeight = maze->getMazeHeight();
    if(mazeWidth < 0 || mazeHeight < 0) return 60;

    //Create the window to display the maze
    SDL_Window* win = SDL_CreateWindow("Maze Solver", 100, 100, mazeWidth, mazeHeight, SDL_WINDOW_SHOWN);
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

    //Get all the cells as rectangles in a vector
    vector< vector<SDL_Rect*>> cells = cellsToRect(maze);

    SDL_Surface *surface = SDL_GetWindowSurface(win);
    for(int x = 0; x < cells.size() - 1; x++){
        vector<SDL_Rect*> currCol = cells.at(x);
        for(int y = 0; y < currCol.size() - 1; y++){

            //If the current cell is a wall, draw it black
            if(maze->getCell(x, y)->getType() == "wall"){
                SDL_FillRect(surface, currCol.at(y), SDL_MapRGB(surface->format, 0, 0, 0));
                SDL_RenderDrawRect(ren, currCol.at(y));
                SDL_RenderPresent(ren);
            }
            if(maze->getCell(x, y)->getType() == "path"){
                SDL_FillRect(surface, currCol.at(y), SDL_MapRGB(surface->format, 255, 255, 255));
                SDL_RenderDrawRect(ren, currCol.at(y));
                SDL_RenderPresent(ren);
            }
        }
    }
    return 0;
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


    int displayMazeCode = displayMaze(&maze);
    if( displayMazeCode != 0){
        cout << "Error while creating maze window: " << displayMazeCode << endl;
        return displayMazeCode;
    }


	return 0;
}

