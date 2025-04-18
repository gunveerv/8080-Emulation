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
    std::ifstream myfile;
    myfile.open(romPath, std::ios::binary);
    struct Register* regPtr = this->ram.getRegister();
    // int pc = 0;

    if (DEBUG) {
        std::cout << "src/disassembler.cpp - Reading File: " << romPath << std::endl;
    }

    if (!myfile.is_open() ) { 
        std::cout << "Couldn't open file\n";
        return 1;
    } 

    // buffer points to the ram buffer
    unsigned char* buffer = this->ram.getBufferPtr();

    // read the data to ram's buffer
    myfile.read(reinterpret_cast<char*>(buffer), MAX_ROM_SIZE);
    myfile.close();

    while (regPtr->pc != -1 && regPtr->pc < MAX_ROM_SIZE) {
        this->disassembleInstruction(buffer, &(regPtr->pc));
    }
    

    // Print out data in codeBuffer
    // for (int i = 0; i < myfile.gcount(); ++i) {
    //     std::cout << static_cast<int>(codeBuffer[i]) << " ";
    // }
    // std::cout << std::endl;
    
    if (DEBUG) {
        std::cout << "Reached end of file" << std::endl;
    }

    // std::cout << regPtr->sp << std::endl;
    // std::cout << "test"<< std::endl;
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
        case 0x00:
        case 0x08:
		case 0x10:
		case 0x18:
        case 0x20:
		case 0x28:
        case 0x30:
		case 0x38:
		case 0xcb:
		case 0xd9:
		case 0xdd:
		case 0xed:
		case 0xfd: {
            std::cout << "NOP" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x01: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "LXI B,#$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0x02: {
            std::cout << "STAX B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x03: {
            std::cout << "INX B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x04: {
            std::cout << "INR B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x05: {
            std::cout << "DCR B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x06: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "MVI B,#$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }
        case 0x07: {
            std::cout << "RLC" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x09: {
            std::cout << "DAD B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x0a: {
            std::cout << "LDAX B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x0b: {
            std::cout << "DCX B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x0c: {
            std::cout << "INR C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x0d: {
            std::cout << "DCR C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x0e: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "MVI C,#$" << input << std::endl;
            *pc = *pc + 2;
            return 0;
        }
        case 0x0f: {
            std::cout << "RRC" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x11: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "LXI D,#$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0x12: {
            std::cout << "STAX D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x13: {
            std::cout << "INX D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x14: {
            std::cout << "INR D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x15: {
            std::cout << "DCR D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x16: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "MVI D,#$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }
        case 0x19: {
            std::cout << "DAD D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x1a: {
            std::cout << "LDAX D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x1b: {
            std::cout << "DCX D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x1c: {
            std::cout << "INR E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x1d: {
            std::cout << "DCR E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x1e: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "MVI E,#$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }
        case 0x1f: {
            std::cout << "RAR" << std::endl;
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
        case 0x22: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "SHLD $" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0x23: {
            std::cout << "INX H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x24: {
            std::cout << "INR H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x25: {
            std::cout << "DCR H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x26: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "MVI H,#$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }
        case 0x27: {
            std::cout << "DAA" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x29: {
            std::cout << "DAD H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x2a: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "LHLD $" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0x2b: {
            std::cout << "DCX H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x2c: {
            std::cout << "INR L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x2d: {
            std::cout << "DCR L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x2e: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "MVI L,#$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }
        case 0x2f: {
            std::cout << "CMA" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x31: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "LXI SP,#$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0x32: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "STA " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0x33: {
            std::cout << "INX SP" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x34: {
            std::cout << "INR M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x35: {
            std::cout << "DCR M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x36: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "MVI M,#$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }
        case 0x37: {
            std::cout << "STC" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x39: {
            std::cout << "DAD SP" << std::endl;
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
        case 0x3c: {
            std::cout << "INR A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x3d: {
            std::cout << "DCR A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x3e: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "MVI A,#$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }
        case 0x3f: {
            std::cout << "CMC" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x40: {
            std::cout << "MOV B,B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x41: {
            std::cout << "MOV B,C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x42: {
            std::cout << "MOV B,D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x43: {
            std::cout << "MOV B,E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x44: {
            std::cout << "MOV B,H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x45: {
            std::cout << "MOV B,L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x46: {
            std::cout << "MOV B,M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x47: {
            std::cout << "MOV B,A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x48: {
            std::cout << "MOV C,B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x49: {
            std::cout << "MOV C,C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x4a: {
            std::cout << "MOV C,D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x4b: {
            std::cout << "MOV C,E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x4c: {
            std::cout << "MOV C,H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x4d: {
            std::cout << "MOV C,L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x4e: {
            std::cout << "MOV C,M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x4f: {
            std::cout << "MOV C,A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x50: {
            std::cout << "MOV D,B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x51: {
            std::cout << "MOV D,C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x52: {
            std::cout << "MOV D,D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x53: {
            std::cout << "MOV D,E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x54: {
            std::cout << "MOV D,H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x55: {
            std::cout << "MOV D,L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x56: {
            std::cout << "MOV D,M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x57: {
            std::cout << "MOV D,A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x58: {
            std::cout << "MOV E,B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x59: {
            std::cout << "MOV E,C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x5a: {
            std::cout << "MOV E,D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x5b: {
            std::cout << "MOV E,E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x5c: {
            std::cout << "MOV E,F" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x5d: {
            std::cout << "MOV E,L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x5e: {
            std::cout << "MOV E,M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x5f: {
            std::cout << "MOV E,A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x60: {
            std::cout << "MOV H,B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x61: {
            std::cout << "MOV H,C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x62: {
            std::cout << "MOV H,D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x63: {
            std::cout << "MOV H,E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x64: {
            std::cout << "MOV H,H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x65: {
            std::cout << "MOV H,L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x66: {
            std::cout << "MOV H,M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x67: {
            std::cout << "MOV H,A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x68: {
            std::cout << "MOV L,B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x69: {
            std::cout << "MOV L,C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x6a: {
            std::cout << "MOV L,D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x6b: {
            std::cout << "MOV L,E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x6c: {
            std::cout << "MOV L,H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x6d: {
            std::cout << "MOV L,L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x6e: {
            std::cout << "MOV L,M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x6f: {
            std::cout << "MOV L,A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x70: {
            std::cout << "MOV M,B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x71: {
            std::cout << "MOV M,C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x72: {
            std::cout << "MOV M,D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x73: {
            std::cout << "MOV M,E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x74: {
            std::cout << "MOV M,H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x75: {
            std::cout << "MOV M,L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x76: {
            std::cout << "HLT" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x77: {
            std::cout << "MOV M,A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x78: {
            std::cout << "MOV A,B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x79: {
            std::cout << "MOV A,C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x7a: {
            std::cout << "MOV A,D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x7b: {
            std::cout << "MOV A,E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x7c: {
            std::cout << "MOV A,H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x7d: {
            std::cout << "MOV A,L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x7e: {
            std::cout << "MOV A,M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x7f: {
            std::cout << "MOV A,A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x80: {
            std::cout << "ADD B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x81: {
            std::cout << "ADD C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x82: {
            std::cout << "ADD D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x83: {
            std::cout << "ADD E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x84: {
            std::cout << "ADD H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x85: {
            std::cout << "ADD L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x86: {
            std::cout << "ADD M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x87: {
            std::cout << "ADD A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x88: {
            std::cout << "ADC B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x89: {
            std::cout << "ADC C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x8a: {
            std::cout << "ADC D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x8b: {
            std::cout << "ADC E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x8c: {
            std::cout << "ADC H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x8d: {
            std::cout << "ADC L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x8e: {
            std::cout << "ADC M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x8f: {
            std::cout << "ADC A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x90: {
            std::cout << "SUB B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x91: {
            std::cout << "SUB C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x92: {
            std::cout << "SUB D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x93: {
            std::cout << "SUB E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x94: {
            std::cout << "SUB H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x95: {
            std::cout << "SUB L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x96: {
            std::cout << "SUB M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x97: {
            std::cout << "SUB A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x98: {
            std::cout << "SBB B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x99: {
            std::cout << "SBB C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x9a: {
            std::cout << "SBB D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x9b: {
            std::cout << "SBB E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x9c: {
            std::cout << "SBB H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x9d: {
            std::cout << "SBB L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x9e: {
            std::cout << "SBB M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x9f: {
            std::cout << "SBB A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0xa0: {
            std::cout << "ANA B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xa1: {
            std::cout << "ANA C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xa2: {
            std::cout << "ANA D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xa3: {
            std::cout << "ANA E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xa4: {
            std::cout << "ANA H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xa5: {
            std::cout << "ANA L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xa6: {
            std::cout << "ANA M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xa7: {
            std::cout << "ANA A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xa8: {
            std::cout << "XRA B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xa9: {
            std::cout << "XRA C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xaa: {
            std::cout << "XRA D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xab: {
            std::cout << "XRA E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xac: {
            std::cout << "XRA H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xad: {
            std::cout << "XRA L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xae: {
            std::cout << "XRA M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xaf: {
            std::cout << "XRA A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0xb0: {
            std::cout << "ORA B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xb1: {
            std::cout << "ORA C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xb2: {
            std::cout << "ORA D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xb3: {
            std::cout << "ORA E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xb4: {
            std::cout << "ORA H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xb5: {
            std::cout << "ORA L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xb6: {
            std::cout << "ORA M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xb7: {
            std::cout << "ORA A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xb8: {
            std::cout << "CMP B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xb9: {
            std::cout << "CMP C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xba: {
            std::cout << "CMP D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xbb: {
            std::cout << "CMP E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xbc: {
            std::cout << "CMP H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xbd: {
            std::cout << "CMP L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xbe: {
            std::cout << "CMP M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xbf: {
            std::cout << "CMP A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0xc0: {
            std::cout << "RNZ" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xc1: {
            std::cout << "POP B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xc2: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "JNZ " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xc3: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "JMP " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xc4: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "CNZ " << "$" << input1 << input2 << std::endl;
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
        case 0xc8: {
            std::cout << "RZ" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xc9: {
            std::cout << "RET" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xca: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "JZ $" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xcc: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "CZ " << "$" << input1 << input2 << std::endl;
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


        case 0xd0: {
            std::cout << "RNC" << std::endl;
            *pc = *pc + 1;
            return 0;

        }
        case 0xd1: {
            std::cout << "POP D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xd2: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "JNC " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xd3: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "OUT #$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }
        case 0xd4: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "CNC " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xd5: {
            std::cout << "PUSH D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xd6: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "SUI #$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }
        case 0xd7: {
            std::cout << "RST 2" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xd8: {
            std::cout << "RC" << std::endl;
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
        case 0xde: {
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "SBI #$" << input1 << std::endl; 
            *pc = *pc + 2;
            return 0;
        }


        case 0xe0: {
            std::cout << "RPO" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xe1: {
            std::cout << "POP H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xe2: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "JPO " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xe3: {
            std::cout << "XTHL" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xe4: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "CPO " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xe5: {
            std::cout << "PUSH H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xe6: {
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "ANI #$" << input1 << std::endl; 
            *pc = *pc + 2;
            return 0;
        }
        case 0xe7: {
            std::cout << "RST 4" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xe8: {
            std::cout << "RPE" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xe9: {
            std::cout << "PCHL" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xea: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "JPE " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xeb: {
            std::cout << "XCHG" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xec: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "CPE " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xee: {
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "XRI #$" << input1 << std::endl; 
            *pc = *pc + 2;
            return 0;
        }
        case 0xef: {
            std::cout << "RST 5" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0xf0: {
            std::cout << "RP" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xf1: {
            std::cout << "POP PSW" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xf2: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "JP " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xf3: {
            std::cout << "DI" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xf4: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "CP " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xf5: {
            std::cout << "PUSH PSW" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xf6: {
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "ORI #$" << input1 << std::endl; 
            *pc = *pc + 2;
            return 0;
        }
        case 0xf7: {
            std::cout << "RST 6" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xf8: {
            std::cout << "RM" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xf9: {
            std::cout << "SPHL" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xfa: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "JM " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xfb: {
            std::cout << "EI" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xfc: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "CM " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xfe: {
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "CPI #$" << input1 << std::endl;
            *pc = *pc + 2;
            return 0;
        }
        case 0xff: {
            std::cout << "RST 7" << std::endl;
            *pc = *pc + 1;
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

int Disassembler::executeInstruction(unsigned char* buffer, int* pc, Register* regPtr)
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
        case 0x00:
        case 0x08:
		case 0x10:
		case 0x18:
        case 0x20:
		case 0x28:
        case 0x30:
		case 0x38:
		case 0xcb:
		case 0xd9:
		case 0xdd:
		case 0xed:
		case 0xfd: {
            *pc = *pc + 1;
            return 0;
        }
        case 0x01: {
            // B <- byte 3, C <- byte 2
            regPtr->B = buffer[*pc+2];
            regPtr->C = buffer[*pc+1];

            *pc = *pc + 3;
            return 0;
        }
        case 0x02: {
            // (BC) <- A
            regPtr->B = regPtr->A;
            *pc = *pc + 1;
            return 0;
        }
        case 0x03: {
            std::cout << "INX B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x04: {
            std::cout << "INR B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x05: {
            // Z, S, P, AC 
            // B <- B-1
            regPtr->B -= 1;

            regPtr->Z = regPtr->B == 0;
            regPtr->S = 0x80 == (regPtr->B & 0x80);
            regPtr->P = this->setParity(regPtr->B);
            // regPtr->AC = 
            *pc = *pc + 1;
            return 0;
        }
        case 0x06: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "MVI B,#$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }
        case 0x07: {
            std::cout << "RLC" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x09: {
            std::cout << "DAD B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x0a: {
            std::cout << "LDAX B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x0b: {
            std::cout << "DCX B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x0c: {
            std::cout << "INR C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x0d: {
            std::cout << "DCR C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x0e: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "MVI C,#$" << input << std::endl;
            *pc = *pc + 2;
            return 0;
        }
        case 0x0f: {
            std::cout << "RRC" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x11: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "LXI D,#$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0x12: {
            std::cout << "STAX D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x13: {
            std::cout << "INX D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x14: {
            std::cout << "INR D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x15: {
            std::cout << "DCR D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x16: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "MVI D,#$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }
        case 0x19: {
            std::cout << "DAD D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x1a: {
            std::cout << "LDAX D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x1b: {
            std::cout << "DCX D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x1c: {
            std::cout << "INR E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x1d: {
            std::cout << "DCR E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x1e: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "MVI E,#$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }
        case 0x1f: {
            std::cout << "RAR" << std::endl;
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
        case 0x22: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "SHLD $" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0x23: {
            std::cout << "INX H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x24: {
            std::cout << "INR H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x25: {
            std::cout << "DCR H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x26: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "MVI H,#$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }
        case 0x27: {
            std::cout << "DAA" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x29: {
            std::cout << "DAD H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x2a: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "LHLD $" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0x2b: {
            std::cout << "DCX H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x2c: {
            std::cout << "INR L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x2d: {
            std::cout << "DCR L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x2e: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "MVI L,#$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }
        case 0x2f: {
            std::cout << "CMA" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x31: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "LXI SP,#$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0x32: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "STA " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0x33: {
            std::cout << "INX SP" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x34: {
            std::cout << "INR M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x35: {
            std::cout << "DCR M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x36: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "MVI M,#$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }
        case 0x37: {
            std::cout << "STC" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x39: {
            std::cout << "DAD SP" << std::endl;
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
        case 0x3c: {
            std::cout << "INR A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x3d: {
            std::cout << "DCR A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x3e: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "MVI A,#$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }
        case 0x3f: {
            std::cout << "CMC" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x40: {
            std::cout << "MOV B,B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x41: {
            std::cout << "MOV B,C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x42: {
            std::cout << "MOV B,D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x43: {
            std::cout << "MOV B,E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x44: {
            std::cout << "MOV B,H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x45: {
            std::cout << "MOV B,L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x46: {
            std::cout << "MOV B,M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x47: {
            std::cout << "MOV B,A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x48: {
            std::cout << "MOV C,B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x49: {
            std::cout << "MOV C,C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x4a: {
            std::cout << "MOV C,D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x4b: {
            std::cout << "MOV C,E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x4c: {
            std::cout << "MOV C,H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x4d: {
            std::cout << "MOV C,L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x4e: {
            std::cout << "MOV C,M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x4f: {
            std::cout << "MOV C,A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x50: {
            std::cout << "MOV D,B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x51: {
            std::cout << "MOV D,C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x52: {
            std::cout << "MOV D,D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x53: {
            std::cout << "MOV D,E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x54: {
            std::cout << "MOV D,H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x55: {
            std::cout << "MOV D,L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x56: {
            std::cout << "MOV D,M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x57: {
            std::cout << "MOV D,A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x58: {
            std::cout << "MOV E,B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x59: {
            std::cout << "MOV E,C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x5a: {
            std::cout << "MOV E,D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x5b: {
            std::cout << "MOV E,E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x5c: {
            std::cout << "MOV E,F" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x5d: {
            std::cout << "MOV E,L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x5e: {
            std::cout << "MOV E,M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x5f: {
            std::cout << "MOV E,A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x60: {
            std::cout << "MOV H,B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x61: {
            std::cout << "MOV H,C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x62: {
            std::cout << "MOV H,D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x63: {
            std::cout << "MOV H,E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x64: {
            std::cout << "MOV H,H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x65: {
            std::cout << "MOV H,L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x66: {
            std::cout << "MOV H,M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x67: {
            std::cout << "MOV H,A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x68: {
            std::cout << "MOV L,B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x69: {
            std::cout << "MOV L,C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x6a: {
            std::cout << "MOV L,D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x6b: {
            std::cout << "MOV L,E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x6c: {
            std::cout << "MOV L,H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x6d: {
            std::cout << "MOV L,L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x6e: {
            std::cout << "MOV L,M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x6f: {
            std::cout << "MOV L,A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x70: {
            std::cout << "MOV M,B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x71: {
            std::cout << "MOV M,C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x72: {
            std::cout << "MOV M,D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x73: {
            std::cout << "MOV M,E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x74: {
            std::cout << "MOV M,H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x75: {
            std::cout << "MOV M,L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x76: {
            std::cout << "HLT" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x77: {
            std::cout << "MOV M,A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x78: {
            std::cout << "MOV A,B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x79: {
            std::cout << "MOV A,C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x7a: {
            std::cout << "MOV A,D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x7b: {
            std::cout << "MOV A,E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x7c: {
            std::cout << "MOV A,H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x7d: {
            std::cout << "MOV A,L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x7e: {
            std::cout << "MOV A,M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x7f: {
            std::cout << "MOV A,A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x80: {
            std::cout << "ADD B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x81: {
            std::cout << "ADD C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x82: {
            std::cout << "ADD D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x83: {
            std::cout << "ADD E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x84: {
            std::cout << "ADD H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x85: {
            std::cout << "ADD L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x86: {
            std::cout << "ADD M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x87: {
            std::cout << "ADD A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x88: {
            std::cout << "ADC B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x89: {
            std::cout << "ADC C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x8a: {
            std::cout << "ADC D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x8b: {
            std::cout << "ADC E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x8c: {
            std::cout << "ADC H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x8d: {
            std::cout << "ADC L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x8e: {
            std::cout << "ADC M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x8f: {
            std::cout << "ADC A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x90: {
            std::cout << "SUB B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x91: {
            std::cout << "SUB C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x92: {
            std::cout << "SUB D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x93: {
            std::cout << "SUB E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x94: {
            std::cout << "SUB H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x95: {
            std::cout << "SUB L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x96: {
            std::cout << "SUB M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x97: {
            std::cout << "SUB A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x98: {
            std::cout << "SBB B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x99: {
            std::cout << "SBB C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x9a: {
            std::cout << "SBB D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x9b: {
            std::cout << "SBB E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x9c: {
            std::cout << "SBB H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x9d: {
            std::cout << "SBB L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x9e: {
            std::cout << "SBB M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x9f: {
            std::cout << "SBB A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0xa0: {
            std::cout << "ANA B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xa1: {
            std::cout << "ANA C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xa2: {
            std::cout << "ANA D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xa3: {
            std::cout << "ANA E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xa4: {
            std::cout << "ANA H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xa5: {
            std::cout << "ANA L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xa6: {
            std::cout << "ANA M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xa7: {
            std::cout << "ANA A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xa8: {
            std::cout << "XRA B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xa9: {
            std::cout << "XRA C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xaa: {
            std::cout << "XRA D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xab: {
            std::cout << "XRA E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xac: {
            std::cout << "XRA H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xad: {
            std::cout << "XRA L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xae: {
            std::cout << "XRA M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xaf: {
            std::cout << "XRA A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0xb0: {
            std::cout << "ORA B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xb1: {
            std::cout << "ORA C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xb2: {
            std::cout << "ORA D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xb3: {
            std::cout << "ORA E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xb4: {
            std::cout << "ORA H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xb5: {
            std::cout << "ORA L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xb6: {
            std::cout << "ORA M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xb7: {
            std::cout << "ORA A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xb8: {
            std::cout << "CMP B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xb9: {
            std::cout << "CMP C" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xba: {
            std::cout << "CMP D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xbb: {
            std::cout << "CMP E" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xbc: {
            std::cout << "CMP H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xbd: {
            std::cout << "CMP L" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xbe: {
            std::cout << "CMP M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xbf: {
            std::cout << "CMP A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0xc0: {
            std::cout << "RNZ" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xc1: {
            std::cout << "POP B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xc2: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "JNZ " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xc3: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "JMP " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xc4: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "CNZ " << "$" << input1 << input2 << std::endl;
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
        case 0xc8: {
            std::cout << "RZ" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xc9: {
            std::cout << "RET" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xca: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "JZ $" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xcc: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "CZ " << "$" << input1 << input2 << std::endl;
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


        case 0xd0: {
            std::cout << "RNC" << std::endl;
            *pc = *pc + 1;
            return 0;

        }
        case 0xd1: {
            std::cout << "POP D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xd2: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "JNC " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xd3: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "OUT #$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }
        case 0xd4: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "CNC " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xd5: {
            std::cout << "PUSH D" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xd6: {
            std::string input = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "SUI #$" << input << std::endl; //D8
            *pc = *pc + 2;
            return 0;
        }
        case 0xd7: {
            std::cout << "RST 2" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xd8: {
            std::cout << "RC" << std::endl;
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
        case 0xde: {
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "SBI #$" << input1 << std::endl; 
            *pc = *pc + 2;
            return 0;
        }


        case 0xe0: {
            std::cout << "RPO" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xe1: {
            std::cout << "POP H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xe2: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "JPO " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xe3: {
            std::cout << "XTHL" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xe4: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "CPO " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xe5: {
            std::cout << "PUSH H" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xe6: {
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "ANI #$" << input1 << std::endl; 
            *pc = *pc + 2;
            return 0;
        }
        case 0xe7: {
            std::cout << "RST 4" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xe8: {
            std::cout << "RPE" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xe9: {
            std::cout << "PCHL" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xea: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "JPE " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xeb: {
            std::cout << "XCHG" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xec: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "CPE " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xee: {
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "XRI #$" << input1 << std::endl; 
            *pc = *pc + 2;
            return 0;
        }
        case 0xef: {
            std::cout << "RST 5" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0xf0: {
            std::cout << "RP" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xf1: {
            std::cout << "POP PSW" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xf2: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "JP " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xf3: {
            std::cout << "DI" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xf4: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "CP " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xf5: {
            std::cout << "PUSH PSW" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xf6: {
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "ORI #$" << input1 << std::endl; 
            *pc = *pc + 2;
            return 0;
        }
        case 0xf7: {
            std::cout << "RST 6" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xf8: {
            std::cout << "RM" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xf9: {
            std::cout << "SPHL" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xfa: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "JM " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xfb: {
            std::cout << "EI" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xfc: {
            std::string input2 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+2]);
            std::cout << "CM " << "$" << input1 << input2 << std::endl;
            *pc = *pc + 3;
            return 0;
        }
        case 0xfe: {
            std::string input1 = this->disassemblerToStringHex(&buffer[*pc+1]);
            std::cout << "CPI #$" << input1 << std::endl;
            *pc = *pc + 2;
            return 0;
        }
        case 0xff: {
            std::cout << "RST 7" << std::endl;
            *pc = *pc + 1;
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

int Disassembler::setParity(unsigned char A)
{
    int count = 0;

    for (int i = 0; i < 8; i++)
    {
        unsigned char tmp = A;
        tmp <<= i;
        tmp &= 0x80;
        count += (tmp == 0x80);
    }

    return ((count &= 0x01) == 0);
}
