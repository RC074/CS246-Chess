#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "board.h"

class Player
{
    Board *b;
protected:
    virtual void getNextMove() = 0;
public:
    void move();
    void setColor(Color c);
};

#endif
