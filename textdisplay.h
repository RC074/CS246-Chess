#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include "observer.h"
#include "board.h"

class TextDisplay: public Observer {
    std::vector<std::vector<char>> theDisplay;
    const int gridSize;
    void init(Board &b);
    char pieceToChar(Piece *p);
public:
    TextDisplay(int n);
    void notify(Move m) override;
    SubscriptionType subType() override;
    ~TextDisplay();
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
