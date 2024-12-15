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
          unsigned char RAM[MAX_RAM_SIZE];
     public:
          Ram();
          ~Ram();
          void setROM(unsigned char* buffer);
          unsigned char* getCodeFromBuffer(int* ptr);
};
 
#endif