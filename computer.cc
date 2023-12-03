#include "computer.h"

vector<vector<bool>> Computer::getCaptureBoard() const {
    auto theBoard = getBoard()->getBoard();
    vector<vector<bool>> capture (8, vector<bool> (8, false));
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            auto piece = theBoard[row][col];
            if (!piece || piece->getColor() != getColor()) continue;
            for (auto move:theBoard[row][col]->getPossibleMoves(theBoard)) {
                capture[move.r1][move.c1] = true;
            }
        }
    }
    return capture;
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

Move Level1::getNextMove(istream &in) {
    auto board = getBoard()->Board::getBoard();
    for (auto row:board) {
        for (auto piece:row) {
            if (!piece) continue;
            auto moves = piece->getPossibleMoves(board);
            if (moves.size() == 0) continue;
            return moves[0];
        }
    }
}


Move Level2::getNextMove(istream &in) {
    Move bestMove = {0, 0, 0, 0};
    int bestScore = -1;
    auto board = getBoard()->getBoard();
    auto capture = getCaptureBoard();
    for (auto row:board) {
        for (auto piece:row) {
            if (!piece) continue;
            auto moves = piece->getPossibleMoves(board);
            for (auto move:moves) {
                if (move.captures->pieceType() == PieceType::KING) {
                    return move;
                }
                int score = move.captures ? 1 : 0;
                if (score > bestScore) {
                    bestMove = move;
                    bestScore = score;
                }
            }
        }
    }
    return bestMove;
}