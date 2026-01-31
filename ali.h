//
// Created by Michal
//
#include <string>

#ifndef MINICPU_ALI_H
#define MINICPU_ALI_H

//
// START OF ALI
//
class ALI {
    // ALI class that runs the main command loop
public:
    Hardware hw;              // Hardware instance
    std::string filename;     // Filename inputted by user for SAL txt file
    std::string currentLine;  // Current instruction line in file

    // Current index of the memory array
    // Used to put the Instruction in the correct spot in the memory array
    int currentIndex = 0;

    // Runs the main command loop and executes all the instructions
    void startExecution();
};
//
// END OF ALI
//

#endif //MINICPU_ALI_H
