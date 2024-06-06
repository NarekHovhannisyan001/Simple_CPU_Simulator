#include "Cpu/Cpu.h"
#include <iostream>

int main() {
    Cpu cpu("program.txt");

    cpu.execute_program();
    cpu.dump_memory();
    cpu.print_registers();

    return 0;
}
