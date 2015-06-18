#include "Subject.h"
#include "Observer.h"

void Subject::subscribe(Observer *newObserver)
{
    observers_.insert(newObserver);
}

void Subject::unsubscribe(Observer *observerToRemove)
{
    observers_.erase(observerToRemove);
}

void Subject::notify()
{
    std::set<Observer *>::iterator it;
    for(it = observers_.begin(); it != observers_.end(); it++)
    {
        (*it)->update();
    }
}
