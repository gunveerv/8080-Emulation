#ifndef CONSTANTS_H
#define CONSTANTS_H

#define DEBUG 1
#define MAX_ROM_SIZE 8192
#define MAX_RAM_SIZE 65536

struct Register {
    unsigned char A, B, C, D, E, H, L;
    // should be an unsigned short int
    // but this brings trouble when &(var) is used
    int sp, pc;
    unsigned char S, Z, P, CY, AC;
};

#endif
