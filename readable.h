#ifndef __READABLE_H__
#define __READABLE_H__
#include <string>
#include <iostream>

using namespace std;

// (0,0) => a8; (7,7) => h1
string toString(int row, int col);

// a8 => (0,0), the input format must be correct
istream &getPos(istream &in, int row, int col);

#endif
