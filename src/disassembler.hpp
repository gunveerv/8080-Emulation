#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // for std::setw
#include <sstream> // for std::ostringstream
#include "constants.hpp"

class Disassembler
{
     private: 
          unsigned char codeBuffer[MAX_ROM_SIZE];
     public:
          Disassembler();
          ~Disassembler();
          int disassembleRom(std::string romPath);
          int disassembleInstruction(unsigned char* buffer, int* pc);
          std::string disassemblerToStringHex(unsigned char* code);
};
 
#endif