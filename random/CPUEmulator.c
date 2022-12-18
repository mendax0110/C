// include the libraries we need
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define the number of registers
#define NUM_REGISTERS 8

// The instructions array contains the list of instructions that the CPU will execute
char *instructions[] = {
    "MOV R0, #10",
    "MOV R1, #20",
    "ADD R2, R0, R1",
    "SUB R3, R1, R0",
    "MUL R4, R0, R1",
    "DIV R5, R1, R0",
    "AND R6, R0, R1",
    "OR R7, R0, R1",
    "HALT"
};

// The registers array stores the current values of the CPU's registers
int registers[NUM_REGISTERS];

// The execute_instruction function takes in an instruction and executes it
void execute_instruction(char *instruction) {
    char *token;
    char *delimiter = " ";

    // Extract the operation from the instruction
    token = strtok(instruction, delimiter);
    if (strcmp(token, "MOV") == 0) {
        // MOV instruction: Move a value into a register
        int value, destination;
        token = strtok(NULL, delimiter);
        sscanf(token, "R%d", &destination);
        token = strtok(NULL, delimiter);
        sscanf(token, "#%d", &value);
        registers[destination] = value;
    } else if (strcmp(token, "ADD") == 0) {
        // ADD instruction: Add two registers and store the result in a third register
        int source1, source2, destination;
        token = strtok(NULL, delimiter);
        sscanf(token, "R%d", &destination);
        token = strtok(NULL, delimiter);
        sscanf(token, "R%d", &source1);
        token = strtok(NULL, delimiter);
        sscanf(token, "R%d", &source2);
        registers[destination] = registers[source1] + registers[source2];
    } else if (strcmp(token, "SUB") == 0) {
        // SUB instruction: Subtract two registers and store the result in a third register
        int source1, source2, destination;
        token = strtok(NULL, delimiter);
        sscanf(token, "R%d", &destination);
        token = strtok(NULL, delimiter);
        sscanf(token, "R%d", &source1);
        token = strtok(NULL, delimiter);
        sscanf(token, "R%d", &source2);
        registers[destination] = registers[source1] - registers[source2];
    } else if (strcmp(token, "MUL") == 0) {
        // MUL instruction: Multiply two registers and store the result in a third register
        int source1, source2, destination;
        token = strtok(NULL, delimiter);
        sscanf(token, "R%d", &destination);
        token = strtok(NULL, delimiter);
        sscanf(token, "R%d", &source1);
        token = strtok(NULL, delimiter);
        sscanf(token, "R%d", &source2);
        registers[destination] = registers[source1] * registers[source2];
    } else if (strcmp(token, "DIV") == 0) {
        // DIV instruction: Divide two registers and store the result in a third register
        int source1, source2, destination;
        token = strtok(NULL, delimiter);
        sscanf(token, "R%d", &destination);
        token = strtok(NULL, delimiter);
        sscanf(token, "R%d", &source1);
        token = strtok(NULL, delimiter);
        sscanf(token, "R%d", &source2);
        registers[destination] = registers[source1] / registers[source2];
    } else if (strcmp(token, "AND") == 0) {
        // AND instruction: Bitwise AND two registers and store the result in a third register
        int source1, source2, destination;
        token = strtok(NULL, delimiter);
        sscanf(token, "R%d", &destination);
        token = strtok(NULL, delimiter);
        sscanf(token, "R%d", &source1);
        token = strtok(NULL, delimiter);
        sscanf(token, "R%d", &source2);
        registers[destination] = registers[source1] & registers[source2];
    } else if (strcmp(token, "OR") == 0) {
        // OR instruction: Bitwise OR two registers and store the result in a third register
        int source1, source2, destination;
        token = strtok(NULL, delimiter);
        sscanf(token, "R%d", &destination);
        token = strtok(NULL, delimiter);
        sscanf(token, "R%d", &source1);
        token = strtok(NULL, delimiter);
        sscanf(token, "R%d", &source2);
        registers[destination] = registers[source1] | registers[source2];
    } else if (strcmp(token, "HALT") == 0) {
        // HALT instruction: Halt the CPU
        // define "i"
        int i;
        // loop through the instructions array
        for (i = 0; i < sizeof(instructions) / sizeof(instructions[0]); i++) 
        {
            // print the current instruction
            printf("%s  ", instructions[i]);
            exit(0);
        }
    }
}

       
