#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include "observer.h"

class TextDisplay: public Observer {
public:
    void notify(Piece * p) override;
    SubscriptionType subType() override;
};

#endif
