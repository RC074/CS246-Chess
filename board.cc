#include "board.h"

void Board::clearBoard() {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            delete theBoard[i][j];
            theBoard[i][j] = nullptr;
        }
    }
    won = false;
}

// void Board::init() {
//     // equivlent to the Grid class for A4
//     // clear grid?
//     // init grid of PIECES
//     clearBoard();
    
//     won = false;
// }

bool Board::move(vector<int> p1, vector<int> p2) {
    // we check if the move is a valid move
    // if it is, we add the move to the stack in the form [r1, c1, r2, c2]
    Piece* tmp = theBoard[p1[0]][p1[1]];
    
}

Piece* Board::getPieceAt(vector<int> p) {
    // recall vector<int> p is in the form [r, c]
    return theBoard[p[0]][p[1]];
}

vector<vector<Piece*>> Board::getBoard() {}

Color Board::getWinner() {}

void Board::undo() {}

vector<int> Board::getPreviousMove() {}

Player* Board::getPlayerBlack() {}

Player* Board::getPlayerWhite() {}
