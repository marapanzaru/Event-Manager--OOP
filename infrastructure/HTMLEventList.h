#pragma once
#include "FileEventList.h"

#include <fstream>

class HTMLEventlist : public FileEventlist
{
public:
    HTMLEventlist();
    ~HTMLEventlist() {}

    void writeToFile() override;
    void displayEventlist() const override;
};
