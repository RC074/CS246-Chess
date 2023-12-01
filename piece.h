// Piece.h
#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "observer.h"

enum class PieceType { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, NONE };
enum class Color { WHITE, BLACK, NO_COLOR };

struct Move {
    int r0, c0, r1, c1;
    Piece *captures;
    const Piece *p;
    
};

class Piece {
  int row;
  int col;
  Color color;
  std::vector<Observer> observers;
  bool isCaptured = false;
public:
    Piece(int row, int col, Color color);
    virtual ~Piece() = default;
    virtual void notify(Piece &p) = 0;
    virtual PieceType pieceType() const = 0;
    Color getColor() const;
    int getRow() const;
    int getCol() const;
    void setPosition(int r, int c);
    void notifyAllObservers();
    void attach(Observer *ob);
    virtual std::vector<Move> getPossibleMoves(std::vector<std::vector<Piece*> > board) const = 0;
    void setIsCaptured(bool t);
};

#endif
