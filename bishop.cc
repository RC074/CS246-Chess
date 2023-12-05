#include "bishop.h"

Bishop::Bishop(int row, int col, Color color):Piece{row, col, color} {}

Bishop::~Bishop() {
}

void Bishop::notify(Piece &p) {
    // Implement the logic to handle the notification from another piece
}

PieceType Bishop::pieceType() const {
    return PieceType::BISHOP;
}


std::vector<Move> Bishop::getPossibleMoves(std::vector<std::vector<Piece*> > board, bool potential) const {
    std::vector<Move> moves;

    const int directions[4][2] = {
        {-1, -1},
        {-1, 1},  
        {1, -1},  
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
                if (potential) moves.push_back({currentRow, currentCol, newRow, newCol, targetPiece, this});
                break;
            }

            newRow += direction[0];
            newCol += direction[1];
        }
    }

    return moves;
}
