#include "board.h"

Board::Board(Player *p1, Player *p2) : 
        p1{p1}, p2{p2}, 
        theGrid{vector<vector<Piece *>>(8, vector<Piece *>(8, nullptr))}
    {}

void Board::init(bool p1White) {
    clearBoard();
    // the board is filled with nullptr now
    p1->setColor((p1White ? Color::WHITE : Color::BLACK));
    p1->setColor(((!p1White) ? Color::WHITE : Color::BLACK));
    for (int row = 0; row < theGrid.size(); ++row) {
        for (int col = 0; col < theGrid[row].size(); ++col) {
            
        }
    }
}

// black pieces on the top, rows and cols indexed from 0-7
Piece *constructPiece(int row, int col) {
    if (!(row <= 7 && row >= 0)) return nullptr;

}