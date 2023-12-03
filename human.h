#ifndef __HUMAN_H__
#define __HUMAN_H__
#include <iostream>
#include "player.h"

class Human: public Player {
protected:
    Move getNextMove() override;
public:
    PlayerType playerType() const override;
};

#endif
