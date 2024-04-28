#include "disassembler.hpp"

/* Constructor */
Disassembler::Disassembler()
{
};

/* Deconstructor */
Disassembler::~Disassembler()
{
};

int Disassembler::disassembleRom(std::string romPath) 
{
    int pc = 0;
    std::ifstream myfile;
    myfile.open(romPath, std::ios::binary);

    if (DEBUG) {
        std::cout << "src/disassembler.cpp - Reading File: " << romPath << std::endl;
    }

    if (!myfile.is_open() ) { 
        std::cout << "Couldn't open file\n";
        return 1;
    } 

    myfile.read(reinterpret_cast<char*>(this->codeBuffer), MAX_ROM_SIZE);

    while (pc != -1 && pc < MAX_ROM_SIZE) {
        this->disassembleInstruction(this->codeBuffer, &pc);
    }
    

    // Print out data in codeBuffer
    // for (int i = 0; i < myfile.gcount(); ++i) {
    //     std::cout << static_cast<int>(codeBuffer[i]) << " ";
    // }
    // std::cout << std::endl;
    
    if (DEBUG) {
            std::cout << "Reached end of file" << std::endl;
        }

    myfile.close();
    return 0;
};


int Disassembler::disassembleInstruction(unsigned char* buffer, int* pc) 
{
    unsigned char* code = &buffer[*pc];

    std::ostringstream oss;
    oss << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(*pc);
    std::string counter = oss.str();

    // std::string counter = std::to_string(*pc);
    std::cout << counter << ": ";

    if (*pc < 0) {
        std::cout << "Program Counter invalid" << std::endl;
        return 1;
    }

    switch (*code)
    {
        case 0x00: {
            std::cout << "NOP" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x0f: {
            std::cout << "RRC" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x21: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "LXI H,#$" << input1 << input2 << std::endl; //D16
            *pc = *pc + 3;
            return 0;
        }
        case 0x27: {
            std::cout << "DAA" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x32: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "STA " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0x35: {
            std::cout << "DCR M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x3a: {
             std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "LDA $" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0x3e: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "MVI A,#$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }


        case 0xa7: {
            std::cout << "ANA A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xaf: {
            std::cout << "XRA A" << std::endl;
            *pc = *pc + 1;
            retur
            n 0;
        }
        case 0xc3: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "JMP " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xc5: {
            std::cout << "PUSH B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xc6: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "ADI #$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }
        case 0xca: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "JZ $" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xcd: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "CALL " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }


        case 0xd5: {
            std::cout << "PUSH D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xda: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "JC " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xdb: {
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "IN #$" << input1 << std::endl; 
            *pc = *pc + 2;
            return 0;
        }


        case 0xe5: {
            std::cout << "PUSH H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0xf5: {
            std::cout << "PUSH PSW" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xfe: {
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "CPI #$" << input1 << std::endl;
            *pc = *pc + 2;
            return 0;
        }


        default: {
            std::string instruction = this->disassemblerToStringHex(code);
            std::cout << "Couldn't find instruction 0x" << instruction << std::endl;
            *pc = -1;
            return 1;
        }

    }
}

std::string Disassembler::disassemblerToStringHex(unsigned char* code) 
{
    std::ostringstream oss;
    oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*code);
    std::string instruction = oss.str();
    return instruction;
}
