#include "player.h"
#include "piece.h"

using namespace std;

bool Player::move(istream &in) {
    Move next = getNextMove(in);
    return b->move(const_cast<Piece*>(next.p), next.r0, next.c0);
}

Board *Player::getBoard() const {
    return b;
}

void Player::setColor(Color c){ color = c; };
Color Player::getColor() { return color; };
