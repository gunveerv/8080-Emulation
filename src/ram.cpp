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
    // for (int i = 0; i < MAX_ROM_SIZE; i++)
    // {
        
    // }
};

unsigned char* Ram::getBufferPtr()
{
    return this->codeBuffer;
};