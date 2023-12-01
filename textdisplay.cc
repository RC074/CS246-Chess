#include "textdisplay.h"

TextDisplay::TextDisplay(int n): theDisplay(), gridSize{8} {
    init();
}

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

    return static_cast<char>(asciiValue);
}

void TextDisplay::init(Board &b) {

}

void TextDisplay::notify(Move m) {
    int oldr = m.r0;
    int oldc = m.c0;
    int newr = m.r1;
    int newc = m.c1;

    if (oldr % 2 == 0 or oldc % 2 == 0) {
        theDisplay[oldr][oldc] = ' ';
    } else {
        theDisplay[oldr][oldc] = '_';
    }



}

SubscriptionType TextDisplay::subType() {

}

TextDisplay::~TextDisplay() {

}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {

}
