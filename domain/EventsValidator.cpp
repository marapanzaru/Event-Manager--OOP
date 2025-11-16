
#include "EventsValidator.h"

using namespace std;

EventException::EventException(std::vector<std::string> _errors): errors{_errors}
{
}

std::vector<std::string> EventException::getErrors() const
{
    return this->errors;
}

void EventValidator::validate(const Event & e)
{
    vector<string> errors;
    if (e.getTitle().size() < 3)
        errors.push_back("The title name cannot be less than 3 characters!\n");
    if (e.getPeople()<0)
        errors.push_back("The number of people attending must be a positive integer\n");



    size_t posWww = e.getLink().find("www");
    size_t posHttp = e.getLink().find("http");
    if (posWww != 0 && posHttp != 0)
        errors.push_back("The link must start with one of the following strings: \"www\" or \"http\"");

    std::string d = e.getDate();
    if (d.size() != 10 || d[4] != '-' || d[7] != '-')
        errors.push_back("The date must be in the format yyyy-mm-dd\n");
    else {
        int y = std::stoi(d.substr(0, 4));
        int m = std::stoi(d.substr(5, 2));
        int day = std::stoi(d.substr(8, 2));
        if (m < 1 || m > 12 || day < 1 || day > 31)
            errors.push_back("Invalid month or day in date\n");
    }


    std::string t = e.getTime();
    if (t.size() != 5 || t[2] != ':')
        errors.push_back("The time must be in the format hh:mm\n");
    else {
        int h = std::stoi(t.substr(0, 2));
        int m = std::stoi(t.substr(3, 2));
        if (h < 0 || h > 23 || m < 0 || m > 59)
            errors.push_back("Invalid hour or minute in time\n");
    }

    if (errors.size() > 0)
        throw EventException(errors);
}
