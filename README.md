# MiniCPU - Simple Assembly Language (SAL) Interpreter

A C++ implementation of a simple assembly language interpreter that simulates a basic CPU with registers, memory, and a complete instruction set.
---

## Overview

MiniCPU is an educational project that implements a simple assembly language interpreter. It simulates a minimalist CPU architecture with:
- Two general-purpose registers (A and B)
- 128 memory locations for both instructions and data
- Overflow and zero flag detection
- Support for arithmetic, control flow, and memory operations

This project demonstrates fundamental concepts in:
- Computer architecture
- Assembly language programming
- Object-oriented design (inheritance and polymorphism)
- Memory management
- Control flow execution

---

## Features

**Complete Instruction Set**: 11 instructions covering all basic operations  
**Flag System**: Overflow and zero flag detection for conditional branching  
**Interactive Execution**: Step-by-step or automatic execution modes  
**Memory Management**: Symbol table for variable-to-address mapping  
**Safety Features**: 1000-instruction warning to prevent infinite loops  
**Comprehensive Testing**: 12 test files covering all functionality  

---

## Architecture

### Hardware Components

**Registers:**
- `a` - Accumulator (Register A) - Main register for arithmetic operations
- `b` - Register B - Secondary register for arithmetic operations
- `pc` - Program Counter - Points to the current instruction (0-indexed)

**Flags:**
- `zero_bit` - Set to 1 when arithmetic result equals zero
- `overflow_bit` - Set to 1 when arithmetic result exceeds 32-bit signed integer range

**Memory:**
- `instruction_memory[128]` - Stores instruction pointers
- `value_memory[128]` - Stores variable values
- `symbol_table` - Maps variable names to memory addresses

### Object-Oriented Design

```
Instruction (abstract base class)
├── DEC  (Declare variable)
├── LDA  (Load accumulator)
├── LDB  (Load register B)
├── LDI  (Load immediate)
├── STR  (Store to memory)
├── XCH  (Exchange registers)
├── ADD  (Add registers)
├── JMP  (Unconditional jump)
├── JZS  (Jump if zero set)
├── JVS  (Jump if overflow set)
└── HLT  (Halt execution)
```

---

## Instruction Set

### Memory and Data Movement

| Instruction | Format | Description |
|------------|--------|-------------|
| `DEC` | `DEC symbol` | Declare a variable (allocate memory) |
| `LDA` | `LDA symbol` | Load value from memory into accumulator (Register A) |
| `LDB` | `LDB symbol` | Load value from memory into Register B |
| `LDI` | `LDI value` | Load immediate integer value into accumulator |
| `STR` | `STR symbol` | Store accumulator value to memory location |
| `XCH` | `XCH` | Exchange contents of Register A and Register B |

### Arithmetic

| Instruction | Format | Description |
|------------|--------|-------------|
| `ADD` | `ADD` | Add Register A and Register B, store result in A. Sets overflow_bit if result exceeds 32-bit range. Sets zero_bit if result equals 0. |

### Control Flow

| Instruction | Format | Description |
|------------|--------|-------------|
| `JMP` | `JMP address` | Unconditionally jump to PC address |
| `JZS` | `JZS address` | Jump to PC address if zero_bit is set (1) |
| `JVS` | `JVS address` | Jump to PC address if overflow_bit is set (1) |
| `HLT` | `HLT` | Halt program execution |

### Important Notes:
- **Program Counter is 0-indexed**: Line 1 of your .sal file is at PC = 0, Line 2 is at PC = 1, etc.
- **Jump addresses use PC values**: When writing `JMP 5`, you jump to the 6th instruction (PC = 5)
- **Overflow behavior**: When overflow occurs, the overflow_bit is set but Register A preserves its original value

---

## Building the Project

### Prerequisites
- C++ compiler with C++11 support (g++, clang++, MSVC)
- Standard C++ library

### Compilation

**Linux/macOS:**
```bash
g++ -std=c++11 main.cpp -o minicpu
```

**Windows (MinGW):**
```bash
g++ -std=c++11 main.cpp -o minicpu.exe
```

**Windows (Visual Studio):**
```bash
cl /EHsc main.cpp
```

---

## Running the Program

### Basic Usage

1. **Start the interpreter:**
   ```bash
   ./minicpu
   ```

2. **Enter the filename when prompted:**
   ```
   Please enter a filename that contains the SAL instructions:
   program.sal
   ```

