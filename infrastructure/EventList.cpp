#include "EventList.h"
#include <algorithm>

EventList::EventList() {
    this->currentEvent = 0;
}

void EventList::add(const Event &e) {
    this->events.push_back(e);
}

void EventList::remove(const std::string& title) {
    auto it = std::remove_if(events.begin(), events.end(),
                             [&title](const Event& e) { return e.getTitle() == title; });
    if (it != events.end()) {
        events.erase(it, events.end());
    }
}

Event EventList::getcurrentEvent() {
    if (this->currentEvent == this->events.size())
        this->currentEvent = 0;

    return this->events[this->currentEvent];
}

void EventList::open() {
    if (this->events.size() == 0)
        return;
    this->currentEvent = 0;
    Event current_event = this->getcurrentEvent();
    current_event.open();
}

void EventList::next() {
    if (this->events.size() == 0)
        return;
    this->currentEvent++;
    Event currentEvent = this->getcurrentEvent();
    currentEvent.open();
}

bool EventList::isempty() {
    return this->events.size() == 0;
}

EventList::~EventList() {

}
