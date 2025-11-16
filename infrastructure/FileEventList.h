#pragma once
#include "EventList.h"

class FileEventlist : public EventList
{
protected:
    std::string filename;

public:
    FileEventlist();
    virtual ~FileEventlist() {}

    void setFilename(const std::string& filename);
    virtual void writeToFile() = 0;
    virtual void displayEventlist() const = 0;
};
