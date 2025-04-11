#include <iostream>
#include <string>

#include "disassembler.hpp"

int main(int argc, char *argv[]) 
{
    std::cout << "8080 Emulation" << std::endl;
    Disassembler disassmberObj;

    std::string romPath;

    romPath = argc == 2 ? argv[1] : "./roms/spaceinvaders/invaders";

    disassmberObj.disassembleRom(romPath);
    return 0;
};