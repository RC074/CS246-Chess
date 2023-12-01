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

     const int movesOffset[8][2] = {
        {-2, -1}, {-1, -2},
        {-2, 1},  {-1, 2},
        {1, -2},  {2, -1},
        {1, 2},   {2, 1}
    };

    int currentRow = getRow();
    int currentCol = getCol();

    for (const auto &offset : movesOffset) {
        int newRow = currentRow + offset[0];
        int newCol = currentCol + offset[1];

        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            Piece *targetPiece = board[newRow][newCol];
            if (!targetPiece || targetPiece->getColor() != this->getColor()) {
                moves.push_back({currentRow, currentCol, newRow, newCol, targetPiece, this});
            }
        }
    }

    return moves;
}
