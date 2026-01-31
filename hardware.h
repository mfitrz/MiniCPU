//
// Created by Michal
//

#include <string>
#include <map>

#ifndef MINICPU_HARDWARE_H
#define MINICPU_HARDWARE_H

// Forward declaration of Instruction Class in order to it as a type in Hardware
// Used for the Instruction pointer array.
class Instruction;

//
// Start of Hardware class
//
class Hardware{
    // Hardware class that holds all the registers, bits, memory, and symbol tables
public:
    // Instruction array that hold pointers to instances of Instructions
    Instruction* instruction_memory[128];

    // Value array that holds Instruction's values
    long long value_memory[128];

    // Symbol table holding the Instruction's name as key and where it is stored in memory as a value
    std::map<std::string, int> symbol_table;

    long long a;       // Accumulator (Register A)
    long long b;       // Register B
    int pc;            // Program Counter
    int zero_bit;      // Zero bit
    int overflow_bit;  // Overflow bit

    // Default constructor that sets everything to 0 or nullptr
    Hardware();
};
//
// End of Hardware class
//

#endif //MINICPU_HARDWARE_H
