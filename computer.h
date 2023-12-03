#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "player.h"

class Computer: public Player {
protected:
    vector<vector<bool>> getThreatBoard() const;
    vector<vector<bool>> getCaptureBoard() const;
};

class Level1: public Computer {
protected:
    Move getNextMove(istream &in) override;
};

class Level2: public Computer {
protected:
    Move getNextMove(istream &in) override;
};

class Level3: public Computer {
protected:
    Move getNextMove(istream &in) override;
};

#endif
