#include "computer.h"

Move Computer::getNextMove(istream &in) const {
    Move bestMove = {0, 0, 0, 0};
    int bestScore = -1;
    auto board = getBoard()->getBoard();
    for (auto row:board) {
        for (auto piece:row) {
            if (!piece || piece->getColor() != getColor()) continue;
            auto moves = piece->getPossibleMoves(board);
            for (auto move:moves) {
                int score = rankMove(move);
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = move;
                }
            }
        }
    }
    std::cout << bestMove.c0 << bestMove.r0 << std::endl;
    return bestMove;
}

vector<vector<bool>> Computer::getThreatBoard() const {
    auto theBoard = getBoard()->getBoard();
    vector<vector<bool>> threat (8, vector<bool> (8, false));
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            auto piece = theBoard[row][col];
            if (!piece || piece->getColor() == getColor()) continue;
            for (auto move:theBoard[row][col]->getPossibleMoves(theBoard)) {
                threat[move.r1][move.c1] = true;
            }
        }
    }
    return threat;
}

int Level1::rankMove(const Move &move) const {
    return getColor() == Color::BLACK? move.r1 : 7-move.r1;
}


int Level2::rankMove(const Move &move) const {
    if (move.captures) {
        if (move.captures->pieceType() == PieceType::KING) return 9;
        return 8;
    }
    return getColor() == Color::BLACK? move.r1 : 7-move.r1;
}