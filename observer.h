#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <iostream>

enum SubscriptionType {All, KingObserver};
struct Move;

class Observer {
public:
    virtual void notify(Move m) = 0;
    virtual SubscriptionType subType() = 0;
};

#endif
