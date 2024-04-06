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
        std::cout << "Disassembler.cpp - Reading File: " << romPath << std::endl;
    }

    myfile.open(romPath);

    // always check whether the file is open
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