3. **Choose execution mode:**
   ```
   Commands are q (quit), s (single), or a (all). Please enter a command:
   ```

### Execution Modes

- **`s` (Single Step)**: Execute one instruction at a time, showing state after each
- **`a` (All)**: Execute all instructions automatically until HLT or 1000-step warning
- **`q` (Quit)**: Exit the program

### Example Session

```
Please enter a filename that contains the SAL instructions:
tests/test1_simple_add.sal

Commands are q (quit), s (single), or a (all). Please enter a command:
a

Instruction: DEC x
Register A: 0
Register B: 0
Overflow bit: 0
Zero bit: 0
Symbols and values:
x: 0

[... more instructions ...]

Instruction: HLT
Register A: 15
Register B: 10
Overflow bit: 0
Zero bit: 0
Symbols and values:
sum: 15
x: 5
y: 10
```

---

## Running Tests

The project includes a comprehensive test suite with 12 test files.

### Test Files Location

All test files are in the `tests/` directory:
```
tests/
├── test1_simple_add.sal
├── test2_overflow.sal
├── test3_zero_flag.sal
├── test4_exchange.sal
├── test5_simple_jump.sal
├── test6_jzs.sal
├── test7_jvs.sal
├── test8_loop_100.sal
├── test9_loop_500.sal
├── test10_nested_loop.sal
├── test11_fibonacci.sal
└── test12_loop_1000.sal
```

### Running Individual Tests

**Method 1: Running all tests from executable directory**
```bash
./minicpu
# When prompted, enter: tests/test1_simple_add.sal
# Then enter: a
```

**Method 2: Using Input Redirection**
```bash
echo -e "tests/test1_simple_add.sal\na" | ./minicpu
```

**Method 3: From tests directory**
```bash
cd tests
../minicpu
# Enter: test1_simple_add.sal
# Then: a
```

### Running All Tests (Linux/macOS)

Create a test runner script:

```bash
#!/bin/bash
for test in tests/*.sal; do
    echo "Running $test..."
    echo -e "$test\na" | ./minicpu | tail -15
    echo "---"
done
```

## Project Structure

```
MiniCPU/
├── main.cpp           # Main program with all implementations
├── hardware.h         # Hardware class definition
├── instructions.h     # Instruction class hierarchy
├── ali.h              # Assembly Language Interpreter class
├── tests/             # Test suite
│   ├── test1_simple_add.sal
│   ├── test2_overflow.sal
│   ├── test3_zero_flag.sal
│   ├── test4_exchange.sal
│   ├── test5_simple_jump.sal
│   ├── test6_jzs.sal
│   ├── test7_jvs.sal
│   ├── test8_loop_100.sal
│   ├── test9_loop_500.sal
│   ├── test10_nested_loop.sal
│   ├── test11_fibonacci.sal
│   └── test12_loop_1000.sal
├── README.md          # This file
└── .gitignore         # Git ignore patterns
```

---

## Implementation Details

### Memory Management
- **128 instruction slots**: Each holds a pointer to an Instruction object
- **128 value slots**: Each holds a long long integer value
- **Symbol table**: Maps string names to integer addresses (0-127)
- **Memory allocation**: Variables are allocated to the first available slot

### Arithmetic Details
- **32-bit signed integer range**: -2,147,483,648 to 2,147,483,647
- **Overflow detection**: Result outside this range sets overflow_bit = 1
- **Overflow behavior**: Register A preserves its original value (does not store overflowed result)
- **Zero detection**: Result exactly equal to 0 sets zero_bit = 1

### Control Flow
- **Program Counter**: Increments after each instruction unless modified by jump
- **Jump instructions**: Set PC directly to target address
- **Conditional jumps**: Check flag bits before jumping
- **Safety feature**: After 1,000 instructions, prompt user to prevent infinite loops

---

## Troubleshooting

### Common Issues

**Problem:** File not found  
**Solution:** Ensure the .sal file is in the correct directory or provide full path

**Problem:** Segmentation fault  
**Solution:** Check that all jump addresses are valid (0 to last instruction PC)

**Problem:** Unexpected results  
**Solution:** Remember PC is 0-indexed; verify jump addresses are correct

**Problem:** Program hangs  
**Solution:** Check for infinite loops; use single-step mode to debug

**Problem:** Overflow not detected  
**Solution:** Ensure values actually exceed 2,147,483,647 (2 billion)

