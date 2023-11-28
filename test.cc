#include <iostream>
#include "piece.h"
#include "king.h"

using namespace std;

int main(int argc, char const *argv[]) {
  King k = King{1, 2, Color::WHITE};
  cout << k.getCol();
}
