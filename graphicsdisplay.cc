#include "graphicsdisplay.h"

GraphicsDisplay::GraphicsDisplay(int n, Xwindow &w): gridSize{n}, window{w} {
    for (int i = 1; i <= gridSize; i++) {
        std::string font = "-b&h-lucidatypewriter-bold-r-normal-sans-20-140-100-100-m-120-iso8859-10";
        window.drawString(30, (i-1)*50 + 60, std::to_string(gridSize-i+1), Xwindow::Black, font);
    }
    for (int i = 0; i < gridSize; i++) {
        std::string font = "-b&h-lucidatypewriter-bold-r-normal-sans-20-140-100-100-m-120-iso8859-10";
        window.drawString((i)*50 + 70, 50*gridSize + 50, std::string(1, (char)(97+i)), Xwindow::Black, font);
    }
}

char GraphicsDisplay::pieceToChar(Piece *p) {
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

// notifies to update the graphics
void GraphicsDisplay::notify(Move m) {
    int oldr = m.r0;
    int oldc = m.c0;
    int newr = m.r1;
    int newc = m.c1;
    // int cellSize = windowWH / gridSize; // 50
    int x = oldc * cellWH;
    int y = oldr * cellWH;

    if ((oldr % 2 == 1 && oldc % 2 == 1) || (oldr % 2 == 0 && oldc % 2 == 0)) {
        window.fillRectangle(x+50, y+30, cellWH, cellWH, Xwindow::White);
    } else {
        window.fillRectangle(x+50, y+30, cellWH, cellWH, Xwindow::Black);
    }

    x = newc * cellWH;
    y = newr * cellWH;

    if (m.p) {
        char pieceChar = pieceToChar(const_cast<Piece*>(m.p));
        std::string pieceStr(1, pieceChar);
        std::string font = "-b&h-lucidatypewriter-bold-r-normal-sans-20-140-100-100-m-120-iso8859-10";
        window.drawString(x+20+50, y+60, pieceStr, m.p->getColor() == Color::BLACK ? Xwindow::Red : Xwindow::Blue, font);
        // window.drawString(x, y, pieceStr);
    }
}

SubscriptionType GraphicsDisplay::subType() {
    return SubscriptionType::All;
}

GraphicsDisplay::~GraphicsDisplay() {}


