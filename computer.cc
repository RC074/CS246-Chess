#include "computer.h"

std::map<PieceType, int> PieceValues {
    {PieceType::PAWN, 1},
    {PieceType::KNIGHT, 3},
    {PieceType::BISHOP, 3},
    {PieceType::ROOK, 5},
    {PieceType::QUEEN, 9}
};


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
            for (auto move:moves) {
                if (getBoard()->leadsToCheck(move)) continue;
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
    if (bestMove.p->pieceType() == PieceType::PAWN &&
        (bestMove.r1 == 0 || bestMove.r1 == 7)) 
            bestMove.promotion = PieceType::QUEEN;
    return bestMove;
}

vector<vector<bool>> Computer::getThreatBoard() const {
    auto theBoard = getBoard()->getBoard();
    vector<vector<bool>> threat (8, vector<bool> (8, false));
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            auto piece = theBoard[row][col];
            if (!piece || piece->getColor() == getColor()) continue;
            auto threats = theBoard[row][col]->getPossibleMoves(theBoard, true);
            if (piece->pieceType() == PieceType::PAWN) {
                Pawn *pawn = dynamic_cast<Pawn *> (piece);
                threats = pawn->getThreat();
            }
            for (auto move:threats) {
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
        if (move.captures->pieceType() == PieceType::KING) return 12;
        return 9;
    }
    return getColor() == Color::BLACK? move.r1 + 1 : 8-move.r1;
}

int Level4::developmentScore(Move m) const {
    int score = 0;
    vector<vector<Piece *>> imagination = getBoard()->getBoard();
    Piece *pieceToMove = imagination[m.r0][m.c0];
    BoolBoard dBoard = BoolBoard(8, vector<bool> (8, false));
    imagination[m.r0][m.c0] = nullptr;
    imagination[m.r1][m.c1] = pieceToMove;
    pieceToMove->setPosition(m.r1, m.c1);
    for (auto row:imagination) {
        for (auto p:row) {
            if (!p || p->getColor() != getColor()) continue;
            auto threats = p->getPossibleMoves(imagination);
            if (p->pieceType() == PieceType::PAWN) {
                Pawn *pawn = dynamic_cast<Pawn *> (p);
                threats = pawn->getThreat();
            }
            for (auto move:p->getPossibleMoves(imagination)) {
                dBoard[move.r1][move.c1] = true;
                if (move.captures) {
                    score += PieceValues[move.captures->pieceType()];
                    if (move.captures->pieceType() == PieceType::KING) {
                        score += 10;
                    }
                } else if (imagination[move.r1][move.c1]) {
                    score += PieceValues[imagination[move.r1][move.c1]->pieceType()];
                }
            }
        }
    }
    for (auto row:dBoard) {
        for (auto p:row) {
            if (p) ++score;
        }
    }
    pieceToMove->setPosition(m.r0, m.c0);
    return score;
}

int Level4::rankMove(const Move &move, BoolBoard &threat) const {
    if (move.captures && !threat[move.r1][move.c1]) return 200 + PieceValues[move.p->pieceType()];
    int captureScore = (move.captures) ? 
        PieceValues[move.captures->pieceType()] : 0;
    if (threat[move.r1][move.c1]) captureScore -= PieceValues[move.p->pieceType()];
    if (captureScore > 0) return 101 + captureScore;
    if (captureScore < 0) return 0;
    if (threat[move.r0][move.c0] && !threat[move.r1][move.c1]) return 100+PieceValues[move.p->pieceType()];
    // if (move.captures) {
    //     if (move.captures->pieceType() == PieceType::KING) return 12;
    //     return 9;
    // }
    int score = getColor() == Color::BLACK? 
        move.r1 + 1 - abs(4-move.c1) : 8-move.r1 - abs(4-move.c1);
    score += developmentScore(move);
    return score;
}
