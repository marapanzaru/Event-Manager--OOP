#include "event.h"
#include <windows.h>
#include <shellapi.h>
#include <sstream>

Event::Event() : title(""), description(""), date(""), time(""), peopleGoing(0), link("") {}

Event::Event(const std::string& title, const std::string& description, const std::string& date, const std::string& time, int peopleGoing, const std::string& link)
    : title(title), description(description), date(date), time(time), peopleGoing(peopleGoing), link(link) {}

void Event::open()
{
    ShellExecuteA(NULL, NULL, "chrome.exe", this->getLink().c_str(), NULL, SW_SHOWMAXIMIZED);
}

std::string Event::getTitle() const { return title; }
std::string Event::getDescription() const { return description; }
std::string Event::getDate() const { return date; }
std::string Event::getTime() const { return time; }
int Event::getPeople() const { return peopleGoing; }
std::string Event::getLink() const { return link; }

void Event::setTitle(const std::string& newTitle) { title = newTitle; }
void Event::setDescription(const std::string& newDescription) { description = newDescription; }
void Event::setDate(const std::string& newDate) { date = newDate; }
void Event::setTime(const std::string& newTime) { time = newTime; }
void Event::setLink(const std::string& newLink) { link = newLink; }

void Event::setPeopleGoing(int newPeopleGoing) {
    if (newPeopleGoing >= 0) {
        peopleGoing = newPeopleGoing;
    }
}

void Event::incrementPeople() { peopleGoing++; }

void Event::decrementPeople() {
    if (peopleGoing > 0) {
        peopleGoing--;
    }
}

bool Event::operator==(const Event& other) const {
    return title == other.title && date == other.date && time == other.time;
}

std::string Event::toString() const {
    return title + "|" + description + "|" + date + " " + time + "|Going: " + std::to_string(peopleGoing) + "|Link: " + link;
}


std::ostream& operator<<(std::ostream& os, const Event& event) {
    os << event.title << "|" << event.description << "|" << event.date << "|"
       << event.time << "|" << event.peopleGoing << "|" << event.link;
    return os;
}

std::istream& operator>>(std::istream& is, Event& event) {
    std::string line;
    if (!std::getline(is, line)) {
        return is;
    }

    std::stringstream ss(line);
    std::string token;

    if (!std::getline(ss, event.title, '|')) return is;


    if (!std::getline(ss, event.description, '|')) return is;


    if (!std::getline(ss, event.date, '|')) return is;


    if (!std::getline(ss, event.time, '|')) return is;


    if (!std::getline(ss, token, '|')) return is;
    try {
        event.peopleGoing = std::stoi(token);
    } catch (const std::exception& e) {
        event.peopleGoing = 0;
    }


    if (!std::getline(ss, event.link)) return is;

    return is;
}
