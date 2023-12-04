// Piece.h
#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "observer.h"

enum class PieceType { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, NONE };
enum class Color { WHITE, BLACK, NO_COLOR };

class Piece;
struct Move {
    int r0, c0, r1, c1;
    Piece *captures = nullptr;
    const Piece *p = nullptr;
    PieceType promotion = PieceType::NONE;
};

class Piece {
  int row;
  int col;
  Color color;
  std::vector<Observer*> observers;
  bool isCaptured = false;
  bool moved = false;
public:
    bool getMoved() const;
    void setMoved(); // only sets moved to true
    bool getIsCaptured() const;
    Piece(int row, int col, Color color);
    virtual ~Piece() = default;
    virtual void notify(Piece &p) = 0;
    virtual PieceType pieceType() const = 0;
    Color getColor() const;
    int getRow() const;
    int getCol() const;
    void setPosition(int r, int c);
    void notifyAllObservers(Move m);
    void attach(Observer *ob);
    virtual std::vector<Move> getPossibleMoves(std::vector<std::vector<Piece*> > board) const = 0;
    void setIsCaptured(bool t);
};

#endif
