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

    if (DEBUG) {
        std::cout << "src/disassembler.cpp - Reading File: " << romPath << std::endl;
    }

    myfile.open(romPath);

    if ( myfile.is_open() ) { 
        while (myfile) {
            // pipe file's content into stream
            myfile >> this->mystring; 
        }

        if (DEBUG) {
            std::cout << "Reached end of file" << std::endl;
        }
    } else {
        std::cout << "Couldn't open file\n";
    }

    myfile.close();
};

