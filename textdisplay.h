#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include "observer.h"
#include "board.h"

class Board;
class TextDisplay: public Observer {
    std::vector<std::vector<char>> theDisplay;
    const int gridSize;
    
    char pieceToChar(Piece *p);
public:
    TextDisplay(int n);
    void notify(Move m) override;
    void init(Board &b);
    SubscriptionType subType() override;
    ~TextDisplay();
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
