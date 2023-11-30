// Piece.h
#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "observer.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "pawn.h"

enum class PieceType { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, NONE };
enum class Color { WHITE, BLACK, NO_COLOR };

struct Move {
    int row, col;
    int action; // 0 for going to empty, 1 for capture
    const Piece *p;
    
};

class Piece {
  int row;
  int col;
  Color color;
  std::vector<Observer> observers;
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
    virtual std::vector<Move> getPossibleMoves(std::vector<std::vector<Piece*> > board) const = 0;
};

#endif
