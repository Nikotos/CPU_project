//-----CPU
#include <iostream>
#include "stack_t.h"
#include <assert.h>

const int RAM_SIZE = 1024,
        MIN_STACK_SIZE = 2,
        SIZEOF_CODE = 100000;
const double EPSILON = 0.000001;

struct Cpu_type {
    Stack_t stak;

    Stack_elem ax = 0;
    Stack_elem bx = 0;
    Stack_elem cx = 0;
    Stack_elem dx = 0;

    Stack_elem* ram = (Stack_elem *) calloc(RAM_SIZE, sizeof(Stack_elem));
    Stack_t calls;

    Cpu_type(): stak (), calls() {};
};

void do_commands(int* heap);
int* make_heap(FILE* CPU_COMMANDS_FILE);
void cpu_dump(Cpu_type cpu);

#define DEF_CMD(name, compiler_code, cpu_code)
#define DEF_REG(name, code)

#include "commands.h"

#undef DEF_CMD
#undef DEF_REG

int main() {
    FILE* CPU_COMMANDS_FILE = fopen("D:\\Study\\DeDnDex\\Si\\CPU_project\\cmake-build-debug\\CPU_COMMANDS.txt", "rt");
    assert(CPU_COMMANDS_FILE);

    int* heap = make_heap(CPU_COMMANDS_FILE);
    assert(heap);

    do_commands(heap);

    fclose(CPU_COMMANDS_FILE);
    return 0;
}

int* make_heap(FILE* CPU_COMMANDS_FILE) {
    int* heap = (int *) calloc(SIZEOF_CODE, sizeof(*heap));
    assert(heap);

    for (int i = 0; (fscanf(CPU_COMMANDS_FILE, "%d", &heap[i])== 1); i++);

    return heap;
}

void do_commands(int* heap) {
    Cpu_type cpu;

    int i = 0;

    while (heap[i] != 0) {
        switch (heap[i]){
            #define DEF_CMD(name, compiler_code, cpu_code)\
                    cpu_code
            #define DEF_REG(name, code)

            #include "commands.h"

            #undef DEF_REG
            #undef DEF_CMD
        }
        i++;
    }
}

void cpu_dump(Cpu_type cpu) {
    FILE* cpu_dump = fopen("dump.txt", "w");
    assert(cpu_dump);

    fprintf(cpu_dump, "\nCPU_DUMP\n"
            "\nSTACK Dump:\n");
    fclose(cpu_dump);

    cpu.stak.Dump();

    cpu_dump = fopen("dump.txt", "a");
    assert(cpu_dump);

    fprintf(cpu_dump, "\nCALLS STACK:\n");
    fclose(cpu_dump);

    cpu.calls.Dump();

    cpu_dump = fopen("dump.txt", "a");
    assert(cpu_dump);

    fprintf(cpu_dump, "\nCPU REGISTERS\n"
            "AX: %f\n"
            "BX: %f\n"
            "CX: %f\n"
            "DX: %f\n\n", cpu.ax, cpu.bx, cpu.cx, cpu.dx);

    fprintf(cpu_dump, "\n CPU RAM:\n");
    for(int i = 0; i < RAM_SIZE; i++) {
        fprintf(cpu_dump, "[%d] = %f\n", i, cpu.ram[i]);
    }
    fclose(cpu_dump);
}