#include "queen.h"

Queen::Queen(int row, int col, Color color):Piece{row, col, color} {}

Queen::~Queen() {
}

void Queen::notify(Piece &p) {
    // Implement the logic to handle the notification from another piece
}

PieceType Queen::pieceType() const {
    return PieceType::QUEEN;
}


std::vector<Move> Queen::getPossibleMoves(std::vector<std::vector<Piece*> > board) const {
    std::vector<Move> moves;

    // Define all possible directions the queen can move: vertical, horizontal, and diagonal
    const int directions[8][2] = {
        {-1, -1},
        {-1, 0}, 
        {-1, 1}, 
        {0, -1}, 
        {0, 1},   
        {1, -1},  
        {1, 0}, 
        {1, 1}   
    };

    int currentRow = getRow();
    int currentCol = getCol();

    for (const auto &direction : directions) {
        int newRow = currentRow + direction[0];
        int newCol = currentCol + direction[1];

        while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            Piece *targetPiece = board[newRow][newCol];
            if (!targetPiece || targetPiece->getColor() != this->getColor()) {
                moves.push_back({currentRow, currentCol, newRow, newCol, targetPiece, this});
                if (targetPiece && targetPiece->getColor() != this->getColor()) {
                    break;
                }
            } else {
              break;
            }
            newRow += direction[0];
            newCol += direction[1];
        }
    }

    return moves;
}
