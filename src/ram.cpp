#include "ram.hpp"

/* Constructor */
Ram::Ram()
{
};

/* Deconstructor */
Ram::~Ram()
{
};

void Ram::setROM(unsigned char* buffer)
{
    std::memcpy(this->codeBuffer, buffer, 5 * sizeof(char));
};

unsigned char* Ram::getBufferPtr()
{
    return this->codeBuffer;
};

Register* Ram::getRegister()
{
    return &(this->reg);
}