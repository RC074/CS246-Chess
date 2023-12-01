#ifndef __MAIN_H__
#define __MAIN_H__
#include <iostream>
#include "piece.h"
#include "board.h"
#include "computer.h"

using namespace std;

Computer p1 {};
Computer p2 {};

Board board {&p1, &p2};

int main(int argc, char const *argv[]) {
  board.getPieceAt(0,3)->setPosition(3, 3);
  board.move(board.getPieceAt(3,3), 5, 5);
  if (board.getPieceAt(5,5)->pieceType() == PieceType::QUEEN) {
    cout << 22222 << endl;
  }
}

#endif
