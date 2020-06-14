//
// Created by Admin on 6/14/2020.
//

#include "Headers.h"

using namespace std;

//Defualt Constructor. Set the ASCII character to ' '
Cell::Cell() {
    setASCII(' ');
};

//Constructor that sets the ASCII character to the value passed in
Cell::Cell(char c) {
    setASCII(c);
};

void Cell::setASCII(char c) { ASCIIrep = c; };

char Cell::getASCII() { return ASCIIrep; };