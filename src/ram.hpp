#ifndef RAM_H
#define RAM_H

// #include <iostream>
// #include <fstream>
// #include <string>
// #include <iomanip> // for std::setw
// #include <sstream> // for std::ostringstream
#include "constants.hpp"

class Ram
{
     private: 
          unsigned char codeBuffer[MAX_ROM_SIZE];
     public:
          Ram();
          ~Ram();
          void setROM(unsigned char* buffer);
          unsigned char* getBufferPtr();
          // unsigned char* getCodeFromBuffer(int* ptr);
};
 
#endif