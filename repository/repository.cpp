#include "repository.h"
#include <algorithm>
#include <fstream>

#include "RepositoryExceptions.h"

EventRepository::EventRepository(const std::string &file): filename(file) {
    loadFromFile(file);
}


void EventRepository::add(const Event& event)
{
    events.push_back(event);
    saveToFile();
}


void EventRepository::remove(const std::string& title)
{
    auto it = std::find_if(events.begin(), events.end(), 
        [&title](const Event& e) { return e.getTitle() == title; });
    
    if (it != events.end()) {
        events.erase(it);
    }
    saveToFile();
}


void EventRepository::update(const Event& updatedEvent)
{
    auto it = std::find_if(events.begin(), events.end(), 
        [&updatedEvent](const Event& e) { return e.getTitle() == updatedEvent.getTitle(); });
    
    if (it != events.end()) {
        *it = updatedEvent;
    }
    saveToFile();
}


const std::vector<Event>& EventRepository::get_all() const
{
    return events;
}


size_t EventRepository::size() const
{
    return events.size();
}

int EventRepository::findIndex(const std::string& title, const std::string& date, const std::string& time) const {
    auto it = std::find_if(events.begin(), events.end(), 
        [&](const Event& e) { 
            return e.getTitle() == title && e.getDate() == date && e.getTime() == time; 
        });
    
    if (it != events.end()) {
        return std::distance(events.begin(), it);
    }
    
    return -1;
}

const Event EventRepository::getEventAt(int index) const {
    if (index >= 0 && index < static_cast<int>(events.size())) {
        return events[index];
    }
    throw std::out_of_range("Index out of range");
}

void EventRepository::loadFromFile(const std::string& filename) {
    std::cout << "Trying to write to: " << filename << std::endl;
    events.clear();
    std::ifstream file(filename);
    if (!file.is_open()) {
        return;
    }
    
    Event event;
    while (file >> event) {
        events.push_back(event);
    }
    
    file.close();
}

void EventRepository::saveToFile() const {

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr  << filename << std::endl;
        throw std::runtime_error("Could not open file for writing");
    }
    
    for (const auto& event : events) {
        file << event << std::endl;
    }

    file.close();
}
Event EventRepository::findByTitle(const std::string &title) const {
    for (auto e: this->events)
    {
        if (e.getTitle() == title)
            return e;
    }

    throw InexistenEventException{};
}
