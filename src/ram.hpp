#ifndef RAM_H
#define RAM_H

// #include <iostream>
// #include <fstream>
// #include <string>
// #include <iomanip> // for std::setw
// #include <sstream> // for std::ostringstream
#include "constants.hpp"
#include <cstring>

class Ram
{
     private: 
          unsigned char codeBuffer[MAX_ROM_SIZE];
          struct Register reg = {0};
     public:
          Ram();
          ~Ram();
          void setROM(unsigned char* buffer);
          unsigned char* getBufferPtr();
          Register* getRegister();
          // unsigned char* getCodeFromBuffer(int* ptr);
};
 
#endif