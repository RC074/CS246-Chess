#include "piece.h"

Piece::Piece(int row, int col, Color color):row{row}, col{col}, color{color}{}

Color Piece::getColor() const {
  return color;
}

int Piece::getRow() const {
  return row;
}

int Piece::getCol() const {
  return col;
}

void Piece::setPosition(int r, int c) {
  this->row = r;
  this->col = c;
}

void Piece::setIsCaptured(bool t) {
  this->isCaptured = t;
}

void Piece::notifyAllObservers() {
  // for (auto ob : observers) {
  //   ob.notify(this);
  // }
}

void Piece::attach(Observer *ob) {
  observers.emplace_back(ob);
}
