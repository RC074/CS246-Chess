#include "king.h"

King::King(int row, int col, Color color):Piece{row, col, color} {}

King::~King() {
}

void King::notify(Piece &p) {
    // Implement the logic to handle the notification from another piece
}

PieceType King::pieceType() const {
    return PieceType::KING;
}


std::vector<Move> King::getPossibleMoves(std::vector<std::vector<Piece> > board) const {
    std::vector<Move> moves;

    return moves;
}

// You would also need to include any other methods that are specific to the King
// For example, if you have a method to check if castling is possible, it would go here
