//
// Created by Admin on 7/3/2020.
//
#include <SDL2/SDL.h>
#include "SDL_Handler.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int SDL_Handler::createLoadingScreen() {
    //Create Window
    genWin = SDL_CreateWindow("Maze Solver", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if(genWin == nullptr){
        cout << "SDL_CreateWindow Error: " << SDL_GetError << endl;
        SDL_Quit();
        return -2;
    }

    //Create SDL renderer
    genRen = SDL_CreateRenderer(genWin, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(genRen == nullptr){
        SDL_DestroyWindow(genWin);
        cout << "SDL_CreateRenderer Error: " << SDL_GetError << endl;
        SDL_Quit();
        return -3;
    }

    //Load the path to the maze generation bmp
    string generateBMPPath = "C:\\Users\\Admin\\CLionProjects\\MazeSolver\\textures\\generatemazetxt.bmp";
    //Load the bmp
    SDL_Surface *bmp = SDL_LoadBMP(generateBMPPath.c_str());
    if(bmp == nullptr){
        SDL_DestroyRenderer(genRen);
        SDL_DestroyWindow(genWin);
        cout << "SDL_LoadBMP Error: " << SDL_GetError << endl;
        SDL_Quit();
        return -4;
    }

    //Create the loading texture
    SDL_Texture *genText = SDL_CreateTextureFromSurface(genRen, bmp);
    SDL_FreeSurface(bmp);
    if(genText == nullptr){
        SDL_DestroyRenderer(genRen);
        SDL_DestroyWindow(genWin);
        cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError << endl;
        return -5;
    }

    //Draw the loading texture
    SDL_RenderCopy(genRen, genText, NULL, NULL);
    SDL_RenderPresent(genRen);

    //Delay the window literally just to make it look like its loading
    SDL_Delay(3000);

    return 0;
}

//Convert the cells in the maze to rectangles to be rendered
void SDL_Handler::cellsToRect(){
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
            cells.push_back(rectCols);
        }
    }
}

int SDL_Handler::displayMaze(){

    //Close the generation window
    closeGenWindow();

    int mazeWidth = maze->getMazeWidth();
    int mazeHeight = maze->getMazeHeight();
    if(mazeWidth < 0 || mazeHeight < 0) return 60;

    //Create the window to display the maze
    simWin = SDL_CreateWindow("Maze Solver", 100, 100, mazeWidth, mazeHeight, SDL_WINDOW_SHOWN);
    if(simWin == nullptr){
        cout << "SDL_CreateWindow Error: " << SDL_GetError << endl;
        SDL_Quit();
        return -6;
    }

    //Create SDL renderer
    simRen = SDL_CreateRenderer(simWin, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(simRen == nullptr){
        SDL_DestroyWindow(simWin);
        cout << "SDL_CreateRenderer Error: " << SDL_GetError << endl;
        SDL_Quit();
        return -7;
    }

    //Get all the cells as rectangles in a vector
    cells.clear();
    cellsToRect();

    if(cells.size() == 0) {
        perror("Failed to create vector of cells");
        return -8;
    }

    SDL_RenderClear(simRen);
    for(int x = 0; x < cells.size(); x++){
        for(int y = 0; y < cells.at(x).size(); y++){

            //If the current cell is a wall, draw it black
            if(maze->getCell(x, y)->getType() == "wall"){
                SDL_SetRenderDrawColor(simRen, 100, 100, 100, 255);
                int fillRectStatus = SDL_RenderFillRect(simRen, cells.at(x).at(y));
                if(fillRectStatus != 0) {
                    string errMsg = "Failed to fill rectangle at " + to_string(x) + " " + to_string(y) + ": " + SDL_GetError();
                    cout << errMsg << endl;
                    return -9;
                }
            }

            //If it is a path, draw it white
            if(maze->getCell(x, y)->getType() == "path"){

                //If the cell is the start of the maze, make it a light green
                if(maze->getCell(x, y)->getASCII() == maze->getStartChar()){
                    SDL_SetRenderDrawColor(simRen, 0, 255, 102, 255);
                    int fillRectStatus = SDL_RenderFillRect(simRen, cells.at(x).at(y));
                    if(fillRectStatus != 0) {
                        string errMsg = "Failed to fill rectangle at " + to_string(x) + " " + to_string(y) + ": " + SDL_GetError();
                        cout << errMsg << endl;
                        return -9;
                    }
                }

                //If the cell is the end of the maze, make it a red
                if(maze->getCell(x, y)->getASCII() == maze->getEndChar()){
                    SDL_SetRenderDrawColor(simRen, 255, 0, 0, 255);
                    int fillRectStatus = SDL_RenderFillRect(simRen, cells.at(x).at(y));
                    if(fillRectStatus != 0) {
                        string errMsg = "Failed to fill rectangle at " + to_string(x) + " " + to_string(y) + ": " + SDL_GetError();
                        cout << errMsg << endl;
                        return -9;
                    }
                }

                //If the cell is a normal path, make it white
                if(maze->getCell(x, y)->getASCII() == maze->getPathChar()){
                    SDL_SetRenderDrawColor(simRen, 255, 255, 255, 255);
                    int fillRectStatus = SDL_RenderFillRect(simRen, cells.at(x).at(y));
                    if(fillRectStatus != 0) {
                        string errMsg = "Failed to fill rectangle at " + to_string(x) + " " + to_string(y) + ": " + SDL_GetError();
                        cout << errMsg << endl;
                        return -9;
                    }
                }
            }
        }
    }
    SDL_RenderPresent(simRen);
    return 0;
}

bool SDL_Handler::runSim() {

    //Main loop flag
    bool running = true;

    //SDL event
    SDL_Event event;

    while(running){


        while(SDL_PollEvent(&event) != 0) {
            //User requests quit
            if( event.type == SDL_QUIT )
            {
                running = false;
                printf("Process ended after user closed application");
            }

                //User presses a key
            else if (event.type == SDL_KEYUP){
                switch(event.key.keysym.sym){
                    //ESC to escape and close the application
                    case SDLK_ESCAPE:
                        running = false;
                        printf("Process ended after user input quit");
                        SDL_Quit();
                        break;
                    //F4 will regenerate the maze
                    case SDLK_F4:
                        SDL_DestroyRenderer(simRen);
                        SDL_DestroyWindow(simWin);
                        createLoadingScreen();
                        generateMaze();
                        displayMaze();
                        return true;
                }
            }
        }
    }
    return running;
}

void SDL_Handler::closeGenWindow() {
    SDL_DestroyRenderer(genRen);
    SDL_DestroyWindow(genWin);
}

void SDL_Handler::loadMaze() { this->maze = maze; }

int SDL_Handler::initialize() {

    if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) {
        cout << "SDL Init Error: " << SDL_GetError << endl;
        return -1;
    }
    maze = new Maze();
    return 0;

}

void SDL_Handler::generateMaze() {
    maze->generateMaze();
    loadMaze();
}