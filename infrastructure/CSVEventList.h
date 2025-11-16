#pragma once
#include "FileEventlist.h"
#include <string>

class CSVEventlist: public FileEventlist
{
public:

    void writeToFile() override;

    void displayEventlist() const override;
};

