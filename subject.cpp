#include "subject.h"

//Subject::~Subject () {
//}

bool Subject::RegisterObserver(Observer * observer) {
    if (std::find(s_Observers.begin(), s_Observers.end(), observer) == s_Observers.end()) {
        s_Observers.push_back(observer);
        return true;
    } else
        return false;
}

bool Subject::UnregisterObserver(Observer * observer) {
    std::list<Observer *>::iterator it;
    it = std::find(s_Observers.begin(), s_Observers.end(), observer);
    if (it != s_Observers.end()) {
        s_Observers.erase(it);
        return true;
    } else
        return false;
}

void Subject::Notify (double u, double y) const {
    std::list<Observer *>::const_iterator it = s_Observers.begin();
    for (; it != s_Observers.end(); ++it) {
            (*it)->Update(u, y);
    }
}

//void Subject::Notify (double y) const {
//    std::list<Observer *>::const_iterator it = s_Observers.begin();
//    for (; it != s_Observers.end(); ++it) {
//            (*it)->Update(y);
//    }
//}
