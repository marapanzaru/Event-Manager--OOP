#pragma once
#include <vector>
#include "domain/Event.h"

class EventRepository
{
public:
    EventRepository(const std::string& file);
    void add(const Event& event);
    void remove(const std::string& title);
    void update(const Event& updatedEvent);
    const std::vector<Event>& get_all() const;
    int findIndex(const std::string& title, const std::string& date, const std::string& time) const;
    const Event getEventAt(int index) const;
    Event findByTitle( const std::string& title) const;
    size_t size() const;




private:
    std::vector<Event> events;
    std::string filename;

    void loadFromFile(const std::string& filename);
    void saveToFile() const;
};
