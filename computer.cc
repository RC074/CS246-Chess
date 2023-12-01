#include "computer.h"

Move Level1::getNextMove() {
    auto board = getBoard()->getBoard();
    for (auto row:board) {
        for (auto piece:row) {
            if (!piece) continue;
            auto moves = piece->getPossibleMoves(board);
            if (moves.size() == 0) continue;
            return moves[0];
        }
    }
}