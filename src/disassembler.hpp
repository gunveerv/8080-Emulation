#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <iostream>
#include <fstream>
#include <string>
#include "constants.hpp"

class Disassembler
{
     private: 
          std::string mystring;
          unsigned char* buffer;
     public:
          Disassembler();
          ~Disassembler();
          void disassembleRom(std::string romPath);
};
 
#endif