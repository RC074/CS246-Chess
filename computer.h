#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "player.h"

class Computer: public Player {
protected:
    vector<vector<bool>> getThreatBoard() const;
    Move getNextMove(istream &in) const override;
    virtual int rankMove(const Move &m) const = 0;
};

class Level1: public Computer {
protected:
    int rankMove(const Move &m) const override;
};

class Level2: public Computer {
protected:
    int rankMove(const Move &m) const override;
};

class Level3: public Computer {
protected:
    int rankMove(const Move &m) const override;
};

#endif
