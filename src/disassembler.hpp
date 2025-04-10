#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // for std::setw
#include <sstream> // for std::ostringstream
#include "constants.hpp"
#include "ram.hpp"

class Disassembler
{
     private:
          Ram ram;
     public:
          Disassembler();
          ~Disassembler();
          int disassembleRom(std::string romPath);
          int disassembleInstruction(unsigned char* buffer, int* pc);
          std::string disassemblerToStringHex(unsigned char* code);
};
 
#endif