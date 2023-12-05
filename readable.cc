#include "readable.h"
#include <sstream>

string toString(int row, int col) {
    int readableRow = 8 - row;
    char readableCol = 'a' + col;
    ostringstream readable {};
    readable << readableCol << readableRow;
    return readable.str();
}

void getPos(istream &in, int &row, int &col) {
    string readable;
    if (!(in >> readable)) return;
    col = readable[0] - 'a';
    row = 8 - (readable[1] - '0');
}

PieceType getPieceType(char c) {
    char currChar = c;
    if (currChar >= 97) currChar -= 32;

    if (currChar == 'K') return PieceType::KING;
    else if (currChar == 'Q') return PieceType::QUEEN;
    else if (currChar == 'B') return PieceType::BISHOP;
    else if (currChar == 'N') return PieceType::KNIGHT;
    else if (currChar == 'R') return PieceType::ROOK;
    else if (currChar == 'P') return PieceType::PAWN;
    else return PieceType::NONE;
}


