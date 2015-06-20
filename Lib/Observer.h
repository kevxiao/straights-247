#ifndef OBSERVER_H
#define OBSERVER_H

// observer class for view to update with model
class Observer
{
public:
    virtual void update() = 0;          // to be implemented by the view
};

#endif
