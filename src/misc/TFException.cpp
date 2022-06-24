#include <string.h>

#include "TFException.hpp"

const char* DividedByZeroException::CANNED_MESSAGE = "Divided by 0!";

const char* InvalidArgumentException::CANNED_MESSAGE = "Invalid argument!";

const char* InvalidFormulaException::CANNED_MESSAGE = "Invalid formulation!";

const char* DividedByZeroException::what() const noexcept
{
    return CANNED_MESSAGE;
}

InvalidArgumentException::InvalidArgumentException(const char* _msg)
{
    static int len1 = strlen(CANNED_MESSAGE);
    int len2 = strlen(_msg);
    
    this->message = new char[len1 + len2 + 2];
    strcpy(this->message, CANNED_MESSAGE);
    strcpy(this->message + len1 + 1, _msg);
    this->message[len1] = ' ';
}

InvalidArgumentException::InvalidArgumentException(const InvalidArgumentException& copy)
{
    this->message = new char[strlen(copy.message) + 1];
    strcpy(this->message, copy.message);
}

InvalidArgumentException::~InvalidArgumentException()
{
    delete this->message;
}

const InvalidArgumentException& InvalidArgumentException::operator=(const InvalidArgumentException& copy)
{
    if(this == &copy)
    {
        return copy;
    }
    
    int lenC = strlen(copy.message);
    if(strlen(this->message) != lenC)
    {
        delete this->message;
        this->message = new char[lenC + 1];
    }
    strcpy(this->message, copy.message);
    
    return *this;
}

const char* InvalidArgumentException::what() const noexcept
{
    return this->message;
}

InvalidFormulaException::InvalidFormulaException(const char* _msg)
{
    static int len1 = strlen(CANNED_MESSAGE);
    int len2 = strlen(_msg);
    
    this->message = new char[len1 + len2 + 2];
    strcpy(this->message, CANNED_MESSAGE);
    strcpy(this->message + len1 + 1, _msg);
    this->message[len1] = ' ';
}

InvalidFormulaException::InvalidFormulaException(const InvalidFormulaException& copy)
{
    this->message = new char[strlen(copy.message) + 1];
    strcpy(this->message, copy.message);
}

InvalidFormulaException::~InvalidFormulaException()
{
    delete this->message;
}

const InvalidFormulaException& InvalidFormulaException::operator=(const InvalidFormulaException& copy)
{
    if(this == &copy)
    {
        return copy;
    }
    
    int lenC = strlen(copy.message);
    if(strlen(this->message) != lenC)
    {
        delete this->message;
        this->message = new char[lenC + 1];
    }
    strcpy(this->message, copy.message);
    
    return *this;
}

const char* InvalidFormulaException::what() const noexcept
{
    return this->message;
}
