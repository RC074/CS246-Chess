#include "readable.h"
#include <sstream>

string toString(int row, int col) {
    int readableRow = 8 - row;
    char readableCol = 'a' + col;
    ostringstream readable {};
    readable << readableCol << readableRow;
    return readable.str();
}

istream &getPos(istream &in, int row, int col) {
    string readable;
    if (!(in >> readable)) return in;
    col = readable[0] - 'a';
    row = 8 - (readable[1] - '0');
}

