#include "Subject.h"
#include "Observer.h"

// add new observer to list
void Subject::subscribe(Observer *newObserver)
{
    observers_.insert(newObserver);
}

// remove observer from list
void Subject::unsubscribe(Observer *observerToRemove)
{
    observers_.erase(observerToRemove);
}

// notify all observers of update
void Subject::notify()
{
    std::set<Observer *>::iterator it;
    for(it = observers_.begin(); it != observers_.end(); it++)
    {
        (*it)->update();
    }
}
