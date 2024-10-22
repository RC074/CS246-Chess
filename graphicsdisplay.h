#ifndef _GRAPHICSDISPLAY_H_
#define _GRAPHICSDISPLAY_H_
#include "observer.h"
#include "window.h"
#include "piece.h"

class GraphicsDisplay: public Observer {
    const int gridSize = 8;
    int cellWH = 50;
    const int windowWH = 400;
    Xwindow &window;
  public:
    GraphicsDisplay(int n, Xwindow &w);
    char pieceToChar(Piece *p);
    void notify(Move m) override; 
    SubscriptionType subType() override;
    ~GraphicsDisplay();;
};

#endif
