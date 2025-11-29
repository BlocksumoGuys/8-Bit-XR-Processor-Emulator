#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

typedef struct{
    uint8_t A;
    uint8_t B;
    uint8_t memory[RAM_SIZE];
    uint8_t PC;
    uint8_t halt;
}CPU;

void cpu_Reset(CPU *cpu){
    cpu->A = 0;
    cpu->B = 0;
    cpu->PC = 0;
    cpu->halt = 0;
    memset(cpu->memory, 0, sizeof(cpu->memory));
}

void cpu_load(CPU *cpu, uint8_t *prog, size_t size){
    size = size > 256 ? 256 : size;
    for(uint8_t i = 0; i < size; i++){
        cpu->memory[i] = prog[i];
    }
}

void cpu_load_execute(CPU *cpu, uint8_t opcode){
    if(opcode){
    switch (opcode)
        {
        case LDA: { // Load A
            cpu->A = cpu->memory[cpu->PC++];
            break;
        }
        case LDB: { // Load B
            cpu->B = cpu->memory[cpu->PC++];
            break;
        }
        case ADD: { // ADD
            uint8_t destination = cpu->memory[cpu->PC++];
            uint8_t src = cpu->memory[cpu->PC++];

            uint8_t *reg_dest = (destination == 0) ? &cpu->A : &cpu->B;
            uint8_t *reg_src = (src == 0) ? &cpu->A : &cpu->B;

            *reg_dest = *reg_dest + *reg_src;
            break;
        }
        case ADDI: { // ADDI
            uint8_t dest = cpu->memory[cpu->PC++];
            uint8_t v1 = cpu->memory[cpu->PC++];
            uint8_t v2 = cpu->memory[cpu->PC++];
            cpu->memory[dest] = v1 + v2;
            break;
        }
        case SUB: { // SUB
            uint8_t destination = cpu->memory[cpu->PC++];
            uint8_t src = cpu->memory[cpu->PC++];

            uint8_t *reg_dest = (destination == 0) ? &cpu->A : &cpu->B;
            uint8_t *reg_src = (src == 0) ? &cpu->A : &cpu->B;

            *reg_dest = *reg_dest - *reg_src;
            break;
        }
        case SUBI: { // SUBI
            uint8_t dest = cpu->memory[cpu->PC++];
            uint8_t v1 = cpu->memory[cpu->PC++];
            uint8_t v2 = cpu->memory[cpu->PC++];
            cpu->memory[dest] = v1 - v2;
            break;
        }
        case MULT: { // MULT
            uint8_t destination = cpu->memory[cpu->PC++];
            uint8_t src = cpu->memory[cpu->PC++];

            uint8_t *reg_dest = (destination == 0) ? &cpu->A : &cpu->B;
            uint8_t *reg_src = (src == 0) ? &cpu->A : &cpu->B;

            *reg_dest = *reg_dest * *reg_src;
            break;
        }
        case MULTI: { // MULTI
            uint8_t dest = cpu->memory[cpu->PC++];
            uint8_t v1 = cpu->memory[cpu->PC++];
            uint8_t v2 = cpu->memory[cpu->PC++];
            cpu->memory[dest] = v1 * v2;
            break;
        } 
        case NOP: // NOP
            cpu->PC++;
            break;
        case JMP:
            cpu->PC = cpu->memory[cpu->PC++];
            break;
        case BEQ:
            if (cpu->memory[cpu->PC++] == cpu->memory[cpu->PC++]){
                cpu->PC = cpu->memory[cpu->PC++];
            }
            break;
        case BEQZ:
            if (cpu->memory[cpu->PC++] == 0){
                cpu->PC = cpu->memory[cpu->PC++];
            }
            break;
        case NBEQ:
            if (!cpu->memory[cpu->PC++] == cpu->memory[cpu->PC++]){
                cpu->PC = cpu->memory[cpu->PC++];
            }
            break;        
        case 0xFF:
            cpu->halt = 1;
            break;
        default:
            //printf("Unknown instructions at %X", cpu->memory[cpu->PC]);
            //cpu->halt = 1;
            //cpu_Reset(cpu);
            break;
        }}   
}

void cpu_running(CPU *cpu){
    while(!cpu->halt){
        uint8_t opcode = cpu->memory[cpu->PC++];
        if(cpu->PC > 255){
            cpu->PC = 0;
        }
        cpu_load_execute(cpu, opcode);
    }
}

int main(){
    CPU cpu;
    uint8_t prog[] = {
        ADDI, 9, 6, 7,
        0xFF
    };

    cpu_Reset(&cpu);
    cpu_load(&cpu, prog, sizeof(prog));
    cpu_running(&cpu);
    printf("%d", (&cpu)->memory[9]);

    return 0;
}