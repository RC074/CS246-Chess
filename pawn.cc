#include "pawn.h"

using namespace std;

Pawn::Pawn(int row, int col, Color color):Piece{row, col, color} {}

Pawn::~Pawn() {
}

void Pawn::notify(Piece &p) {
    // Implement the logic to handle the notification from another piece
}

PieceType Pawn::pieceType() const {
    return PieceType::PAWN;
}

vector<Move> Pawn::getThreat() {
    vector <Move> moves {};
    int direction = (this->getColor() == Color::WHITE) ? -1 : 1;
    if (getRow() + direction > 7 || getRow() + direction < 0) return moves;
    if (getCol() > 0) {
        moves.emplace_back(Move{getRow(), getCol(), getRow()+direction, getCol()-1, nullptr, this});
    }
    if (getCol() < 7) {
        moves.emplace_back(Move{getRow(), getCol(), getRow()+direction, getCol()+1, nullptr, this});
    }
    return moves;
}




vector<Move> Pawn::getPossibleMoves(std::vector<std::vector<Piece*> > board, bool potential) const {
    vector<Move> moves;
    int direction = (this->getColor() == Color::WHITE) ? -1 : 1; // Assuming white pawns move up (decrease in row)

    int currentRow = getRow();
    int currentCol = getCol();

    int newRow = currentRow + direction;
    if (newRow >= 0 && newRow < 8) {
        Piece *targetPiece = board[newRow][currentCol];
        if (!targetPiece) {
            moves.push_back({currentRow, currentCol, newRow, currentCol, targetPiece, this});
        }
        if (currentCol-1 >= 0) {
            targetPiece = board[newRow][currentCol-1];
            if (targetPiece && targetPiece->getColor() != this->getColor()) {
                moves.push_back({currentRow, currentCol, newRow, currentCol-1, targetPiece, this});
            }
        }
        if (currentCol+1 < 8) {
            targetPiece = board[newRow][currentCol+1];
            if (targetPiece && targetPiece->getColor() != this->getColor()) {
                moves.push_back({currentRow, currentCol, newRow, currentCol+1, targetPiece, this});
            }
        }
        if (!getMoved()) {
          newRow += direction;
          if (newRow >= 0 && newRow < 8) {
              targetPiece = board[newRow][currentCol];
              if (!targetPiece && !board[newRow-direction][currentCol]) {
                  moves.push_back({currentRow, currentCol, newRow, currentCol, targetPiece, this});
              }
          }
        }
    }
    return moves;
}

