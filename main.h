#ifndef VALS_H
#define VALS_H

#define RAM_SIZE (256)

typedef enum{
    LDA = 0x01,
    LDB = 0x02,
    ADD = 0x03,
    ADDI = 0x04,
    SUB = 0x05,
    SUBI = 0x06,
    MULT = 0x07,
    MULTI = 0x08,
    NOP = 0x09,
    JMP = 0x10,
    BEQ = 0x11,
    BEQZ = 0x12,
    NBEQ = 0x13,
}INSTRUCTIONS;

#endif