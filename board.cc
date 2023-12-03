#include "board.h"
// #include "piece.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "pawn.h"

using namespace std;
using Point = pair<int, int>;
using Row = vector<Piece *>;

void Board::removePieceAt(int row, int col) {
    if (!theBoard[row][col]) return;
    delete theBoard[row][col];
    theBoard[row][col] = nullptr;
}

void Board::setPieceAt(PieceType pt, int row, int col, Color c) {
    Piece *newPiece;
    if (pt == PieceType::KING) {
        newPiece = new King {row, col, c};
    }
    else if (pt == PieceType::BISHOP) newPiece = new Bishop {row, col, c};
    else if (pt == PieceType::KNIGHT) newPiece = new Knight {row, col, c};
    else if (pt == PieceType::PAWN) newPiece = new Pawn {row, col, c};
    else if (pt == PieceType::QUEEN) newPiece = new Queen {row, col, c};
    else if (pt == PieceType::ROOK) newPiece = new Rook {row, col, c}; 
    else return;
    
    // put piece into the board
    removePieceAt(row, col);
    theBoard[row][col] = newPiece;
}
// black pieces on the top, rows and cols indexed from 0-7
Piece *defaultConstructPiece(int row, int col) {
    if (!(row <= 7 && row >= 0)) throw std::out_of_range{
        "rows and cols indexed from 0-7"
    };
    if (row > 1 && row < 6) return nullptr;

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

Board::Board(): 
    theBoard{vector<Row>(BOARD_SIZE, Row(BOARD_SIZE, nullptr))},
    td{new TextDisplay{BOARD_SIZE}}, 
    winner{Color::NO_COLOR} {}

Board::~Board() {
    clearBoard();
    delete td;
    td = nullptr;
}

void Board::init(Player &blackPlayer, Player &whitePlayer, 
                 bool useStandard) {
    clearBoard();

    // the board is filled with nullptr now
    this->blackPlayer = &blackPlayer;
    this->whitePlayer = &whitePlayer;
    blackPlayer.setColor(Color::BLACK);
    whitePlayer.setColor(Color::WHITE);
    delete td;
    td = new TextDisplay(BOARD_SIZE);
    if (!useStandard) return;
    for (int row = 0; row < theBoard.size(); ++row) {
        for (int col = 0; col < theBoard[row].size(); ++col) {
            auto newPiece = defaultConstructPiece(row, col);
            if (Point{row, col} == Point{0, 4}) {
                blackKing = dynamic_cast<King *>(newPiece);
            } else if (Point{row, col} == Point{7, 4}) {
                whiteKing = dynamic_cast<King *>(newPiece);
            }
            theBoard[row][col] = newPiece;
            td->notify(Move{row, col, row, col, nullptr, theBoard[row][col]});
            if (theBoard[row][col]) theBoard[row][col]->attach(td);
        }
    }
}


bool Board::validateBoard() {
    int bKingCount = 0;
    int wKingCount = 0;
    King *tmpBlackKing = nullptr;
    King *tmpWhitekKing = nullptr;
    for (auto row:theBoard) {
        for (auto piece:row) {
            if (piece->pieceType() == PieceType::KING) {
                if (piece->getColor() == Color::BLACK) {
                    bKingCount++;
                    tmpBlackKing = dynamic_cast<King *>(piece);
                } else {
                    wKingCount++;
                    tmpWhitekKing = dynamic_cast<King *>(piece);
                }
            }
            if (piece->pieceType() == PieceType::PAWN && 
                (piece->getRow() == 0 || piece->getRow() == 7)) {
                    return false;
            }
        }
    }
    if (bKingCount != 1 || wKingCount != 1) return false;
    blackKing = tmpBlackKing;
    whiteKing = tmpWhitekKing;
    return true;
}

void Board::updateWin() {
    if (blackKing->getIsCaptured()) {
        winner = Color::BLACK;
    } else if (whiteKing->getIsCaptured()) {
        winner = Color::WHITE;
    } else {
        winner = Color::NO_COLOR;
    }
}


void Board::clearBoard() {
    for (int i = 0; i < theBoard.size(); ++i) {
        for (int j = 0; j < theBoard[i].size(); ++j) {
            delete theBoard[i][j];
            theBoard[i][j] = nullptr;
        }
    }
    winner = Color::NO_COLOR;
}

bool Board::move(Piece *pieceToMove, int row, int col) {
    // we check if the move is a valid move
    // if it is, we add the move to the stack ian the form [r1, c1, r2, c2]
    if (!pieceToMove) return false;
    vector<Move> moves = pieceToMove->getPossibleMoves(theBoard);
    bool moved = false;
    for (Move m : moves) {
        if (m.r1 == row && m.c1 == col) {
            pieceToMove->setPosition(row, col);
            theBoard[m.r0][m.c0] = nullptr;
            theBoard[m.r1][m.c1] = pieceToMove;
            if (m.captures) {
                Piece *capturedPiece = m.captures;
                capturedPiece->setIsCaptured(true);

                // Move m = getPreviousMove();
                capturedPiece->notifyAllObservers(m);
            }
            // Move m = getPreviousMove();
            pieceToMove->notifyAllObservers(m);
            moved = true;
            break;
        }
    }
    if (!moved) return false;
    updateWin();
    return true;
    
}

bool Board::move(int r0, int c0, int r1, int c1) {
    Piece *p = getPieceAt(r0, c0);
    return move(p, r1, c1);
}

Piece* Board::getPieceAt(int row, int col) {
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
    return blackPlayer;
}

Player* Board::getPlayerWhite() {
    return whitePlayer;
}

ostream &operator<<(ostream &out, const Board &b) {
    out << *b.td;
    return out;
}
