#include "player.h"

using namespace std;

bool Player::move(istream &in, bool useStandard) {
    Move next = getNextMove(in);

    Piece *p = b->getPieceAt(next.r0, next.c0);
    if (!p || p->getColor() != getColor()) return false;
    if (useStandard) {
        if (p->pieceType() == PieceType::KING && !p->getMoved()) {
            if ((next.r1 == 7 && next.c1 == 6) || (next.r1 == 0 && next.c1 == 6) || (next.r1 == 7 && next.c1 == 2) || (next.r1 == 0 && next.c1 == 2)) {
                King *k = dynamic_cast<King *>(p);
                b->updateDangerZone(Color::BLACK);
                b->updateDangerZone(Color::WHITE);
                return k->castling(b->getBoard(), b->getDangerZone(k->getColor() == Color::BLACK ? Color::WHITE : Color::BLACK), k, next.r1+next.c1);
            }
        }
    }
    return b->move(p, next.r1, next.c1, next.promotion);
}

void Player::setBoard(Board *b) {
    this->b = b;
}

Board *Player::getBoard() const {
    return b;
}

void Player::setColor(Color c){ color = c; };
Color Player::getColor() const { return color; };
