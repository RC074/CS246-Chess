// King.h
#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
public:
    King(int row, int col, Color color);
    ~King() override;
    std::vector<Move> getPossibleMoves(std::vector<std::vector<Piece> > board) const override;
    PieceType pieceType() const override;
    void notify(Piece &p) override;
};

#endif // KING_H
