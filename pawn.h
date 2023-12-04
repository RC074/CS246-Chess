// Pawn.h
#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
public:
    Pawn(int row, int col, Color color);
    ~Pawn() override;
    std::vector<Move> getPossibleMoves(std::vector<std::vector<Piece*>> board) const override;
    std::vector<Move> getThreat(std::vector<std::vector<Piece*>> board);
    PieceType pieceType() const override;
    void notify(Piece &p) override;
};

#endif // PAWN_H
