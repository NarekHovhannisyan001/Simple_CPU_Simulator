#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "Memory.h"
#include <iostream>

Memory::Memory() {
    mem.fill(0);
}

unsigned char Memory::read(unsigned char address) const {
    if (address >= mem.size()) {
        throw std::out_of_range("Memory address out of range");
    }
    return mem[address];
}

void Memory::write(unsigned char address, unsigned char value) {
    if (address >= mem.size()) {
        throw std::out_of_range("Memory address out of range");
    }
    mem[address] = value;
}
void Memory::dump() const {
    for (size_t i = 0; i < mem.size(); ++i) {
        std::cout << "Memory[" << i << "] = " << +mem[i] << std::endl;
    }
}

#endif //MEMORY_HPP