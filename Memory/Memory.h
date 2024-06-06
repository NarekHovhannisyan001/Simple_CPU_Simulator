#ifndef MEMORY_H
#define MEMORY_H

#include <array>
// #include <cstdint>

class Memory {
public:
    Memory();
    unsigned char read(unsigned char address) const;
    void write(unsigned char address, unsigned char value);
    void dump() const;

private:
    std::array<unsigned char, 32> mem;
};

#include "Memory.hpp"

#endif // MEMORY_H
