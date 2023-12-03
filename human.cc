#include <sstream>
#include "human.h"
#include "readable.h"

using namespace std;

Move Human::getNextMove(istream &in) {
    string s;
    vector<string> instruction;
    while (in>>s) {
        instruction.emplace_back(s);
    }
    if (instruction.size() != 2 && instruction.size() != 3) 
        throw invalid_argument {"incorrect input"};
    int r0, c0, r1, c1;
    istringstream p0 {instruction[0]};
    istringstream p1 {instruction[1]};
    getPos(p0, r0, c0);
    getPos(p1, r1, c1);
    Move move {r0, c0, r1, c1};
    if (instruction.size() == 3) {
        char c;
        istringstream iss {instruction[2]};
        iss >> c;
        move.promotion = getPieceType(c);
    }
    return move;
}
