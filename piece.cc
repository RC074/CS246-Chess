#include "piece.h"

Piece::Piece(int row, int col, Color color):row{row}, col{col}, color{color}{}

bool Piece::getMoved() const {
  return moved;
}

void Piece::setMoved() {
  moved = true;
}

Color Piece::getColor() const {
  return color;
}

bool Piece::getIsCaptured() const {
  return isCaptured;
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

void Piece::notifyAllObservers(Move m) {
  for (auto ob : observers) {
    ob->notify(m);
  }
}

void Piece::attach(Observer *ob) {
  observers.emplace_back(ob);
}
