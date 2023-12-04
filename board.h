#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include "player.h"
#include "textdisplay.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "pawn.h"
#include "graphicsdisplay.h"

using namespace std;


const int BOARD_SIZE = 8;
class Player;
class TextDisplay;
class GraphicsDisplay;
class King;
class Board{
    Player *blackPlayer, *whitePlayer;
    King *blackKing = nullptr;
    King *whiteKing = nullptr;
    vector<vector<Piece *>> theBoard;
    void clearBoard();
    Color winner;
    vector<Move> history;
    TextDisplay *td;
    GraphicsDisplay *gd;
    Xwindow &window;
    void updateWin(); // called at each move
    vector<vector<bool>> whiteDangerZone;
    vector<vector<bool>> blackDangerZone;
public:
    Board(Xwindow &window);
    ~Board();
    void init(Player &blackPlayer, Player &WhitePlayer, 
              bool useStandard = true, bool graphicOn = true);
    void removePieceAt(int row, int col);
    void setPieceAt(PieceType pt, int row, int col, Color c);
    bool validateBoard(); // use at the end of setup
    bool move(int r0, int c0, int r1, int c1);
    bool move(Piece *pieceToMove, int row, int col);
    Piece* getPieceAt(int row, int col);
    vector<vector<Piece*>> getBoard();
    Color getWinner();
    void undo();
    void updateDangerZone(Color color);
    bool inCheck(Color color);
    bool checkMate(Color color);
    Move getPreviousMove();
    Player *getPlayerBlack();
    Player *getPlayerWhite();
    friend std::ostream &operator<<(std::ostream &out, const Board &g);
};

#endif
