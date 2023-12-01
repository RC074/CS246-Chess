#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "board.h"
#include "piece.h"

class Board;
class Player
{
    Board *b;
protected:
    Board *getBoard();
    virtual Move getNextMove() = 0;
public:
    void move();
    void setColor(Color c);
    Color getColor();
};

#endif
