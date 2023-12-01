#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "board.h"
#include "piece.h"

class Board;
class Player
{
    Board *b;
    Color color;
protected:
    Board *getBoard() const;
    virtual Move getNextMove() = 0;
public:
    void move();
    void setColor(Color c);
    Color getColor();
};

#endif
