#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "hardware.h"
#include "instructions.h"
#include "ali.h"

using namespace std;

//
// Start of Hardware definitions
//
// Default constructor of Hardware class that sets everything to 0 or nullptr
Hardware::Hardware() {
    // Set all pointers of instruction_memory array to nullptr
    for (auto &e : instruction_memory) {
        e = nullptr;
    }

    // Set all elements of value_memory array to 0
    for (auto &e : value_memory) {
        e = 0;
    }

    // Default values of 0 assigned to all hardware
    a = 0;
    b = 0;
    pc = 0;
    zero_bit = 0;
    overflow_bit = 0;
}
//
// End of Hardware definitions
//



//
// Start of Instruction definitions
//
// Default constructor for Instruction class
Instruction::Instruction() {
    hardware_pointer = nullptr;
    printString = "N/A";
    argValue = "N/A";
}

// Prints everything needed
void Instruction::print() const{
    cout << "Instruction: " << printString << " ";

    // Print out the instructions value if it exists
    if (argValue == "N/A") {
        cout << endl;
    } else {
        cout << argValue << endl;
    }

    cout << "Register A: " << hardware_pointer->a << endl;
    cout << "Register B: " << hardware_pointer->b << endl;
    cout << "Overflow bit: " << hardware_pointer->overflow_bit << endl;
    cout << "Zero bit: " << hardware_pointer->zero_bit << endl;
    cout << "Symbols and values: " << endl;

    // Loops through the symbol table containing all the symbols
    // and their values. The symbols are their values are printed
    // out into the console.
    for (const auto& elem : hardware_pointer->symbol_table) {
        cout << elem.first << ": " << hardware_pointer->value_memory[elem.second] << endl;
    }

    cout << endl;
}
//
// End of Instruction definitions
//


//
// Start of DEC definitions
//
void DEC::execute() {
    printString = "DEC";  // Assign name

    // Loop through the memory to check if the location is empty and if the address
    // is not yet used in the map.
    for (int i = 0; i < 128; i++) {
        bool found = false;  // Index (address in array) not found yet

        // If the current index of the instruction array is empty,
        // check if the map (symbol_table) does not have that address
        // If so, then assign symbol to according spot in memory
        if (hardware_pointer->instruction_memory[i] == nullptr) {
            for (auto &e : hardware_pointer->symbol_table) {
                if (e.second == i) {
                    found = true;
                    break;
                }
            }
            // Index not found in hash, so you cna put it in.
            if (!found) {
                hardware_pointer->symbol_table[argValue] = i;
                break;
            }
        }
    }

    hardware_pointer->pc++;  // Update pc
    print();
}
//
// End of DEC definitions
//



//
// Start of LDA definitions
//
void LDA::execute() {
    printString = "LDA";  // Name instruction LDA

    // Gets address of symbol in memory
    int symbol_address = hardware_pointer->symbol_table[argValue];

    // Assign accumulator (register a) with symbol's value
    hardware_pointer->a = hardware_pointer->value_memory[symbol_address];

    hardware_pointer->pc++;  // Update pc

    print();
}
//
// End of LDA definitions
//



//
// Start of LDB definitions
//
void LDB::execute() {
    printString = "LDB";  // Name instruction LDB

    // Gets address of symbol in memory
    int symbol_address = hardware_pointer->symbol_table[argValue];

    // Assign register b with symbol's value
    hardware_pointer->b = hardware_pointer->value_memory[symbol_address];

    hardware_pointer->pc++;  // Update pc

    print();
}
//
// End of LDB definitions
//



//
// Start of LDI definitions
//
void LDI::execute() {
    printString = "LDI";  // Assign name to LDI

    // Update accumulator with value of instruction
    hardware_pointer->a = stoi(argValue);

    hardware_pointer->pc++;  // Update pc

    print();
}
//
// End of LDI definitions
//



//
// Start of STR definitions
//
// Stores the value of accumulator into the SYMBOL at its appropriate
// index in memory (address).
void STR::execute() {
    printString = "STR";  // Assign name to STR

    // Gets the index (address) of the symbol from the hash of symbol -> index
    int symbol_index = hardware_pointer->symbol_table[argValue];

    // Stores the value of accumulator into the address of the symbol
    hardware_pointer->value_memory[symbol_index] = hardware_pointer->a;

    hardware_pointer->pc++;  // Update program counter

    print();
}
//
// End of STR definitions
//



