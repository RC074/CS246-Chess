#ifndef __READABLE_H__
#define __READABLE_H__
#include <string>
#include <iostream>

using namespace std;

string toString(int row, int col);

istream &getPos(istream &in, int row, int col);

#endif
