#include "knight.h"

Knight::Knight(int row, int col, Color color):Piece{row, col, color} {}

Knight::~Knight() {
}

void Knight::notify(Piece &p) {
    // Implement the logic to handle the notification from another piece
}

PieceType Knight::pieceType() const {
    return PieceType::KNIGHT;
}


std::vector<Move> Knight::getPossibleMoves(std::vector<std::vector<Piece*> > board) const {
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

    // Get the Knight's current position (row, col)
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
