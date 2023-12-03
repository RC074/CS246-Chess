#ifndef __HUMAN_H__
#define __HUMAN_H__
#include <iostream>
#include "player.h"

class Human: public Player {
public:
    bool move(istream &in) override;
};

#endif
