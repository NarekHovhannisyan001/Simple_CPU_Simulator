# CPU Simulator

This project is a CPU simulator. It models a fictional CPU with memory and registers. The CPU has six registers named AYB, BEN, GIM, DA, ECH, and ZA. AYB is the accumulator, which means it stores the result of any operation. BEN, GIM, DA, and ECH are general-purpose registers. ZA is a flag register used to store the results of comparisons and overflows. The CPU also has an optional GH register, which stores the address of the next instruction (like an instruction pointer).

The CPU can:
- Store data in registers.
- Work with memory.
- Do arithmetic operations.
- Compare values.
- Perform conditional or unconditional jumps.

The memory has 32 addresses, each storing one byte of data. The CPU only works with one-byte values. You can refer to memory addresses using the [] symbol, like [5] for the value at memory address 5. Supported instructions include MOV, ADD, SUB, MUL, DIV, AND, OR, NOT, CMP, JMP, JG, JL, and JE.

## How to Use

1. **Clone the repository**
   ```bash
   git clone https://github.com/your-username/cpu-simulator.git
   cd cpu-simulator
2. Build the project and run
	g++ -std=c++2a main.cpp -o cpu_simulator && ./cpu_simulator



Task Description
CPU Simulator
Implement a CPU simulator program. The purpose of the program is to represent a fictional abstract CPU, which operates with fictional abstract memory. The CPU consists of six registers. The names of the registers are AYB, BEN, GIM, DA, ECH, and ZA. AYB also represents the accumulator register, meaning that the result of any operation is automatically stored in this register. BEN, GIM, DA, ECH are general-purpose registers, while ZA also serves as a flag register where the results of arithmetic operations are stored if there is an overflow, as well as the result of the CMP operation where the comparison result is stored in the DA register, used by the JG, JE, JL operations.

If necessary, you can also include a register named GH, where the address of the next operation will be stored (equivalent to the EIP register). The CPU provides the ability to store data in a register, work with memory, perform arithmetic operations, compare values with each other, and perform conditional or unconditional jumps. The CPU Simulator program also has a special function, dump_memory(), which will print the values stored in 32 memory addresses on the screen according to the addresses.

Memory consists of only 32 addresses, each addressing one byte of space. The CPU does not work with values larger than one byte. For example, the ADD command can only add numbers of one byte. Memory referencing is done using the [] symbol, for example, [5] refers to the value located at memory address 5. Supported instructions are MOV, ADD, SUB, MUL, DIV, AND, OR, NOT, CMP (comparison), JMP (unconditional jump), JG (jump if greater), JL (jump if less), JE (jump if equal).

Memory consists of only 32 addresses, where each address occupies one byte of space. The CPU does not work with values larger than one byte. For example, the ADD command can only add one-byte numbers. Memory referencing is done using the [] symbol, for example, [5] represents the value at memory address 5.
