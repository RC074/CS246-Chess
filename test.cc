#include <iostream>
#include "board.h"
#include "player.h"
#include "computer.h"
#include "textdisplay.h"

using namespace std;

Level1 p1;
Level1 p2;


int main(int argc, char const *argv[]) {
  Board board {};
  board.init(p1, p2);
  cout << board << endl;

  Piece *p = board.getPieceAt(1, 4);
  board.move(p, 2, 4);
  cout << board << endl;
  board.move(p, 3, 4);
  cout << board << endl;
  board.move(p, 4, 4);
  cout << board << endl;
  board.move(p, 5, 4);
  cout << board << endl;
  Piece *p2 = board.getPieceAt(6, 5);
  board.move(p2, 5, 4);
  cout << board << endl;
  cout << p->getIsCaptured() << endl;
  Piece *b2 = board.getPieceAt(7, 5);
  board.move(b2, 2, 5); // doesn't do anything since bishop cant move directly up
  cout << board << endl;
  p = board.getPieceAt(6, 7);
  board.move(p, 5, 7);
  board.move(p, 4, 7);
  board.move(p, 3, 7);
  board.move(p, 2, 7);
  Piece *r2 = board.getPieceAt(7, 7);
  board.move(r2, 3, 7);
  cout << board << endl;
}
