#include <iostream>
#include <memory>
#include <sstream>
#include "board.h"
#include "player.h"
#include "computer.h"
#include "textdisplay.h"
#include "human.h"
#include "readable.h"
#include "window.h"

using namespace std;

// FLAGS
Color START_COLOR = Color::WHITE;

// Level1 p1;
// Level1 p2;
// computer[1-4]

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
    Xwindow window;
    Board board {window};
    Color turn = Color::WHITE;
    int blackScoreRaw = 0; // real score is this score divided by 10.
    int whiteScoreRaw = 0;

    while(cin >> cmd) {

        if (cmd == "setup") {
            cout << "entering setup mode" << endl;

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
                        cout << "Invalid add piece position: " << pos << endl;
                        continue;
                    }
                    
                    Color c;
                    if (pieceInt >= 97) c = Color::BLACK;
                    else c = Color::WHITE;
                    
                    PieceType pt = getPieceType(piece);
                    if (pt == PieceType::NONE) {
                        cout << "Invalid piece" << endl;
                        continue;
                    }

                    board.setPieceAt(pt, row, col, c);
                    cout << board << endl;

                } // "+" adding piece
                else if (cmd == "-") {
                    string pos;
                    cin >> pos;
                    vector<int> posVec = parsePos(pos);
                    int row = posVec[0];
                    int col = posVec[1];
                    if (row < 0 || row > 7 || col < 0 || col > 7) {
                        cout << "Invalid remove piece position: " << pos << endl;
                        continue;
                    }
                    board.removePieceAt(row, col);
                    cout << board << endl;
                }
                else if (cmd == "=") {
                    string color;
                    cin >> color;
                    if (color == "black") turn = Color::BLACK;
                    else if (color == "white") turn = Color::WHITE;
                    else {
                        cout << "Invalid color: " << color << endl;
                        continue;
                    }
                }
                else if (cmd == "done") {
                    board.updateDangerZone(Color::BLACK);
                    board.updateDangerZone(Color::WHITE);
                    if (!board.validateBoard()) {
                        cout << "incorrect setup" << endl;
                        continue;
                    }
                    useStandard = false;
                    cout << "Leaving setup mode" << endl;
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

                board.init(*player2, *player1, useStandard);
                cout << board << endl; // print the initialized board

                // game HERE, MOVES HERE
                while (cin >> cmd) {
                    try {
                        Player &p = (turn == Color::WHITE) ?  *player1 : *player2;
                        

                        if (cmd == "move") {
                            if (!p.move(cin, useStandard)) {
                                cout << "invalid move" << endl;
                                continue;
                            }
                            
                            cout << board << endl;
                            if (board.staleMate(Color::BLACK)) {
                                cout << "Draw" << endl;
                                whiteScoreRaw += 5;
                                blackScoreRaw += 5;
                                break;
                            }
                            if (board.staleMate(Color::WHITE)) {
                                cout << "Draw" << endl;
                                whiteScoreRaw += 5;
                                blackScoreRaw += 5;
                                break;
                            }
                            if (board.checkMate(Color::BLACK)) {
                                cout << "White Player Wins" << endl;
                                whiteScoreRaw += 10;
                                break;
                            }
                            if (board.checkMate(Color::WHITE)) {
                                cout << "Black Player Wins" << endl;
                                blackScoreRaw += 10;
                                break;
                            }

                        }
                        else if (cmd == "undo") {
                            board.undo();
                            cout << "Undo successful, new board:" << endl;
                            cout << board << endl;
                        }
                        else if (cmd == "resign") {
                            if (turn == Color::WHITE) cout << "Black wins!" << endl;
                            else cout << "White wins!" << endl;
                            break;
                        }
                        else {
                            cout << "Invalid command: " << cmd << endl;
                            continue;
                        }
                        turn = (turn == Color::BLACK) ? Color::WHITE : Color::BLACK;
                    } catch(const std::exception& e) {
                        std::cerr << e.what() << '\n';
                    }
                    
                 }

            } else {
                cout << "Invalid players type: " << p1 << ", " << p2 << endl;
                // break; we don't want to break here, we want to continue to the next command
            }

        } // if "game"
        else {
            cout << "Invalid command: " << cmd << endl;
        }
        
    } // while

    // after ctrl-D
    cout << "Final Score:" << endl;
    ostringstream whiteScore;
    ostringstream blackScore;
    whiteScore << whiteScoreRaw / 10;
    blackScore << blackScoreRaw / 10;
    if (whiteScoreRaw % 10 > 0) whiteScore << "." << whiteScoreRaw % 10;
    if (blackScoreRaw % 10 > 0) blackScore << "." << blackScoreRaw % 10;
    cout << "White: " << whiteScore.str() << endl;
    cout << "Black: " << blackScore.str() << endl;
}
