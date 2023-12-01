#include "pawn.h"

Pawn::Pawn(int row, int col, Color color):Piece{row, col, color} {}

Pawn::~Pawn() {
}

void Pawn::notify(Piece &p) {
    // Implement the logic to handle the notification from another piece
}

PieceType Pawn::pieceType() const {
    return PieceType::PAWN;
}


std::vector<Move> Pawn::getPossibleMoves(std::vector<std::vector<Piece*> > board, bool moved) const {
    std::vector<Move> moves;

    int direction = (this->getColor() == Color::WHITE) ? -1 : 1; // Assuming white pawns move up (decrease in row)

    int currentRow = getRow();
    int currentCol = getCol();

    int newRow = currentRow + direction;
    if (newRow >= 0 && newRow < 8) {
        Piece *targetPiece = board[newRow][currentCol];
        if (!targetPiece || targetPiece->getColor() != this->getColor()) {
            moves.push_back({currentRow, currentCol, newRow, currentCol, targetPiece, this});
        }
        targetPiece = board[newRow][currentCol-1];
        if (targetPiece && targetPiece->getColor() != this->getColor()) {
          moves.push_back({currentRow, currentCol, newRow, currentCol-1, targetPiece, this});
        }
        targetPiece = board[newRow][currentCol+1];
        if (targetPiece && targetPiece->getColor() != this->getColor()) {
          moves.push_back({currentRow, currentCol, newRow, currentCol+1, targetPiece, this});
        }
        if (!moved) {
          newRow += direction;
          if (newRow >= 0 && newRow < 8) {
              targetPiece = board[newRow][currentCol];
              if (!targetPiece || targetPiece->getColor() != this->getColor()) {
                  moves.push_back({currentRow, currentCol, newRow, currentCol, targetPiece, this});
              }
          }
        }
      }
      return moves;
    }
