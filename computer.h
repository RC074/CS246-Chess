#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "player.h"

class Computer: public Player {
protected:
    void getNextMove() override;
};

#endif
