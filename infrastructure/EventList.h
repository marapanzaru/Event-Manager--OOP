#pragma once
#include <vector>
#include "domain/event.h"

class EventList {

protected:
    std::vector<Event> events;
    int currentEvent;
public:
    EventList();
    void add(const Event& e);
    void open();
    void next();
    bool isempty();
    void remove(const std::string& title);
    Event getcurrentEvent();
    const std::vector<Event>& getAll() const {
        return events;
    }
    virtual ~EventList();

};
