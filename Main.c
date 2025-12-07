#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

typedef struct{
    uint8_t A;
    uint8_t B;
    uint8_t memory[RAM_SIZE];
    uint8_t PC;
    uint8_t halt;
}CPU;

void cpu_Reset(CPU *cpu);
void cpu_load(CPU *cpu, uint8_t *prog, size_t size);
void cpu_load_execute(CPU *cpu, uint8_t opcode);

int main(){
    CPU cpu;
    clock_t start = clock();
    cpu_Reset(&cpu);
    uint8_t prog[] = {
        ADDI, 9, 4, 7,
        END
    };
    for(int i = 0; i <= 1000000; i++){
        cpu_load(&cpu, prog, sizeof(prog));
    }
    uint8_t t = (&cpu)->memory[9];
    //printf("%d \n", t);
    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;


    printf("%f", elapsed);

    return 0;
}

void cpu_Reset(CPU *cpu){
    cpu->A = cpu->B = 0;
    cpu->PC = 0;
    cpu->halt = 0;
    memset(cpu->memory, 0, RAM_SIZE);
}

void cpu_load(CPU *cpu, uint8_t *prog, size_t size){
    cpu->PC = 0;
    memcpy(cpu->memory, prog, size);
    while (cpu->halt == 0 && cpu->PC < RAM_SIZE)
        {
            uint8_t opcode = cpu->memory[cpu->PC++];
            cpu_load_execute(cpu, opcode);
        }
}

void cpu_load_execute(CPU *cpu, uint8_t opcode){
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
        case STA: {
            uint8_t addr = cpu->memory[cpu->PC++];
            cpu->memory[addr] = cpu->A;
            break;
        }
        case STB: {
            uint8_t addr = cpu->memory[cpu->PC++];
            cpu->memory[addr] = cpu->B;
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
            if (cpu->memory[cpu->PC++] != cpu->memory[cpu->PC++]){
                cpu->PC = cpu->memory[cpu->PC++];
            }
            break;
        case DEA:
            cpu->A--;
            break;
        case DEB:
            cpu->B--;
            break;
        case DEC: {
            uint8_t addr = cpu->memory[cpu->PC++];
            cpu->memory[addr]--;
            break;
        }
        case INCRA:
            cpu->A++;
            break;
        case INCRB:
            cpu->B++;
            break;
        case INCR: {
            uint8_t addr = cpu->memory[cpu->PC++];
            cpu->memory[addr]++;
            break;
        }
        case END:
            cpu->halt = 1;
            break;
        default:
            break;
    }   
}