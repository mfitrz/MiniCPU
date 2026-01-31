//
// Created by Michal
//

#include <string>
#include "hardware.h"

#ifndef MINICPU_INSTRUCTIONS_H
#define MINICPU_INSTRUCTIONS_H

//
// Start of Instruction
//
class Instruction {
    // Abstract Instruction class that will be inherited by derived Instruction classes
    // that will implement the abstract execute function accordingly
public:
    Hardware* hardware_pointer;  // Pointer to Hardware class (on heap)
    std::string printString;     // Instruction name
    std::string argValue;        // Instruction value (if applicable)

    // Default constructor for Instruction class
    Instruction();

    // Abstract execute function that will be implemented in the
    // derived classes (each instruction). Each instruction
    // will have its own definition.
    virtual void execute()=0;

    // Prints everything needed
    void print() const;
};
//
// End of Instruction
//



//
// Start of DEC
//
class DEC: public Instruction{
public:
    void execute() override;
};
//
// End of DEC
//



//
// Start of LDA
//
class LDA: public Instruction{
public:
    void execute() override;
};
//
// End of LDA
//



//
// Start of LDB
//
class LDB: public Instruction{
public:
    void execute() override;
};
//
// End of LDB
//



//
// Start of LDI
//
class LDI: public Instruction{
public:
    void execute() override;
};
//
// End of LDI
//



//
// Start of STR
//
class STR: public Instruction{
    // Stores the value of accumulator into the SYMBOL at its appropriate
    // index in memory (address).
public:
    void execute() override;
};
//
// End of STR
//



//
// Start of XCH
//
class XCH: public Instruction{
    // Switches the contents of accumulator and register b
public:
    void execute() override;
};
//
// END of XCH
//



//
// Start of JMP
//
class JMP: public Instruction{
public:
    void execute() override;
};
//
// END OF JMP
//



//
// Start of JZS
//
class JZS: public Instruction{
    //  Makes PC (program counter) transfer control to the inputted number, but
    //  only if the zero-result bit is set.
public:
    void execute() override;
};
//
// End of JZS
//



//
// Start of JVS
//
class JVS: public Instruction{
    // Makes PC (program counter) transfer control to the inputted number, but
    // only if overflow bit is set.
public:
    void execute() override;
};
//
// END OF JVS
//



//
// Start of ADD
//
class ADD: public Instruction {
    // Adds accumulator and register_b. The result of this
    // addition is stored into the accumulator.
    // If there is an overflow or zero, the respective bit is flagged.
    // Only stores the addition into accumulator if the result is within the bounds.
public:
    void execute() override;
};
//
// END OF ADD
//



//
// Start of HLT
//
class HLT: public Instruction{
public:
    void execute() override;
};
//
// END OF HLT
//

#endif //MINICPU_INSTRUCTIONS_H
