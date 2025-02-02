#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "board.h"
#include "piece.h"
using namespace std;

class Board;

enum PlayerType {HUMAN, COMPUTER};

class Player
{
    Board *b;
    Color color;
protected:
    Board *getBoard() const;
    virtual Move getNextMove(istream &in) const = 0;
public:
    void setBoard(Board *b);
    void resign();
    bool move(istream &instruction, bool useStandard); // some player needs input
    void setColor(Color c);
    Color getColor() const;
    virtual PlayerType playerType() const = 0;
};

#endif
