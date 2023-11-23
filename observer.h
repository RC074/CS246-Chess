#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include "piece.h"

enum SubscriptionType {All, CaptureOnly};

class Observer {
public:
    virtual void notify(Piece * p) = 0;
    virtual SubscriptionType subType() = 0;
};

#endif
