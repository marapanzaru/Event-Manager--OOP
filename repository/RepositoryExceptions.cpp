
#include "RepositoryExceptions.h"
FileException::FileException(const std::string & msg) : message(msg)
{
}

const char * FileException::what() const noexcept
{
    return message.c_str();
}

RepositoryException::RepositoryException() : exception{}, message{""}
{
}

RepositoryException::RepositoryException(const std::string & msg): message{msg}
{
}

const char * RepositoryException::what() const noexcept
{
    return this->message.c_str();
}

const char * DuplicateEventException::what() const noexcept
{
    return "There is another event with the same title!";
}

const char * InexistenEventException::what() const noexcept
{
    return "There are no event with the given title!";
}