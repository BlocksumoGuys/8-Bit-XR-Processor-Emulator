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
    DEA = 0x14,
    DEB = 0x15,
    DEC = 0x16,
    INCRA = 0x17,
    INCRB = 0x18,
    INCR = 0x19,
    STA = 0x20,
    STB = 0x21,
}INSTRUCTIONS;

#endif