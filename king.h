// King.h
#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
public:
    King(int row, int col, Color color);
    ~King() override;
    std::vector<Move> getPossibleMoves(std::vector<std::vector<Piece*> > board) const override;
    bool castling(std::vector<std::vector<Piece*> > &board, std::vector<std::vector<bool>> dangerZone, King *king, int destination);
    PieceType pieceType() const override;
    void notify(Piece &p) override;
};

#endif // KING_H
