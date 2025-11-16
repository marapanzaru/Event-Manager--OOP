
#include "HTMLEventList.h"
#include "RepositoryExceptions.h"
#include <Windows.h>
#include <shellapi.h>

HTMLEventlist::HTMLEventlist() : FileEventlist()
{
}

void HTMLEventlist::writeToFile()
{
    if (this->filename.empty())
        throw FileException("File name is empty!");

    std::ofstream f(this->filename);
    if (!f.is_open())
        throw FileException("Could not open the file!");


    f << "<!DOCTYPE html>\n"
      << "<html>\n"
      << "<head>\n"
      << "    <title>My Events</title>\n"
      << "    <style>\n"
      << "        table { border-collapse: collapse; width: 100%; }\n"
      << "        th, td { text-align: left; padding: 8px; }\n"
      << "        tr:nth-child(even) { background-color: #f2f2f2; }\n"
      << "        th { background-color: #4CAF50; color: white; }\n"
      << "        a { color: #0066cc; text-decoration: none; }\n"
      << "        a:hover { text-decoration: underline; }\n"
      << "    </style>\n"
      << "</head>\n"
      << "<body>\n"
      << "    <h1>My Events List</h1>\n"
      << "    <table>\n"
      << "        <tr>\n"
      << "            <th>Title</th>\n"
      << "            <th>Description</th>\n"
      << "            <th>Date</th>\n"
      << "            <th>Time</th>\n"
      << "            <th>People Going</th>\n"
      << "            <th>Link</th>\n"
      << "        </tr>\n";


    for (const auto& event : this->events)
    {
        f << "        <tr>\n"
          << "            <td>" << event.getTitle() << "</td>\n"
          << "            <td>" << event.getDescription() << "</td>\n"
          << "            <td>" << event.getDate() << "</td>\n"
          << "            <td>" << event.getTime() << "</td>\n"
          << "            <td>" << event.getPeople() << "</td>\n"
          << "            <td><a href=\"" << event.getLink() << "\" target=\"_blank\">" << event.getLink() << "</a></td>\n"
          << "        </tr>\n";
    }


    f << "    </table>\n"
      << "</body>\n"
      << "</html>\n";

    f.close();
}

void HTMLEventlist::displayEventlist() const
{
    if (this->filename.empty())
        throw FileException("File name is empty!");


    ShellExecuteA(NULL, "open", this->filename.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
