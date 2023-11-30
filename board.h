#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include "player.h"
#include "piece.h"

using namespace std;

const int BOARD_SIZE = 8;

class Board{
    Player *p1, *p2;
    vector<vector<Piece *>> theBoard;
    void clearBoard();
    bool won;
    vector<Move> history;
public:
    Board(Player *p1, Player *p2);
    void init(bool p1White);
    bool move(Piece *pieceToMove, int row, int col);
    Piece* getPieceAt(int row, int col);
    vector<vector<Piece*>> getBoard();
    Color getWinner();
    void undo();
    Move getPreviousMove();
    Player *getPlayerBlack();
    Player *getPlayerWhite();
};

#endif
