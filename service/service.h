#pragma once
#include "repository/repository.h"
#include "domain/event.h"
#include "infrastructure//FileEventList.h"
#include "domain/EventsValidator.h"
#include <vector>
#include <string>
#include "undo_redo.h"

#include <memory>


class Service
{
public:
    Service(const EventRepository& r, FileEventlist* p, EventValidator v) : repo{ r }, eventlist{ p }, validator{ v } {}

    EventRepository getRepo() const { return repo; }
    FileEventlist* getEventlist() const { return eventlist; }

    void addEvent(const std::string& title, const std::string& description,
                  const std::string& date, const std::string& time, int peopleGoing, const std::string& link);

    void removeEvent(const std::string& title);

    void updateEvent(const std::string& title, const std::string& newDescription,
                     const std::string& newDate, const std::string& newTime, int newPeopleGoing, const std::string& newLink);

    const std::vector<Event>& getAllEvents() const;

    size_t getEventCount() const;

    // User operations
    std::vector<Event> getEventsByMonth(const std::string& month) const;
    void addToUserList(const Event& e);
    void removeFromUserList(const std::string& title);
    const std::vector<Event>& getUserEvents() const;
    void increaseParticipants(const std::string& title);
    void decreaseParticipants(const std::string& title);
    void saveToFile();
    void openFile();

    void undo();
    void redo();

private:
    EventRepository repo;
    FileEventlist* eventlist;
    EventValidator validator;
    bool eventExists(const std::string& title);
    std::vector<std::unique_ptr<UndoAction>> undoStack;
    std::vector<std::unique_ptr<UndoAction>> redoStack;
};