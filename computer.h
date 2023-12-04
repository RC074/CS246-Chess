#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "player.h"
#include "readable.h"

using BoolBoard = vector<vector<bool>>;

class Computer: public Player {
protected:
    BoolBoard getThreatBoard() const;
    Move getNextMove(istream &in) const override;
    virtual int rankMove(const Move &m, BoolBoard &threat) const = 0;
public:
    PlayerType playerType() const override;
};

class Level1: public Computer {
protected:
    int rankMove(const Move &m, BoolBoard &threat) const override;
};

class Level2: public Computer {
protected:
    int rankMove(const Move &m, BoolBoard &threat) const override;
};

class Level3: public Computer {
protected:
    int rankMove(const Move &m, BoolBoard &threat) const override;
};

class Level4: public Computer {
protected:
    int rankMove(const Move &m, BoolBoard &threat) const override;
};

#endif
