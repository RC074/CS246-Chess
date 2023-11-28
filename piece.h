// Piece.h
#ifndef PIECE_H
#define PIECE_H

#include <vector>

enum class PieceType { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, NONE };
enum class Color { WHITE, BLACK, NO_COLOR };

struct Move {
    int row, col;
    Piece *p;
};

class Piece {
  int row;
  int col;
  PieceType pt;
public:
    Piece(int row, int c);
    virtual ~Piece() = default;
    virtual void notify(Piece &p) = 0;
    PieceType pieceType() const;
    Color getColor() const;
    virtual std::vector<Move> getPossibleMoves() const = 0;
    // Other methods can be declared here
};

class King : public Piece {
public:
    std::vector<Move> getPossibleMoves() const override;
    // Other King-specific methods and members
};

class Queen : public Piece {
public:
    std::vector<Move> getPossibleMoves() const override;
    // Other Queen-specific methods and members
};

// ... Other pieces follow a similar pattern ...

#endif // PIECE_H
