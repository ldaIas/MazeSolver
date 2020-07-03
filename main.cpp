#include "Headers.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

void runSim(SDL_Window *pWindow, SDL_Renderer *pRenderer);

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
    vector<vector<SDL_Rect *>> cellsAsRectangles;
    if(maze != nullptr) {
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
    return cellsAsRectangles;
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

    if(cells.size() == 0) {
        perror("Failed to create vector of cells");
        return 8;
    }

    SDL_Surface *surface = SDL_GetWindowSurface(win);
    SDL_RenderClear(ren);
    for(int x = 0; x < cells.size(); x++){
        for(int y = 0; y < cells.at(x).size(); y++){

            //If the current cell is a wall, draw it black
            if(maze->getCell(x, y)->getType() == "wall"){
                SDL_SetRenderDrawColor(ren, 100, 100, 100, 255);
                int fillRectStatus = SDL_RenderFillRect(ren, cells.at(x).at(y));
                if(fillRectStatus != 0) {
                    string errMsg = "Failed to fill rectangle at " + to_string(x) + " " + to_string(y) + ": " + SDL_GetError();
                    cout << errMsg << endl;
                    return 9;
                }
            }

            //If it is a path, draw it white
            if(maze->getCell(x, y)->getType() == "path"){

                //If the cell is the start of the maze, make it a light green
                if(maze->getCell(x, y)->getASCII() == maze->getStartChar()){
                    SDL_SetRenderDrawColor(ren, 0, 255, 102, 255);
                    int fillRectStatus = SDL_RenderFillRect(ren, cells.at(x).at(y));
                    if(fillRectStatus != 0) {
                        string errMsg = "Failed to fill rectangle at " + to_string(x) + " " + to_string(y) + ": " + SDL_GetError();
                        cout << errMsg << endl;
                        return 9;
                    }
                }

                //If the cell is the end of the maze, make it a red
                if(maze->getCell(x, y)->getASCII() == maze->getEndChar()){
                    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
                    int fillRectStatus = SDL_RenderFillRect(ren, cells.at(x).at(y));
                    if(fillRectStatus != 0) {
                        string errMsg = "Failed to fill rectangle at " + to_string(x) + " " + to_string(y) + ": " + SDL_GetError();
                        cout << errMsg << endl;
                        return 9;
                    }
                }

                //If the cell is a normal path, make it white
                if(maze->getCell(x, y)->getASCII() == maze->getPathChar()){
                    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
                    int fillRectStatus = SDL_RenderFillRect(ren, cells.at(x).at(y));
                    if(fillRectStatus != 0) {
                        string errMsg = "Failed to fill rectangle at " + to_string(x) + " " + to_string(y) + ": " + SDL_GetError();
                        cout << errMsg << endl;
                        return 9;
                    }
                }
            }
        }
        SDL_RenderPresent(ren);
    }
    SDL_RenderPresent(ren);

    runSim(win, ren);
    return 0;
}

/*void runSim(SDL_Window *win, SDL_Renderer *ren) {

    bool running = true;
    while(running){

    }

}*/



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

