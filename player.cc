#include "player.h"

using namespace std;

bool Player::move(istream &in) {
    Move next = getNextMove(in);
    Piece *p = b->getPieceAt(next.r0, next.c0);
    if (!p || p->getColor() != getColor()) return false;
    return b->move(next.r0, next.c0, next.r1, next.c1, next.promotion);
}

void Player::setBoard(Board *b) {
    this->b = b;
}

Board *Player::getBoard() const {
    return b;
}

void Player::setColor(Color c){ color = c; };
Color Player::getColor() const { return color; };
