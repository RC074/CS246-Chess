#include "textdisplay.h"

TextDisplay::TextDisplay(int n): theDisplay{vector<vector<char>>(8, (vector<char>(8, ' ')))}, gridSize{8} {}

char TextDisplay::pieceToChar(Piece *p) {
    int asciiValue = 0;
    Color c = p->getColor();
    PieceType pt = p->pieceType();
    // for ref: enum class PieceType { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, NONE };
    // note A is 65, a is 97, so we need to add 32 to get the lower case (Black)
    if (pt == PieceType::KING) {
        asciiValue = 75;
    } else if (pt == PieceType::QUEEN) {
        asciiValue = 81;
    } else if (pt == PieceType::BISHOP) {
        asciiValue = 66;
    } else if (pt == PieceType::KNIGHT) {
        asciiValue = 78;
    } else if (pt == PieceType::ROOK) {
        asciiValue = 82;
    } else { // pt == PieceType::PAWN
        asciiValue = 80;
    } 
    if (c == Color::BLACK) {
        asciiValue += 32;
    }

    return static_cast<char>(asciiValue);
}

// void TextDisplay::init(Board &b) {
//     for (int i = 0; i < gridSize; i++) {
//         for (int j = 0; j < gridSize; j++) {
//             Piece *p = b.getPieceAt(i, j);
//             if (p) {
//                 theDisplay[i][j] = pieceToChar(p);
//             } else {
//                 if ((i + j) % 2 == 0) {
//                     theDisplay[i][j] = ' ';
//                 } else {
//                     theDisplay[i][j] = '_';
//                 }
//             }
//         }
//     }
// }

void TextDisplay::notify(Move m) {
    int oldr = m.r0;
    int oldc = m.c0;
    int newr = m.r1;
    int newc = m.c1;

    if ((oldr % 2 == 1 && oldc % 2 == 1) || (oldr % 2 == 0 && oldc % 2 == 0)) {
        theDisplay[oldr][oldc] = ' '; // white square
    } else {
        theDisplay[oldr][oldc] = '_'; // black square
    }

    if (m.p) {
        char pieceChar = pieceToChar(const_cast<Piece*>(m.p));
        theDisplay[newr][newc] = pieceChar;
    }
}

SubscriptionType TextDisplay::subType() {
    return SubscriptionType::All;
}

TextDisplay::~TextDisplay() {}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    for (int i = 0; i < td.gridSize; ++i) {
        for (int j = 0; j < td.gridSize; ++j) {
            if (j == td.theDisplay[0].size() - 1) {
                out << td.theDisplay[i][j] << std::endl;
            }
            else out << td.theDisplay[i][j];
        }
    }
    return out;
}
