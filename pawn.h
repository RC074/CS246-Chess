// Pawn.h
#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
    bool justMovedTwoCells = false;
public:
    bool hasJustMovedTwoCells() const;
    void resetFlag();
    void setMovedTwoCells();
    Pawn(int row, int col, Color color);
    ~Pawn() override;
    std::vector<Move> getPossibleMoves(std::vector<std::vector<Piece*>> board, bool potential=false) const override;
    std::vector<Move> getThreat();
    PieceType pieceType() const override;
    void notify(Piece &p) override;
};

#endif // PAWN_H