//
// Start of XCH definitions
//
// Switches the contents of accumulator and register b
void XCH::execute() {
    printString = "XCH";  // Assign name of Instruction ot XCH

    // Temp value to store content of register a
    long long temp = hardware_pointer->a;

    // Swap register contents
    hardware_pointer->a = hardware_pointer->b;
    hardware_pointer->b = temp;

    hardware_pointer->pc++;  // Move PC
    print();
}
//
// END of XCH definitions
//



//
// Start of JMP definitions
//
void JMP::execute() {
    printString = "JMP";

    // Update PC to the value of the JMP instruction
    hardware_pointer->pc = stoi(argValue);

    print();
}
//
// END OF JMP definitions
//



//
// Start of JZS definitions
//
//  Makes PC (program counter) transfer control to the inputted number, but
//  only if the zero-result bit is set.
void JZS::execute() {
    printString = "JZS";  // Assign JZS as name

    // Moves PC to the value of the JZS instruction
    // if the overflow bit is set
    if (hardware_pointer->zero_bit == 1){
        hardware_pointer->pc = stoi(argValue);

        // Otherwise, just move to next instruction
    } else {
        hardware_pointer->pc++;
    }

    print();
}
//
// End of JZS definitions
//



//
// Start of JVS definitions
//
// Makes PC (program counter) transfer control to the inputted number, but
// only if overflow bit is set.
void JVS::execute() {
    printString = "JVS";  // Assign name of Instruction

    // Moves PC to the value of the JVS instruction
    // if the overflow bit is set
    if (hardware_pointer->overflow_bit == 1) {
        hardware_pointer->pc = stoi(argValue);

        // Otherwise, just move to next instruction
    } else {
        hardware_pointer->pc++;
    }

    print();
}
//
// END OF JVS definitions
//



//
// Start of ADD definitions
//
// Adds accumulator and register_b. The result of this
// addition is stored into the accumulator.
// If there is an overflow or zero, the respective bit is flagged.
// Only stores the addition into accumulator if the result is within the bounds.
void ADD::execute() {
    printString = "ADD";
    long long result = hardware_pointer->a + hardware_pointer->b;

    // Lower bound for 2's complement
    // Flags overflow bit
    if (result <= -2147483648 ){
        hardware_pointer->overflow_bit = 1;

        // Upper bound for 2's complement
        // Flags overflow bit
    } else if (result >= 2147483647){
        hardware_pointer->overflow_bit = 1;

        // Updates zero bit if result is 0
    } else if (result == 0){
        hardware_pointer->a = result;
        hardware_pointer->zero_bit = 1;

        // Addition was fine (no 0, no overflows)
        // Stores the result into accumulator
        // Reset overflow and zero bit
    } else {
        hardware_pointer->a = result;
        hardware_pointer->overflow_bit = 0;
        hardware_pointer->zero_bit = 0;
    }

    hardware_pointer->pc++;  // Update program counter
    print();
}

//
// END OF ADD definitions
//



//
// Start of HLT definitions
//
void HLT::execute() {
    printString = "HLT";
    print();
}
//
// END OF HLT definitions
//



