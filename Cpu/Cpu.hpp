#ifndef CPU_HPP
#define CPU_HPP

// #include "Cpu.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

Cpu::Cpu() : AYB(0), BEN(0), GIM(0), DA(0), ECH(0), ZA(0), GH(0) {}

Cpu::Cpu(const std::string& filepath) : Cpu() {
    load_program(filepath);
    parse_labels();
}

void Cpu::load_program(const std::string& filepath) {
    std::ifstream file(filepath);
    std::string line;
    while (std::getline(file, line)) {
        program.push_back(line);
    }
}

void Cpu::parse_labels() {
    for (int i = 0; i < program.size(); ++i) {
        std::string line = program[i];
        if (!line.empty() && line.back() == ':') {
            labels[line.substr(0, line.size() - 1)] = i;
        }
    }
}

void Cpu::execute_program() {
    GH = 0;
    while (GH < program.size()) {
        std::string instruction = program[GH];
        if (!instruction.empty() && instruction[0] != '#') {
            execute(instruction);
        }
        GH++;
    }
}

void Cpu::execute(const std::string& instruction) {
    std::istringstream iss(instruction);
    std::string opcode, operand1, operand2;
    iss >> opcode;
    try {
        if (opcode == "MOV") {
            iss >> operand1 >> operand2;
            mov(operand1, operand2);
        } else if (opcode == "ADD") {
            iss >> operand1 >> operand2;
            add(operand1, operand2);
        } else if (opcode == "SUB") {
            iss >> operand1 >> operand2;
            sub(operand1, operand2);
        } else if (opcode == "MUL") {
            iss >> operand1 >> operand2;
            mul(operand1, operand2);
        } else if (opcode == "DIV") {
            iss >> operand1 >> operand2;
            div(operand1, operand2);
        } else if (opcode == "AND") {
            iss >> operand1 >> operand2;
            and_op(operand1, operand2);
        } else if (opcode == "OR") {
            iss >> operand1 >> operand2;
            or_op(operand1, operand2);
        } else if (opcode == "NOT") {
            iss >> operand1;
            not_op(operand1);
        } else if (opcode == "CMP") {
            iss >> operand1 >> operand2;
            cmp(operand1, operand2);
        } else if (opcode == "JE") {
            iss >> operand1;
            je(operand1);
        } else if (opcode == "JG") {
            iss >> operand1;
            jg(operand1);
        } else if (opcode == "JL") {
            iss >> operand1;
            jl(operand1);
        } else if (opcode == "JMP") {
            iss >> operand1;
            jmp(operand1);
        } else {
            throw std::invalid_argument("Invalid opcode: " + opcode);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error executing instruction '" << instruction << "': " << e.what() << std::endl;
    }
}

void Cpu::mov(const std::string& dest, const std::string& src) {
    if (src[0] == '[' && src.back() == ']') {
        char srcAddress = std::stoi(src.substr(1, src.size() - 2));
        if (dest[0] == '[' && dest.back() == ']') {
            char destAddress = std::stoi(dest.substr(1, dest.size() - 2));
            memory.write(destAddress, memory.read(srcAddress));
        } else {
            get_register(dest) = memory.read(srcAddress);
        }
    } else {
        if (dest[0] == '[' && dest.back() == ']') {
            char destAddress = std::stoi(dest.substr(1, dest.size() - 2));
            if (std::isdigit(src[0])) {
                memory.write(destAddress, std::stoi(src));
            } else {
                memory.write(destAddress, get_register(src));
            }
        } else {
            get_register(dest) = std::isdigit(src[0]) ? std::stoi(src) : get_register(src);
        }
    }
}

void Cpu::add(const std::string& dest, const std::string& src) {
    char& reg = get_register(dest);
    if (src[0] == '[' && src.back() == ']') {
        char address = std::stoi(src.substr(1, src.size() - 2));
        reg += memory.read(address);
    } else {
        reg += get_register(src);
    }
}

void Cpu::sub(const std::string& dest, const std::string& src) {
    char& reg = get_register(dest);
    if (src[0] == '[' && src.back() == ']') {
        char address = std::stoi(src.substr(1, src.size() - 2));
        reg -= memory.read(address);
    } else {
        reg -= get_register(src);
    }
}

void Cpu::mul(const std::string& dest, const std::string& src) {
    char& reg = get_register(dest);
    if (src[0] == '[' && src.back() == ']') {
        char address = std::stoi(src.substr(1, src.size() - 2));
        reg *= memory.read(address);
    } else {
        reg *= get_register(src);
    }
}

void Cpu::div(const std::string& dest, const std::string& src) {
    char& reg = get_register(dest);
    char divisor;
    if (src[0] == '[' && src.back() == ']') {
        char address = std::stoi(src.substr(1, src.size() - 2));
        divisor = memory.read(address);
    } else {
        divisor = get_register(src);
    }

    if (divisor != 0) {
        reg /= divisor;
    } else {
        std::cerr << "Error: Division by zero" << std::endl;
    }
}

void Cpu::and_op(const std::string& dest, const std::string& src) {
    get_register(dest) &= get_register(src);
}

void Cpu::or_op(const std::string& dest, const std::string& src) {
    get_register(dest) |= get_register(src);
}

void Cpu::not_op(const std::string& dest) {
    get_register(dest) = ~get_register(dest);
}

void Cpu::cmp(const std::string& dest, const std::string& src) {
    char lhs = (dest[0] == '[') ? memory.read(std::stoi(dest.substr(1, dest.size() - 2))) : get_register(dest);
    char rhs = (src[0] == '[') ? memory.read(std::stoi(src.substr(1, src.size() - 2))) : get_register(src);
    if (lhs == rhs) {
        ZA = 1;
    } else if (lhs > rhs) {
        ZA = 2;
    } else {
        ZA = 0;
    }
}

void Cpu::jmp(const std::string& label) {
    GH = labels.at(label) - 1;
}

void Cpu::jg(const std::string& label) {
    if (ZA == 2) {
        GH = labels.at(label) - 1;
    }
}

void Cpu::jl(const std::string& label) {
    if (ZA == 0) {
        GH = labels.at(label) - 1;
    }
}

void Cpu::je(const std::string& label) {
    if (ZA == 1) {
        GH = labels.at(label) - 1;
    }
}

char& Cpu::get_register(const std::string& name) {
    if (name == "AYB") return AYB;
    if (name == "BEN") return BEN;
    if (name == "GIM") return GIM;
    if (name == "DA") return DA;
    if (name == "ECH") return ECH;
    if (name == "ZA") return ZA;
    throw std::invalid_argument("Invalid register name: " + name);
}

void Cpu::print_registers() const {
    std::cout << "AYB = " << +AYB << std::endl;
    std::cout << "BEN = " << +BEN << std::endl;
    std::cout << "GIM = " << +GIM << std::endl;
    std::cout << "DA = " << +DA << std::endl;
    std::cout << "ECH = " << +ECH << std::endl;
    std::cout << "ZA = " << +ZA << std::endl;
    std::cout << "GH = " << +GH << std::endl;
}

void Cpu::dump_memory() const {
    memory.dump();
}


#endif //CPU_HPP