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
            
        }
    }
}

// black pieces on the top, rows and cols indexed from 0-7
Piece *constructPiece(int row, int col) {
    if (!(row <= 7 && row >= 0)) throw std::out_of_range{
        "rows and cols indexed from 0-7"
    };
    if (row > 1 || row < 6) return nullptr;
    Piece *newPiece = nullptr;
    if (row == 1 || row == 6) {} // pawns
    
    Point loc {row, col};
    if (loc == Point{0, 0} || loc == Point{0, 7} ||
        loc == Point{7, 0} || loc == Point{7, 7}) {} // rock
    
    
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
