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
    std::memcpy(this->memory, buffer, 5 * sizeof(char));
};

unsigned char* Ram::getBufferPtr()
{
    return this->memory;
};

Register* Ram::getRegister()
{
    return &(this->reg);
}
