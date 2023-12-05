// Bishop.h
#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
public:
    Bishop(int row, int col, Color color);
    ~Bishop() override;
    std::vector<Move> getPossibleMoves(std::vector<std::vector<Piece*> > board, bool potential) const override;
    PieceType pieceType() const override;
    void notify(Piece &p) override;
};

#endif // BISHOP_H
