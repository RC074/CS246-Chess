#include "computer.h"

PlayerType Computer::playerType() const {
    return PlayerType::COMPUTER;
}

Move Computer::getNextMove(istream &in) const {
    vector<vector<bool>> threat = getThreatBoard();
    Move bestMove = {0, 0, 0, 0};
    int bestScore = -1;
    auto board = getBoard()->getBoard();
    for (auto row:board) {
        for (auto piece:row) {
            if (!piece || piece->getColor() != getColor()) continue;
            auto moves = piece->getPossibleMoves(board);
            int r = piece->getRow();
            int c = piece->getCol();
            for (auto move:moves) {
                if (move.r1 < 0 || move.r1 > 8 || move.c1 < 0 || move.c1 > 8) {
                    continue;
                }
                int score = rankMove(move, threat);
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

int Level1::rankMove(const Move &move, BoolBoard &threat) const {
    return getColor() == Color::BLACK? move.r1 : 7-move.r1;
}


int Level2::rankMove(const Move &move, BoolBoard &threat) const {
    if (move.captures) {
        if (move.captures->pieceType() == PieceType::KING) return 9;
        return 8;
    }
    return getColor() == Color::BLACK? move.r1 : 7-move.r1;
}

int Level3::rankMove(const Move &move, BoolBoard &threat) const {
    if (threat[move.r1][move.c1]) return 0;
    if (threat[move.r0][move.c0]) return 11;
    if (move.captures) {
        if (move.captures->pieceType() == PieceType::KING) return 10;
        return 9;
    }
    return getColor() == Color::BLACK? move.r1 + 1 : 8-move.r1;
}

int Level4::rankMove(const Move &move, BoolBoard &threat) const {

}