#include "service.h"
#include "RepositoryExceptions.h"
#include <algorithm>


/*
 *  Adds a new event to the repository if it does not already exist.
 * Parameters:
 *   - title: The title of the event.
 *   - description: The description of the event.
 *   - date: The date of the event.
 *   - time: The time of the event.
 *   - peopleGoing: The number of people attending.
 *   - link: The event link.
 */
void Service::addEvent(const std::string& title, const std::string& description, const std::string& date, const std::string& time, int peopleGoing, const std::string& link)
{
    if (eventExists(title)) {
        throw DuplicateEventException();
    }
    Event e{title, description, date, time, peopleGoing, link};
    this->validator.validate(e);
    this->repo.add(e);

    undoStack.push_back(std::make_unique<AddUndoAction>(repo, e));
    redoStack.clear();
}

/*
 * Removes an event from the repository based on its title.
 * Parameters:
 *   - title: The title of the event to be removed.
 */
void Service::removeEvent(const std::string& title)
{
    if (!eventExists(title)) {
        throw InexistenEventException();
    }
    const auto& events = repo.get_all();
    auto it = std::find_if(events.begin(), events.end(), [&title](const Event& e) { return e.getTitle() == title; });

    Event e = *it;
    this->repo.remove(title);
    undoStack.push_back(std::make_unique<RemoveUndoAction>(repo, e));
    redoStack.clear();
}

/*
 * Updates an existing event's details.
 * Parameters:
 *   - title: The title of the event to update.
 *   - newDescription: The new description of the event.
 *   - date: The new date of the event.
 *   - time: The new time of the event.
 *   - newPeopleGoing: The updated number of attendees.
 *   - newLink: The new event link.
 */
void Service::updateEvent(const std::string& title, const std::string& newDescription, const std::string& newDate, const std::string& newTime, int newPeopleGoing, const std::string& newLink) {
    if (!eventExists(title)) {
        throw InexistenEventException();
    }
    const auto& events = repo.get_all();
    auto it = std::find_if(events.begin(), events.end(), [&title](const Event& e) { return e.getTitle() == title; });

    Event oldEvent = *it;
    Event newEvent{title, newDescription, newDate, newTime, newPeopleGoing, newLink};
    this->validator.validate(newEvent);
    this->repo.update(newEvent);

    undoStack.push_back(std::make_unique<UpdateUndoAction>(repo, oldEvent, newEvent));
    redoStack.clear();
}
/*
 *  Retrieves all events from the repository.
 * Returns:
 *   - A constant reference to a vector containing all events.
 */
const std::vector<Event>& Service::getAllEvents() const
{
    return repo.get_all();
}

/*
 * Gets the total number of events stored in the repository.
 * Returns:
 *   - The number of events as a size_t.
 */
size_t Service::getEventCount() const
{
    return repo.size();
}

/*
 * Checks if an event with the given title exists in the repository.
 * Parameters:
 *   - title: The title of the event to search for.
 * Returns:
 *   - True if the event exists, false otherwise.
 */
bool Service::eventExists(const std::string& title)
{
    const std::vector<Event>& events = repo.get_all();
    return std::any_of(events.begin(), events.end(),
        [&title](const Event& e) { return e.getTitle() == title; });
}

std::vector<Event> Service::getEventsByMonth(const std::string& month) const {
    std::vector<Event> filtered;
    const std::vector<Event>& allEvents = repo.get_all();

    std::copy_if(allEvents.begin(), allEvents.end(), std::back_inserter(filtered),
        [&month](const Event& e) {
            return month.empty() || e.getDate().substr(5, 2) == month;
        });

    std::sort(filtered.begin(), filtered.end(),
        [](const Event& a, const Event& b) {
            if (a.getDate() != b.getDate()) {
                return a.getDate() < b.getDate();
            }
            return a.getTime() < b.getTime();
        });

    return filtered;
}

void Service::addToUserList(const Event& e) {
    const auto& allEvents = repo.get_all();
    auto it = std::find_if(allEvents.begin(), allEvents.end(),
                           [&e](const Event& event) { return event.getTitle() == e.getTitle(); });
    if (it == allEvents.end()) {
        throw InexistenEventException();
    }
    const auto& userEvents = eventlist->getAll();
    auto userIt = std::find_if(userEvents.begin(), userEvents.end(),
                               [&e](const Event& event) { return event.getTitle() == e.getTitle(); });
    if (userIt != userEvents.end()) {
        throw std::runtime_error("Event is already in the user's list!");
    }
    increaseParticipants(e.getTitle());
    if (this->eventlist)
        this->eventlist->add(*it);
}

void Service::removeFromUserList(const std::string& title) {
    if (!this->eventlist)
        return;
    const auto& userEvents = eventlist->getAll();
    auto it = std::find_if(userEvents.begin(), userEvents.end(),
                           [&title](const Event& e) { return e.getTitle() == title; });
    if (it == userEvents.end()) {
        throw std::runtime_error("Event not found in the user's list!");
    }
    decreaseParticipants(title);
    this->eventlist->remove(title);
}
const std::vector<Event>& Service::getUserEvents() const {
    return eventlist->getAll();
}

void Service::increaseParticipants(const std::string& title) {
    const std::vector<Event>& allEvents = repo.get_all();

    auto it = std::find_if(allEvents.begin(), allEvents.end(),
                         [&title](const Event& e) { return e.getTitle() == title; });

    if (it != allEvents.end()) {
        Event updatedEvent = *it;
        updatedEvent.setPeopleGoing(it->getPeople() + 1);
        repo.update(updatedEvent);
    }
}

void Service::decreaseParticipants(const std::string& title) {
    const std::vector<Event>& allEvents = repo.get_all();

    auto it = std::find_if(allEvents.begin(), allEvents.end(),
                         [&title](const Event& e) { return e.getTitle() == title; });

    if (it != allEvents.end()) {
        Event updatedEvent = *it;
        int updatedCount = it->getPeople() > 0 ? it->getPeople() - 1 : 0;
        updatedEvent.setPeopleGoing(updatedCount);
        repo.update(updatedEvent);
    }
}

void Service::saveToFile() {
    if (this->eventlist) {
        this->eventlist->writeToFile();
    }
}

void Service::openFile() {
    if (this->eventlist) {
        this->eventlist->displayEventlist();
    }
}
void Service::undo() {
    if (undoStack.empty())
        throw std::runtime_error("Nothing to undo.");

    std::unique_ptr<UndoAction> action = std::move(undoStack.back());
    undoStack.pop_back();
    action->undo();
    redoStack.push_back(std::move(action));
}

void Service::redo() {
    if (redoStack.empty())
        throw std::runtime_error("Nothing to redo.");

    std::unique_ptr<UndoAction> action = std::move(redoStack.back());
    redoStack.pop_back();
    action->redo();
    undoStack.push_back(std::move(action));
}