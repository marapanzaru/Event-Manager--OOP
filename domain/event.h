#pragma once
#include <iostream>
#include <string>

class Event
{
private:
    std::string title;
    std::string description;
    std::string date;
    std::string time;
    int peopleGoing;
    std::string link;
    
public:

    Event();

    Event(const std::string& title, const std::string& description, const std::string& date, const std::string& time, int peopleGoing, const std::string& link);
    

    std::string getTitle() const;
    std::string getDescription() const;
    std::string getDate() const;
    std::string getTime() const;
    int getPeople() const;
    std::string getLink() const;


    void setTitle(const std::string& newTitle);
    void setDescription(const std::string& newDescription);
    void setDate(const std::string& newDate);
    void setTime(const std::string& newTime);
    void setPeopleGoing(int newPeopleGoing);
    void setLink(const std::string& newLink);

    void open();


    void incrementPeople();
    void decrementPeople();

    bool operator==(const Event& other) const;

    std::string toString() const;
    

    friend std::ostream& operator<<(std::ostream& os, const Event& event);
    friend std::istream& operator>>(std::istream& is, Event& event);
};