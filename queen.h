// Queen.h
#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {
public:
    Queen(int row, int col, Color color);
    ~Queen() override;
    std::vector<Move> getPossibleMoves(std::vector<std::vector<Piece*> > board, bool potential=false) const override;
    PieceType pieceType() const override;
    void notify(Piece &p) override;
};

#endif // QUEEN_H
