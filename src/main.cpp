#include <iostream>
#include <string>

#include "disassembler.hpp"

int main() 
{
    std::cout << "8080 Emulation" << std::endl;
    Disassembler disassmberObj;

    std::string romPath;
    romPath = "./roms/spaceinvaders/invaders";

    disassmberObj.disassembleRom(romPath);
    return 0;
};