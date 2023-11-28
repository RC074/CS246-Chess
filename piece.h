// Piece.h
#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "observer.h"

enum class PieceType { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, NONE };
enum class Color { WHITE, BLACK, NO_COLOR };

struct Move {
    int row, col;
    Piece *p;
};

class Piece {
  int row;
  int col;
<<<<<<< HEAD
  PieceType pt;
=======
  Color color;
  std::vector<Observer> observers;
>>>>>>> e6d26f07425d90094ec30c683540acec27f8cd8e
public:
    Piece(int row, int col, Color color);
    virtual ~Piece() = default;
    virtual void notify(Piece &p) = 0;
<<<<<<< HEAD
    PieceType pieceType() const;
    Color getColor() const;
    virtual std::vector<Move> getPossibleMoves() const = 0;
    // Other methods can be declared here
=======
    virtual PieceType pieceType() const = 0;
    Color getColor() const;
    int getRow() const;
    int getCol() const;
    void setPosition(int r, int c);
    void notifyAllObservers();
    virtual std::vector<Move> getPossibleMoves(std::vector<std::vector<Piece> > board) const = 0;
>>>>>>> e6d26f07425d90094ec30c683540acec27f8cd8e
};

#endif
