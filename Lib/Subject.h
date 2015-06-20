#ifndef SUBJECT_H
#define SUBJECT_H

#include <set>
#include "Observer.h"

// class for subjects that need to update views
class Subject
{

public:
    void subscribe(Observer *);                 // mutator - add observer/view to the list
    void unsubscribe(Observer *);               // mutator - remove observer/view from list

protected:
    void notify();                              // notify all the observers

private:
    std::set<Observer *> observers_;            // list of observers/views for this subject
};

#endif
