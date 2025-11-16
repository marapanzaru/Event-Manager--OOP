
#include "FileEventList.h"
#include <fstream>
#include <stdexcept>

FileEventlist::FileEventlist() : EventList{}, filename{""}
{
}

void FileEventlist::setFilename(const std::string& filename)
{   std::ofstream fout(filename);
	if (!fout.is_open())
		throw std::runtime_error("Could not open file: " + filename);
	fout.close();
	this->filename = filename;
}