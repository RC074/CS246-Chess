#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include "player.h"
#include "piece.h"
#include "textdisplay.h"

using namespace std;

const int BOARD_SIZE = 8;
class Player;
class Board{
    Player *blackPlayer, *whitePlayer;
    vector<vector<Piece *>> theBoard;
    void clearBoard();
    bool won;
    vector<Move> history;
    TextDisplay *td;
public:
    Board();
    ~Board();
    void init(Player &blackPlayer, Player &WhitePlayer, 
              bool useStandard = false);
    void set();
    bool move(Piece *pieceToMove, int row, int col);
    Piece* getPieceAt(int row, int col);
    vector<vector<Piece*>> getBoard();
    Color getWinner();
    void undo();
    Move getPreviousMove();
    Player *getPlayerBlack();
    Player *getPlayerWhite();
    friend std::ostream &operator<<(std::ostream &out, const Board &g);
};

#endif
