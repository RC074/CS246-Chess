#include "computer.h"

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