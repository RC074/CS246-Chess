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

PieceType getPieceType(char c) {
    char lowerC = ('a' <= c && c <= 'z') ? c : c - 'A' + 'a';
    if (lowerC == 'k') return PieceType::KING;
    if (lowerC == 'q') return PieceType::QUEEN;
    if (lowerC == 'b') return PieceType::BISHOP;
    if (lowerC == 'r') return PieceType::ROOK;
    if (lowerC == 'n') return PieceType::KNIGHT;
    if (lowerC == 'p') return PieceType::PAWN;
}


