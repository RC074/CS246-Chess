#include "board.h"
#include "piece.h"

using namespace std;
using Point = pair<int, int>;

Board::Board(Player *p1, Player *p2) : 
        p1{p1}, p2{p2}, 
        theBoard{vector<vector<Piece *>>(BOARD_SIZE, 
            vector<Piece *>(BOARD_SIZE, nullptr))}
    {}

void Board::init(bool p1White) {
    clearBoard();
    // the board is filled with nullptr now
    p1->setColor((p1White ? Color::WHITE : Color::BLACK));
    p1->setColor(((!p1White) ? Color::WHITE : Color::BLACK));
    for (int row = 0; row < theBoard.size(); ++row) {
        for (int col = 0; col < theBoard[row].size(); ++col) {
            theBoard[row][col] = defaultConstructPiece(row, col);
        }
    }
}

// black pieces on the top, rows and cols indexed from 0-7
Piece *defaultConstructPiece(int row, int col) {
    if (!(row <= 7 && row >= 0)) throw std::out_of_range{
        "rows and cols indexed from 0-7"
    };
    if (row > 1 || row < 6) return nullptr;

    Color color = (row <= 5) ? Color::BLACK : Color::WHITE;
    // pawns
    if (row == 1 || row == 6) return new Pawn {row, col, color};
    
    Point loc {row, col};
    // rooks
    if (loc == Point{0,0} || loc == Point{0,7} ||
        loc == Point{7,0} || loc == Point{7,7}) {
            return new Rook {row, col, color};
    }
    // knights
    if (loc == Point{0,1} || loc == Point{0,6} ||
        loc == Point{7,1} || loc == Point{7,6}) {
            return new Knight {row, col, color};
    }

    // Bishops
    if (loc == Point{0,2} || loc == Point{0,5} ||
        loc == Point{7,2} || loc == Point{7, 5}) {
            return new Bishop {row, col, color};
    }

    // Queens
    if (loc == Point{0,3} || loc == Point{7,3}) {
        return new Queen {row, col, color};
    }
    
    // Kings
    if (loc == Point{0,4} || loc == Point{7,4}) {
        return new King {row, col, color};
    }
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

bool Board::move(Piece *pieceToMove, int row, int col) {
    // we check if the move is a valid move
    // if it is, we add the move to the stack ian the form [r1, c1, r2, c2]
    if (!pieceToMove) return false;
    vector<Move> moves = pieceToMove->getPossibleMoves(theBoard);
    for (Move m : moves) {
        if (m.r1 == row && m.c1 == col) {
            pieceToMove->setPosition(row, col);
            if (m.captures) {
                Piece *capturedPiece = m.captures;
                capturedPiece->setIsCaptured(true);
                capturedPiece->notifyAllObservers();
            }
            pieceToMove->notifyAllObservers();
        }
    }
    
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