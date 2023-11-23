#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player
{
protected:
    virtual void getNextMove() = 0;
public:
    void move();
};

#endif
