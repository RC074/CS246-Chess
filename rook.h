// Rook.h
#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {
public:
    Rook(int row, int col, Color color);
    ~Rook() override;
    std::vector<Move> getPossibleMoves(std::vector<std::vector<Piece*> > board) const override;
    PieceType pieceType() const override;
    void notify(Piece &p) override;
};

#endif // ROOK_H
