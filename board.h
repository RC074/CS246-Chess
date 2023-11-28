#ifndef __BOARD_H__
#define __BOARD_H__
#include "observer.h"
#include "player.h"
#include "piece.h"
#include <vector>
using namespace std;

class Board: public Observer{
    vector<vector<Piece*>> theBoard;
    bool won;
    void clearBoard();
    const int boardSize = 8;
    vector<vector<int>> stack;
public:
    void init();
    bool move(vector<int> p1, vector<int> p2);
    
    Piece* getPieceAt(vector<int> p);
    vector<vector<Piece*>> getBoard();
    Color getWinner();
    void undo();
    vector<int> getPreviousMove();
    Player* getPlayerBlack();
    Player* getPlayerWhite();
    // test
};

#endif
