#include "board.h"

Board::Board(Player *p1, Player *p2) : 
        p1{p1}, p2{p2}, 
        theBoard{vector<vector<Piece *>>(8, vector<Piece *>(8, nullptr))}
    {}

void Board::init(bool p1White) {
    clearBoard();
    // the board is filled with nullptr now
    p1->setColor((p1White ? Color::WHITE : Color::BLACK));
    p1->setColor(((!p1White) ? Color::WHITE : Color::BLACK));
    for (int row = 0; row < theBoard.size(); ++row) {
        for (int col = 0; col < theBoard[row].size(); ++col) {
            
        }
    }
}

// black pieces on the top, rows and cols indexed from 0-7
Piece *constructPiece(int row, int col) {
    if (!(row <= 7 && row >= 0)) return nullptr;

}

void Board::clearBoard() {
    for (int i = 0; i < theBoard.size(); ++i) {
        for (int j = 0; j < theBoard[i].size(); ++j) {
            delete theBoard[i][j];
            theBoard[i][j] = nullptr;
        }
    }
    won = false;
}

bool Board::move(vector<int> p1, vector<int> p2) {
    // 
}

Piece* Board::getPieceAt(int row, int col) {
    // recall vector<int> p is in the form [r, c]
    return theBoard[row][col];
}

vector<vector<Piece*>> Board::getBoard() {
    return theBoard;
}

Color Board::getWinner() {
    // return the piece that made the last move's color.
    Move prevMove = getPreviousMove();
    return getPieceAt(prevMove.r1, prevMove.c1)->getColor();
}

void Board::undo() {
    // pop the last move off the stack (with getPreviousMove() and pop_back()
    // move the piece back to its original position (first two num in the prevMove vector)
    // set the piece at the new position to empty piece? or the piece that was there before - can get by the piece before?
    // set the piece at the old position to the piece we popped off the stack
    // set the piece's position to the old position

    Move prevMove = getPreviousMove();
    int oldr = prevMove.r0;
    int oldc = prevMove.c0; 
    int newr = prevMove.r1;
    int newc = prevMove.c1;

    Piece* newPosPiece = theBoard[newr][newc]; // the piece that was at the new position
    history.pop_back();
    // if there was a capture, then the piece at the new position is the captured piece
    theBoard[newr][newc] = prevMove.captures ? const_cast<Piece*>(prevMove.captures) : nullptr;
    theBoard[oldr][oldc] = newPosPiece; // set the old position to the piece that was at the new position
    newPosPiece->setPosition(oldr, oldc); // set the piece's position to the old position
}

Move Board::getPreviousMove() {
    return history.back();
}

Player* Board::getPlayerBlack() {
    if (p1->getColor() == Color::BLACK) {
        return p1;
    } else {
        return p2;
    }
}

Player* Board::getPlayerWhite() {
    if (p1->getColor() == Color::WHITE) {
        return p1;
    } else {
        return p2;
    }
}
