#include "king.h"
struct Move;

King::King(int row, int col, Color color):Piece{row, col, color} {}

King::~King() {
}

void King::notify(Piece &p) {
    
}



PieceType King::pieceType() const {
    return PieceType::KING;
}


std::vector<Move> King::getPossibleMoves(std::vector<std::vector<Piece*> > board) const {
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

    // Get the king's current position (row, col)
    int currentRow = getRow();
    int currentCol = getCol();

    for (const auto &direction : directions) {
        int newRow = currentRow + direction[0];
        int newCol = currentCol + direction[1];

        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            Piece *targetPiece = board[newRow][newCol];
            if (!targetPiece || targetPiece->getColor() != this->getColor()) {
                moves.push_back({currentRow, currentCol, newRow, newCol, targetPiece, this});
            }
            
        }
    }

    return moves;
}


bool King::castling(std::vector<std::vector<Piece*> > board, std::vector<std::vector<bool>> dangerZone, King *king, int destination) {
    int king_r = king->getRow();
    int king_c = king->getCol();
    if (destination == 6 || destination == 13) {
        if (!board[king_r][king_c+1] && !board[king_r][king_c+2]) {
            if (dangerZone[king_r][king_c+1] && dangerZone[king_r][king_c+2]) {
                Piece *rook = board[king_r][king_c+3];
                if (rook->getMoved()) return false;
                board[king_r][king_c+1] = rook;
                board[king_r][king_c+2] = king;
                rook->setMoved();
                rook->setPosition(king_r, king_c+1);
                rook->notifyAllObservers(Move{king_r, king_c+3, king_r, king_c+1, nullptr, rook});
                king->setMoved();
                king->setPosition(king_r, king_c+2);
                king->notifyAllObservers(Move{king_r, king_c, king_r, king_c+2, nullptr, king});
                
                return true;
            }
        }
    } else {
        if (!board[king_r][king_c-1] && !board[king_r][king_c-2]) {
            if (dangerZone[king_r][king_c-1] && dangerZone[king_r][king_c-2]) {
                Piece *rook = board[king_r][king_c-4];
                if (rook->getMoved()) return false;
                board[king_r][king_c-1] = rook;
                board[king_r][king_c-2] = king;
                rook->setMoved();
                rook->setPosition(king_r, king_c-1);
                rook->notifyAllObservers(Move{king_r, king_c-4, king_r, king_c-1, nullptr, rook});
                king->setMoved();
                king->setPosition(king_r, king_c-2);
                king->notifyAllObservers(Move{king_r, king_c, king_r, king_c-2, nullptr, king});
                return true;
            }
        }
    }
    return false;
}
