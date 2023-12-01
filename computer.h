#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "player.h"

class Computer: public Player {
    Move bestNextMove;
protected:
    virtual int RankMove(Move &move) const = 0;
    Move getNextMove() override;
};

class Level1: public Computer {
protected:
    int RankMove(Move &move) const override;
};

class Level2: public Computer {
protected:
    int RankMove(Move &move) const override;
};

#endif
