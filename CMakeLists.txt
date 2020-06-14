cmake_minimum_required(VERSION 3.16)
project(MazeSolver)

set(CMAKE_CXX_STANDARD 14)

add_executable(MazeSolver main.cpp Headers.h Cell.cpp Maze.cpp)