#include "Headers.h"
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
using namespace std;

int main() {

	Maze maze;
	maze.generateMaze();

	return 0;
}