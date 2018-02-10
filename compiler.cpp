//---Compiler
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <map>
#include <iostream>

const int MAX_COMMAND = 100,
        SIZEOF_REG = 5,
        SIZEOF_CODE = 100000,
        SIZEOF_LABEL = 30,
        NUM_OF_LABELS = 50;

//------------------------------------------------------------
//! struct for comparing labels with their positions in code
//-----------------------------------------------------------
struct Label_type
{
    char label[SIZEOF_LABEL] = {};
    int jindex = -1;
};

void compile_file (int* i, Label_type* labels, int* labels_amount, int* heap);
void compile_command (int* index, int* heap, FILE* inputs, const char* command, Label_type* labels, const int labels_amount);
void out_to_file (int* heap, const int commands_amount);
bool is_label (char* command);

#define DEF_CMD(name, compiler_code, cpu_code)
#define DEF_REG(name, code)

#include "commands.h"

#undef DEF_REG
#undef DEF_CMD

int main() {
    //----------------------------------
    //! 'heap' with numeric commands
    //----------------------------------
    int *heap = (int *) calloc(SIZEOF_CODE, sizeof(*heap));
    assert(heap);


    //----------------------------------
    //!  array with named labels
    //----------------------------------
    Label_type *labels = (Label_type *) calloc(NUM_OF_LABELS, sizeof(*labels));
    assert(labels);

    int labels_amount = 0;
    assert(&labels_amount);

    int commands_amount = 0;   //actually iteration index
    assert(&commands_amount);

    compile_file(&commands_amount, labels, &labels_amount, heap);
    commands_amount = 0;
    compile_file( &commands_amount, labels, &labels_amount, heap);

    out_to_file(heap, commands_amount);

    return 0;
}

//-------------------------------------------------------------
//!
//! tells what register is in "register_name"
//!
//-------------------------------------------------------------
int tell_register(const char* register_name) {
    #define DEF_CMD(name, compiler_code, cpu_code)
    #define DEF_REG(name, code)\
        code
    #include "commands.h"

    #undef DEF_REG
    #undef DEF_CMD
    {
        printf("Unknown REGISTER!");
        assert(0);
    }
}

//-------------------------------------------------------------
//!
//! compile file "program.txt"
//!
//-------------------------------------------------------------
void compile_file (int* i, Label_type* labels, int* labels_amount, int* heap)
{
    FILE* inputs = fopen("program.txt", "rt");
    assert(inputs != NULL);

    char* command = (char*)calloc (MAX_COMMAND,  sizeof (*command));
    assert (command);

    while(strcmp(command, "END") != 0)
    {

        fscanf (inputs, "%s", command);
        bool label = is_label(command);

        if (!label) {
            compile_command(i, heap, inputs, command, labels, *labels_amount);
        }

        else {
            strcpy((labels[(*labels_amount)]).label, command);
            (labels[(*labels_amount)]).jindex = *i;
            (*labels_amount)++;
            printf("read label is -[%s]\n", command);
            printf("index is - [%d]\n", *i);
        }
    }

    fclose (inputs);
}

//-------------------------------------------------------------
//!
//! Convert assembler commands to numeric
//!
//-------------------------------------------------------------
void compile_command (int* index, int* heap, FILE* inputs, const char* command, Label_type* labels, const int labels_amount)
{
#define DEF_CMD(name, compiler_code, cpu_code)\
            compiler_code
#define DEF_REG(name, code)

#include "commands.h"

#undef DEF_REG
#undef DEF_CMD
    {
        printf ("UNKNOWN COMMAND: '%s'", command);
        assert(0);
    }
}

//-------------------------------------------------------------
//!
//! write numeric commands directly to the file
//!
//-------------------------------------------------------------
void out_to_file (int* heap, const int commands_amount)
{
    FILE* outputs = fopen ("CPU_COMMANDS.txt", "w");
    assert (outputs);

    int i = 0;

    while (i < commands_amount) {
        if ((heap[i] == PUSH) || (heap[i] == POP)) {
            fprintf (outputs, "%d\n%d\n%d\n", heap[i], heap[i + 1], heap[i + 2]);
            i += 3;
        }
        else if (heap[i] == JE || heap[i] == JNE || heap[i] == JA ||
                 heap[i] == JAE || heap[i] == JB || heap[i] == JBE ||
                 heap[i] == JMP || heap[i] == CALL)
        {
            fprintf (outputs, "%d\n%d\n", heap[i], heap[i + 1]);
            i += 2;
        }
        else {
            fprintf(outputs, "%d\n", heap[i]);
            i++;
        }
    }

    fclose (outputs);
}

//-------------------------------------------------------------
//!
//! check if readed command is label
//!
//-------------------------------------------------------------
bool is_label(char* command)
{
    if (command[0] == ':') {
        return 1;
    }
    else {
        return 0;
    }
}

