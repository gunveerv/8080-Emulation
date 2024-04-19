#include "disassembler.hpp"

/* Constructor */
Disassembler::Disassembler()
{

};

/* Deconstructor */
Disassembler::~Disassembler()
{

};

void Disassembler::disassembleRom(std::string romPath) 
{
    std::ifstream myfile;
    std::string hexString;

    if (DEBUG) {
        std::cout << "src/disassembler.cpp - Reading File: " << romPath << std::endl;
    }

    myfile.open(romPath);

    if ( myfile.is_open() ) { 
        while (myfile >> hexString) {
            unsigned int hexValue = std::stoi(hexString, nullptr, 16);
            // Output the value in hexadecimal format with '0x' prefix
            std::cout << "0x" << std::hex << hexValue << std::endl;
        }

        if (DEBUG) {
            std::cout << "Reached end of file" << std::endl;
        }
    } else {
        std::cout << "Couldn't open file\n";
    }

    myfile.close();
};

// Disassembler::disassembleInstruction(unsigned char* buffer, int* pc) 
// {

// }
