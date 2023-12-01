#include <iostream>
#include "board.h"
#include "player.h"
#include "computer.h"

using namespace std;

Level1 p1;
Level1 p2;

Board board {};

int main(int argc, char const *argv[]) {
  cout << "HIHHIHI" << endl;
  board.init(p1, p2);
  Piece *p = board.getPieceAt(0,3);
  if (p) {
    cout << 3333 << endl;
  }
  cout << "HIHHIHI" << endl;
  if (p->pieceType() == PieceType::QUEEN) {
    cout << 22222 << endl;
  }
  cout << "HIHHIHI" << endl;
  p->setPosition(3, 3);
  cout << "HIHHIHI" << endl;
  board.move(p, 5, 5);
  cout << "HIHHIHI" << endl;
  if (board.getPieceAt(5,5)) {
    cout << 666 << endl;
  }
  if (board.getPieceAt(5,5)->pieceType() == PieceType::QUEEN) {
    cout << 22222 << endl;
  }
}
