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
        case 0x08: {
            *pc = -1;
            return 1;
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

        case 0x10: {
            *pc = -1;
            return 1;
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
        case 0x18: {
            *pc = -1;
            return 1;
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


        case 0x20: {
            *pc = -1;
            return 1;
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
        case 0x28: {
            *pc = -1;
            return 1;
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


        case 0x30: {
            *pc = -1;
            return 1;
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


        case 0x46: {
            std::cout << "MOV B,M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x4e: {
            std::cout << "MOV C,M" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x5f: {
            std::cout << "MOV E,A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x61: {
            std::cout << "MOV H,C" << std::endl;
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
        case 0x6f: {
            std::cout << "MOV L,A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0x78: {
            std::cout << "MOV A,B" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0x7a: {
            std::cout << "MOV A,D" << std::endl;
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


        case 0xa7: {
            std::cout << "ANA A" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xaf: {
            std::cout << "XRA A" << std::endl;
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

        case 0xe1: {
            std::cout << "POP H" << std::endl;
            *pc = *pc + 1;
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
        case 0xeb: {
            std::cout << "XCHG" << std::endl;
            *pc = *pc + 1;
            return 0;
        }


        case 0xf1: {
            std::cout << "POP PSW" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xf5: {
            std::cout << "PUSH PSW" << std::endl;
            *pc = *pc + 1;
            return 0;
        }
        case 0xfb: {
            std::cout << "EI" << std::endl;
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