//
// START OF ALI definitions
//
// Runs the main command loop and executes the instructions
void ALI::startExecution() {
    cout << "Please enter a filename that contains the SAL instructions: " << endl;
    cin >> filename;

    // Constructor of ifstream that takes in the inputted filename
    ifstream inputFile(filename);

    // File opened successfully, continue with normal execution.
    if (inputFile.is_open()) {
        cout << "File opened successfully!" << endl;

        // If not, keep prompting for correct file.
    } else {
        cout << "File did not open successfully!" << endl;

        // Loop until file is opened correctly
        while (!inputFile.is_open()) {
            cout << "Please enter a filename that contains the SAL instructions: " << endl;
            cin >> filename;

            ifstream temp(filename);

            // Makes the inputFile ifstream take the contents of temp ifstream
            inputFile.swap(temp);
        }
    }

    // Loop through the inputted SAL file line by line.
    // Each line contains an instruction.
    // Each instruction is put into memory.
    while(getline(inputFile, currentLine)) {
        // If the current line's instruction starts with DEC,
        // then make a DEC instruction and put it into memory
        if (currentLine.rfind("DEC", 0) == 0) {
            DEC* dec = new DEC();  // New instance of DEC instruction

            // Update the instruction's hardware pointer
            // with the address of the hw instance
            dec->hardware_pointer = &hw;

            // String manipulation to get the Instruction value after the Instruction
            size_t index_of_space = currentLine.find(' ');
            string instruction_value = currentLine.substr(index_of_space + 1);

            // Update the DEC instruction value
            dec->argValue = instruction_value;

            // Add the DEC instruction into memory
            hw.instruction_memory[currentIndex] = dec;

            // Check if the current line's string starts with LDA
            // If so, we add LDA instruction into Hardware's memory
        } else if (currentLine.rfind("LDA", 0) == 0) {
            LDA* lda = new LDA();  // New instance of LDA instruction

            // Update the instruction's hardware pointer
            // with the address of the hw instance
            lda->hardware_pointer = &hw;

            // String manipulation to get the Instruction value after the Instruction
            size_t index_of_space = currentLine.find(' ');
            string instruction_value = currentLine.substr(index_of_space + 1);

            // Update the LDA instruction value
            lda->argValue = instruction_value;

            // Put the instance of LDA we just made into the instruction memory
            // found of the Hardware Class
            hw.instruction_memory[currentIndex] = lda;

            // If the current line's instruction starts with LDB,
            // then make a LDB instruction and put it into memory
        } else if (currentLine.rfind("LDB", 0) == 0) {
            LDB* ldb = new LDB();  // New instance of LDB instruction

            // Update the instruction's hardware pointer
            // with the address of the hw instance
            ldb->hardware_pointer = &hw;

            // String manipulation to get the Instruction value after the Instruction
            size_t index_of_space = currentLine.find(' ');
            string instruction_value = currentLine.substr(index_of_space + 1);

            // Update the LDB instruction value
            ldb->argValue = instruction_value;

            // Put the instance of LDB we just made into the instruction memory
            // found of the Hardware Class
            hw.instruction_memory[currentIndex] = ldb;

            // If the current line's instruction starts with LDI,
            // then make a LDI instruction and put it into memory
        } else if (currentLine.rfind("LDI", 0) == 0) {
            LDI* ldi = new LDI();  // New instance of LDI instruction

            // Update the instruction's hardware pointer
            // with the address of the hw instance
            ldi->hardware_pointer = &hw;

            // String manipulation to get the Instruction value after the Instruction
            size_t index_of_space = currentLine.find(' ');
            string instruction_value = currentLine.substr(index_of_space + 1);

            // Update the LDI instruction value
            ldi->argValue = instruction_value;

            // Put the instance of LDI we just made into the instruction memory
            // found of the Hardware Class
            hw.instruction_memory[currentIndex] = ldi;

            // If the current line's instruction starts with STR,
            // then make STR instruction and put it into memory
        } else if (currentLine.rfind("STR", 0) == 0) {
            STR* str = new STR();  // New instance of STR instruction

            // Update the instruction's hardware pointer
            // with the address of the hw instance
            str->hardware_pointer = &hw;

            // String manipulation to get the Instruction value after the Instruction
            size_t index_of_space = currentLine.find(' ');
            string instruction_value = currentLine.substr(index_of_space + 1);

            // Update the STR instruction value
            str->argValue = instruction_value;

            // Put the instance of STR we just made into the instruction memory
            // found of the Hardware Class
            hw.instruction_memory[currentIndex] = str;

            // If the current line's instruction starts with XCH,
            // then make a XCH instruction and put it into memory
        } else if (currentLine.rfind("XCH", 0) == 0) {
            XCH* xch= new XCH();  // New instance of XCH instruction

            // Update the instruction's hardware pointer
            // with the address of the hw instance
            xch->hardware_pointer = &hw;

            // Put the instance of XCH we just made into the instruction memory
            // found of the Hardware Class
            hw.instruction_memory[currentIndex] = xch;

            // If the current line's instruction starts with JMP,
            // then make a JMP instruction and put it into memory
        } else if (currentLine.rfind("JMP", 0) == 0) {
            JMP* jmp = new JMP();  // New instance of JMP instruction

            // Update the instruction's hardware pointer
            // with the address of the hw instance
            jmp->hardware_pointer = &hw;

            // String manipulation to get the Instruction value after the Instruction
            size_t index_of_space = currentLine.find(' ');
            string instruction_value = currentLine.substr(index_of_space);

            // Update the JMP instruction value
            jmp->argValue = instruction_value;

            // Put the instance of JMP we just made into the instruction memory
            // found of the Hardware Class
            hw.instruction_memory[currentIndex] = jmp;

            // If the current line's instruction starts with JZS,
            // then make a JZS instruction and put it into memory
        } else if (currentLine.rfind("JZS", 0) == 0) {
            JZS* jzs = new JZS();  // New instance of JZS instruction

            // Update the instruction's hardware pointer
            // with the address of the hw instance
            jzs->hardware_pointer = &hw;

            // String manipulation to get the Instruction value after the Instruction
            size_t index_of_space = currentLine.find(' ');
            string instruction_value = currentLine.substr(index_of_space);

            // Update the JZS instruction value
            jzs->argValue = instruction_value;

            // Put the instance of JZS we just made into the instruction memory
            // found of the Hardware Class
            hw.instruction_memory[currentIndex] = jzs;

            // If the current line's instruction starts with JVS,
            // then make a JVS instruction and put it into memory
        } else if (currentLine.rfind("JVS", 0) == 0) {
            JVS* jvs = new JVS();  // New instance of JVS instruction

            // Update the instruction's hardware pointer
            // with the address of the hw instance
            jvs->hardware_pointer = &hw;

            // String manipulation to get the Instruction value after the Instruction
            size_t index_of_space = currentLine.find(' ');
            string instruction_value = currentLine.substr(index_of_space);

            // Update the JVS instruction value
            jvs->argValue = instruction_value;

            // Put the instance of JVS we just made into the instruction memory
            // found of the Hardware Class
            hw.instruction_memory[currentIndex] = jvs;

            // If the current line's instruction starts with ADD,
            // then make ADD instruction and put it into memory
        } else if (currentLine.rfind("ADD", 0) == 0) {
            ADD* add = new ADD();  // New instance of ADD instruction

            // Update the instruction's hardware pointer
            // with the address of the hw instance
            add->hardware_pointer = &hw;

            // Put the instance of ADD we just made into the instruction memory
            // found of the Hardware Class
            hw.instruction_memory[currentIndex] = add;

            // The last instruction is
        } else if (currentLine.rfind("HLT", 0) == 0) {
            HLT* hlt = new HLT();  // New instance of HLT instruction

            // Update the instruction's hardware pointer
            // with the address of the hw instance
            hlt->hardware_pointer = &hw;

            // Put the instance of HLT we just made into the instruction memory
            // found of the Hardware Class
            hw.instruction_memory[currentIndex] = hlt;
        }

        currentIndex++;  // Increase the current index of the memory array by one
    }

    // Main command loop
    while (true) {
        string command;
        cout << "Commands are q (quit), s (single), or a (all). Please enter a command: " << endl;
        cin >> command;  // Get user input

        // Quit the program if the user inputs q
        if (command == "q"){
            cout << "You have chosen to quit the program." << endl;
            exit(0);

            // Execute a single line of code if user inputs s
        } else if (command == "s" ){
            // Execute the current instruction
            hw.instruction_memory[hw.pc]->execute();

        } else if (command == "a"){
            // Counter that stores the number of instruction executed in this a command
            // This is for infinite instruction loops. If it hits 1000 (1000 instructions)
            // then, I will prompt user to continue or not with automatic all instructions.
            int counter = 0;

            // Used for checking if the user wants to continue this a loop after 1000 instructions
            // If so, it will become true, meaning the user wants to continue the loop
            bool continue_loop = false;

            // Loop through memory until we find a HLT instruction
            while (hw.instruction_memory[hw.pc]->printString != "HLT"){
                // After 1000 instructions executed in the loop, it will prompt the user
                // to continue the automatic instruction execution. If not, then the current
                // loop will break. The can choose to do other commands or quit after in
                // the normal command loop.
                if (counter >= 1000 && !continue_loop) {
                    string user_choice;

                    cout << "1000 instructions have been executed already in this a command." << endl;
                    cout << "Do you want to continue execution? Please enter n for no." << endl;
                    cout << "Any other input will continue execution." << endl;

                    cin >> user_choice;  // Get user input

                    // Breaks the automatic instruction execution loop
                    if (user_choice == "n") {
                        break;
                    }

                    continue_loop = true;  // User wants to continue automatic cmd loop
                }

                // Execute the current instruction
                hw.instruction_memory[hw.pc]->execute();

                counter++;  // Update counter by one
            }

            // After the while loop that goes through all instructions
            // Break the input prompt loop as there are no more instructions left
            break;
        }
    }
}
//
// END OF ALI definitions
//


int main(){
    ALI my_ALI;

    my_ALI.startExecution();  // Runs the whole program

    return 0;
}