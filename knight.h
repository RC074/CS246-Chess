// Knight.h
#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {
public:
    Knight(int row, int col, Color color);
    ~Knight() override;
    std::vector<Move> getPossibleMoves(std::vector<std::vector<Piece*> > board, 
        bool potential=false) const override;
    PieceType pieceType() const override;
    void notify(Piece &p) override;
};

#endif // KNIGHT_H
