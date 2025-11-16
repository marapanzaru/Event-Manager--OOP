
#include "CSVEventList.h"
#include <fstream>
#include <Windows.h>
#include "RepositoryExceptions.h"

using namespace std;

void CSVEventlist::writeToFile()
{
    ofstream f(this->filename);

    if (!f.is_open())
        throw FileException("The file could not be opened!");

    for (auto s : this->events) {
        f << s.getTitle() << ","
            << s.getDescription() << ","
            << s.getDate() << ","
            << s.getPeople() << ","
            << s.getLink() << "\n";
    }
    f.close();
}

void CSVEventlist::displayEventlist() const
{
    string aux = "\"" + this->filename + "\"";
    //ShellExecuteA(NULL, NULL, "C:\\Program Files (x86)\\OpenOffice 4\\program\\scalc.exe", aux.c_str(), NULL, SW_SHOWMAXIMIZED);
    //ShellExecuteA(NULL, NULL, "c:\\Program Files\\Microsoft Office\\Office15\\EXCEL.EXE", aux.c_str(), NULL, SW_SHOWMAXIMIZED);
    ShellExecuteA(NULL, "open", "notepad.exe", aux.c_str(), NULL, SW_SHOW);
}
