#ifndef CPU_H
#define CPU_H

#include "../Memory/Memory.h"
#include <string>
#include <vector>
#include <unordered_map>


class Cpu {
public:
    Cpu();
    Cpu(const std::string& filepath);
    void execute_program();
    void execute(const std::string& instruction);
    void mov(const std::string& dest, const std::string& src);
    void add(const std::string& dest, const std::string& src);
    void sub(const std::string& dest, const std::string& src);
    void mul(const std::string& dest, const std::string& src);
    void div(const std::string& dest, const std::string& src);
    void and_op(const std::string& dest, const std::string& src);
    void or_op(const std::string& dest, const std::string& src);
    void not_op(const std::string& dest);
    void cmp(const std::string& dest, const std::string& src);
    void jmp(const std::string& label);
    void jg(const std::string& label);
    void jl(const std::string& label);
    void je(const std::string& label);
    void print_registers() const;
    void dump_memory() const;

private:
    void parse_labels();
    void load_program(const std::string& filepath);
    char& get_register(const std::string& name);

    char AYB, BEN, GIM, DA, ECH, ZA, GH;
    Memory memory;
    std::vector<std::string> program;
    std::unordered_map<std::string, int> labels;
};

#include "Cpu.hpp"

#endif // CPU_HP
