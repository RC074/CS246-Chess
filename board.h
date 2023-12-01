#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include "player.h"
#include "piece.h"
#include "king.h"

using namespace std;

const int BOARD_SIZE = 8;
class Player;
class Board{
    Player *blackPlayer, *whitePlayer;
    King *blackKing = nullptr;
    King *whiteKing = nullptr;
    vector<vector<Piece *>> theBoard;
    void clearBoard();
    bool won;
    vector<Move> history;
public:
    Board();
    void init(Player &blackPlayer, Player &WhitePlayer, 
              bool useStandard = false);
    void removePieceAt(int row, int col);
    void setPieceAt(PieceType pt, int row, int col, Color c);
    bool isValidBoard();
    void startGame();
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
