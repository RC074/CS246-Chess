#include "rook.h"

Rook::Rook(int row, int col, Color color):Piece{row, col, color} {}

Rook::~Rook() {
}

void Rook::notify(Piece &p) {
    // Implement the logic to handle the notification from another piece
}

PieceType Rook::pieceType() const {
    return PieceType::ROOK;
}


std::vector<Move> Rook::getPossibleMoves(std::vector<std::vector<Piece*> > board) const {
    std::vector<Move> moves;

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

    // Get the Rook's current position (row, col)
    int currentRow = getRow();
    int currentCol = getCol();

    for (const auto &direction : directions) {
        int newRow = currentRow + direction[0];
        int newCol = currentCol + direction[1];

        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            Piece *targetPiece = board[newRow][newCol];
            if (targetPiece->getColor() != this->getColor()) {
                moves.push_back({currentRow, currentCol, newRow, newCol, targetPiece, this});
            }
            
        }
    }

    return moves;
}
