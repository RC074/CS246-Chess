#include "player.h"
#include "piece.h"

using namespace std;

bool Player::move(istream &in) {
    Move next = getNextMove(in);
    return b->move(next.r0, next.c0, next.r1, next.c1);
}

void Player::setBoard(Board *b) {
    this->b = b;
}

Board *Player::getBoard() const {
    return b;
}

void Player::setColor(Color c){ color = c; };
Color Player::getColor() const { return color; };
