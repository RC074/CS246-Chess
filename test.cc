#include <iostream>
#include "board.h"
#include "player.h"
#include "computer.h"
#include "textdisplay.h"
#include "human.h"
#include "computer.h"
#include <sstream>

using namespace std;

// Level1 p1;
// Level1 p2;
// computer[1-4]

PieceType charToPiece(char c) {
    int currChar = static_cast<int>(c);
    if (currChar >= 97) currChar -= 32;
    if (c == 'K') return PieceType::KING;
    else if (c == 'Q') return PieceType::QUEEN;
    else if (c == 'B') return PieceType::BISHOP;
    else if (c == 'N') return PieceType::KNIGHT;
    else if (c == 'R') return PieceType::ROOK;
    else if (c == 'P') return PieceType::PAWN;
    else return PieceType::NONE;
}

vector<int> parsePos(string pos) {
    stringstream iss {pos};
    char colChar; // column is taken in as a char, from a-h
    int row; // row is taken in as an int, from 1-8
    iss >> colChar >> row;
    row = 8 - row;
    int col = static_cast<int>(colChar) - 97; // ex. if colChar = 'a', col = 1, since a is 97 in ascii
    return {row, col};
}

int main(int argc, char const *argv[]) {
    bool useStandard = true;
    string cmd, p1, p2;
    // Xwindow zw;
    Board board {};
    Color turn = Color::WHITE;

    while(true) {
        cin >> cmd;

        if (cmd == "setup") {

            while (true) {
                cin >> cmd;
                if (cmd == "+") { // adding a piece
                    char piece;
                    string pos;
                    cin >> piece >> pos;
                    int pieceInt = static_cast<int>(piece); // converting piece to int to check if B or W
                    
                    vector<int> posVec = parsePos(pos);
                    int row = posVec[0];
                    int col = posVec[1];
                    if (row < 0 || row > 7 || col < 0 || col > 7) {
                        cout << "Invalid add piece position [" << static_cast<char>(row) << "][" << static_cast<char>(col) << "]" << endl;
                        continue;
                    }
                    
                    Color c;
                    if (pieceInt >= 97) c = Color::BLACK;
                    else c = Color::WHITE;
                    
                    PieceType pt = charToPiece(piece);
                    if (pt == PieceType::NONE) {
                        cout << "Invalid piece" << endl;
                        continue;
                    }

                    board.removePieceAt(row, col);
                    board.setPieceAt(pt, row, col, c);

                } // "+" adding piece
                else if (cmd == "-") {
                    string pos;
                    cin >> pos;
                    vector<int> posVec = parsePos(pos);
                    int row = posVec[0];
                    int col = posVec[1];
                    if (row < 0 || row > 7 || col < 0 || col > 7) {
                        cout << "Invalid remove piece position: [" << static_cast<char>(row) << "][" << static_cast<char>(col) << "]" << endl;
                        continue;
                    }
                }
                else if (cmd == "=") {
                    string color;
                    cin >> color;
                    if (color == "black") turn = Color::BLACK;
                    else if (color == "white") turn = Color::WHITE;
                    else cout << "Invalid color: " << color << endl;
                }
                else if (cmd == "done") {
                    useStandard = false;
                    break;
                }
                else cout << "Invalid command: " << cmd << endl; // invalid command, still in setup mode
            } // while we are in the "setup" command   

        } // if "setup"
        else if (cmd == "game") {
            cin >> p1 >> p2;
            if ((p1 == "human" || p1 == "computer1" || p1 == "computer2" || p1 == "computer3" || p1 == "computer4") &&
                (p2 == "human" || p2 == "computer1" || p2 == "computer2" || p2 == "computer3" || p2 == "computer4")) {

                shared_ptr<Player> player1, player2;

                if (p1 == "human") player1 = make_shared<Human>();
                else if (p1 == "computer1") player1 = make_shared<Level1>();
                else if (p1 == "computer2") player1 = make_shared<Level2>();
                else if (p1 == "computer3") player1 = make_shared<Level3>();
                else player1 = make_shared<Level4>();

                if (p2 == "human") player2 = make_shared<Human>();
                else if (p2 == "computer1") player2 = make_shared<Level1>();
                else if (p2 == "computer2") player2 = make_shared<Level2>();
                else if (p2 == "computer3") player2 = make_shared<Level3>();
                else player2 = make_shared<Level4>();

                board.init(*player1, *player2, useStandard);

                // game HERE, MOVES HERE

            } else {
                cout << "Invalid players type: " << p1 << ", " << p2 << endl;
                // break; we don't want to break here, we want to continue to the next command
            }

        } // if "game"
        
    } // while



//   Board board {};
//   board.init(p1, p2);
//   cout << board << endl;

//   Piece *p = board.getPieceAt(1, 4);
//   board.move(p, 2, 4);
//   cout << board << endl;
//   board.move(p, 3, 4);
//   cout << board << endl;
//   board.move(p, 4, 4);
//   cout << board << endl;
//   board.move(p, 5, 4);
//   cout << board << endl;
//   Piece *p2 = board.getPieceAt(6, 5);
//   board.move(p2, 5, 4);
//   cout << board << endl;
//   cout << p->getIsCaptured() << endl;
//   Piece *b2 = board.getPieceAt(7, 5);
//   board.move(b2, 2, 5); // doesn't do anything since bishop cant move directly up
//   cout << board << endl;
//   p = board.getPieceAt(6, 7);
//   board.move(p, 5, 7);
//   board.move(p, 4, 7);
//   board.move(p, 3, 7);
//   board.move(p, 2, 7);
//   Piece *r2 = board.getPieceAt(7, 7);
//   board.move(r2, 3, 7);
//   cout << board << endl;
}
