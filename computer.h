#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "player.h"

class Computer: public Player {
protected:
    Move bestNextMove;
};

class Level1: public Computer {
protected:
    Move getNextMove() override;
};

class Level2: public Computer {
protected:
    Move getNextMove() override;
};

class Level3: public Computer {
protected:
    Move getNextMove() override;
};

#endif
