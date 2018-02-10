//----FOR GENERATING COMMANDS

#define COMMAND(name)\
    if (strcmp (command, #name) == 0)

#define REGISTER(name)\
    if (strcmp (register_name, #name) == 0) return name;\
    else

#define COMMON_COMMAND(name)\
    COMMAND(name)\
        {\
        heap[(*index)] = name;\
        (*index)++;\
        }\
    else

//-----------------------------------
//! Jump Commands
//! Code for Compiler
//!
//-----------------------------------
#define JUMP_COMMAND(name)\
    COMMAND(name)\
    {\
        char* label = (char*) calloc (SIZEOF_LABEL, sizeof (*label));\
        assert (label);\
\
        fscanf (inputs, " %s", label);\
\
        heap[(*index)] = name;\
        (*index)++;\
\
        int point = -1;\
        assert (&point);\
\
        for (int j = 0; j < labels_amount; j++)\
        {\
            if (strcmp(label, labels[j].label) == 0)\
                point = labels[j].jindex;\
        }\
        printf("finded label to jump is - [%s] - [%d]\n",label, point);\
        heap[(*index)] = point;\
        (*index)++;\
    }\
    else

//-----------------------------------
//!
//! Checker for JUMP COMMANDS
//!
//-----------------------------------
#define IS_GOOD_JUMPING\
        if (heap[i + 1] == -1)\
            {\
                printf ("Bad jumping\n");\
                cpu_dump (cpu);\
                assert (0);\
            }\

//-----------------------------------
//!
//! Checker for POP and PUSH
//!
//-----------------------------------
#define IS_IT_GOOD_COMMAND\
    if (bites == -1) {\
        printf ("WRONG COMMAND: '%s'\n", command);\
        assert (0);\
    }

//-------------------------------------------
//!
//! Default condition for choosing register
//!
//-------------------------------------------
#define UNKNOWN_REGISTER\
            default:\
                printf ("UNKNOWN REGISTER\n");\
                assert(0);


//-----------------------------------
//!
//! Checker for STACK for Comparing
//! Checker for size
//!
//-----------------------------------
#define IS_STACK_OK\
     if (cpu.stak.Size () < MIN_STACK_SIZE)\
            {\
                printf ("COMPARING is NOT Possible, stack size < 2\n");\
                cpu_dump (cpu);\
                assert (0);\
            }\

//-----------------------------------
//!
//! Checker if STACK EMPTY
//!
//-----------------------------------
#define IS_STACK_EMPTY\
    if (cpu.stak.Empty()) \
    {\
        printf("Stack is EMPTY");\
        cpu_dump(cpu);\
        assert(0);\
    }

//-----------------------------------
//!
//! Usual operations: +,-,*,/
//!
//-----------------------------------
#define USUAL_OPERATION(name, operation)\
      case name:\
            {\
            IS_STACK_OK\
            \
                Stack_elem x1 = cpu.stak.Pop ();\
                Stack_elem x2 = cpu.stak.Pop ();\
\
                assert (&x1);\
                assert (&x2);\
\
                cpu.stak.Push (x2 operation x1);\
            }\
            break;

//--------------------------------------------------
//!
//! NON-TRIVIAL operations: sin,cos,sqrt
//!
//--------------------------------------------------
#define TRICKY_OPERATION(name_cpu, name_math)\
    case name_cpu:\
        {\
            Stack_elem value = cpu.stak.Pop ();\
            assert (&value);\
\
            cpu.stak.Push (name_math(value));\
        }\
            break;

//--------------------------------------------------
//!
//! PUSH operation for register
//!
//--------------------------------------------------
#define REGISTER_PUSH(name_here, name_cpu)\
                case name_here:\
                    cpu.stak.Push(name_cpu);\
\
                    break;

//--------------------------------------------------
//!
//! POP operation for register
//!
//--------------------------------------------------
#define REGISTER_POP(name_here, name_cpu)\
                case name_here:\
                    name_cpu = cpu.stak.Pop();\
\
                    break;

//-----------------------------------
//! Jump Commands
//! Code for CPU
//! JUMP if CONDITION
//!
//-----------------------------------
#define JUMP_IF_CONDITION(name, condition)\
        case name:\
            IS_STACK_OK\
            {\
                Stack_elem x1 = cpu.stak.Pop();\
                Stack_elem x2 = cpu.stak.Pop();\
\
                assert (&x1);\
                assert (&x2);\
\
                if (condition)\
                {\
                    IS_GOOD_JUMPING\
                    i = heap[i + 1] - 1;\
                }\
                else\
                    i++;\
            }\
            break;


enum commands {
    END   =  0,
    PUSH  =  1,
    POP   =  2,
    IN    =  3,
    OUT   =  4,
    ADD   =  5,
    SUB   =  6,
    MUL   =  7,
    DIV   =  8,
    SQRT  =  9,
    SIN   = 10,
    COS   = 11,
    JMP   = 12,
    JE    = 13,
    JNE   = 14,
    JA    = 15,
    JAE   = 16,
    JB    = 17,
    JBE   = 18,
    CALL  = 19,
    RET   = 20
};

enum registers {
    AX = 1,
    BX = 2,
    CX = 3,
    DX = 4
};

enum push_types {
    VAL = 1,
    REG = 2,
    RAM = 3
};


//-------------------------------------------------------------
//! PUSH Realisation
//! All types of PUSH
//!
//-------------------------------------------------------------
DEF_CMD(PUSH,
COMMAND(PUSH) {

    int bites = -1;
    assert (&bites);

    char* register_name = (char*) calloc (SIZEOF_REG, sizeof (*register_name));
    assert (register_name);

    fscanf (inputs, " %[ABCDX] %n", register_name, &bites);

    if (bites == -1)
    {
        int value = 0;
        assert (&value);

        fscanf (inputs, "[%d]%n", &value, &bites);

        if (bites == -1)
        {
            fscanf (inputs, "%d%n", &value, &bites);

            IS_IT_GOOD_COMMAND

            else {
                heap[(*index)] = PUSH;
                (*index)++;
                heap[(*index)] = VAL;
                (*index)++;
                heap[(*index)] = value;
                (*index)++;
            }
        }
        else
        {
            heap[(*index)] = PUSH;
            (*index)++;
            heap[(*index)] = RAM;
            (*index)++;
            heap[(*index)] = value;
            (*index)++;
        }
    }
    else
    {
        heap[(*index)] = PUSH;
        (*index)++;
        heap[(*index)] = REG;
        (*index)++;
        heap[(*index)] = tell_register (register_name);
        (*index)++;
    }

    free (register_name);
}
else,
        case PUSH:
            i++;

                switch (heap[i]) {
                    case VAL:
                        cpu.stak.Push (heap[i + 1]);

                        break;
                    case REG:
                        switch (heap[i + 1]) {

                            REGISTER_PUSH(AX, cpu.ax)
                            REGISTER_PUSH(BX, cpu.bx)
                            REGISTER_PUSH(CX, cpu.cx)
                            REGISTER_PUSH(DX, cpu.dx)
                            UNKNOWN_REGISTER
                        }

                        break;
                    case RAM:
                        if (heap[i + 1] >= RAM_SIZE)
                        {
                            printf ("WRONG ADDRESS OF RAM [%d]", heap[i + 1]);
                            assert (0);
                        }
                        else
                            cpu.stak.Push (cpu.ram[heap[i + 1]]);
                }

                i++;
                break;)



//-------------------------------------------------------------
//! POP Realisation
//! All types of POP
//!
//-------------------------------------------------------------
DEF_CMD(POP,
COMMAND(POP) {
    int bites = -1;
    assert (&bites);

    char* register_name = (char*) calloc (SIZEOF_REG, sizeof (*register_name));
    assert (register_name);

    fscanf (inputs, " %[ABCDX] %n", register_name, &bites);

    if (bites == -1)
    {
        int value = 0;
        assert (&value);

        fscanf (inputs, "[%d]%n", &value, &bites);

        IS_IT_GOOD_COMMAND
        else {
            heap[(*index)] = POP;
            (*index)++;
            heap[(*index)] = RAM;
            (*index)++;
            heap[(*index)] = value;
            (*index)++;
        }
    }
    else
    {
        heap[(*index)] = POP;
        (*index)++;
        heap[(*index)] = REG;
        (*index)++;
        heap[(*index)] = tell_register (register_name);
        (*index)++;
    }

    free (register_name);
}
else,
        case POP:
            i++;
                IS_STACK_EMPTY;
                switch (heap[i])
                {
                    case REG:
                    {
                        switch (heap[i + 1]){

                            REGISTER_POP(AX, cpu.ax)
                            REGISTER_POP(BX, cpu.bx)
                            REGISTER_POP(CX, cpu.cx)
                            REGISTER_POP(DX, cpu.dx)
                            UNKNOWN_REGISTER
                        }
                        break;
                    }
                    case RAM:
                    {
                        if (heap[i + 1] >= RAM_SIZE)
                        {
                            printf ("WRONG ADDRESS OF RAM [%d]", heap[i + 1]);
                            assert (0);
                        }
                        else
                            cpu.ram[heap[i + 1]] = cpu.stak.Pop ();
                    }
                }
                i++;

                break;)

DEF_CMD(IN, COMMON_COMMAND(IN),
        case IN: {
            Stack_elem val = 0;
            assert(&val);
            printf("enter the value:\n");
            scanf("%lf", &val);
            cpu.stak.Push(val);
        }
            break;)

DEF_CMD(OUT,COMMON_COMMAND(OUT),
        case OUT: {
            IS_STACK_EMPTY
            printf("%f", cpu.stak.Pop());
        }
            break;)

DEF_CMD(ADD, COMMON_COMMAND(ADD),USUAL_OPERATION(ADD, +))
DEF_CMD(SUB, COMMON_COMMAND(SUB),USUAL_OPERATION(SUB, -))
DEF_CMD(MUL, COMMON_COMMAND(MUL),USUAL_OPERATION(MUL, *))
DEF_CMD(DIV, COMMON_COMMAND(DIV),USUAL_OPERATION(DIV, /))

DEF_CMD(SQRT, COMMON_COMMAND(SQRT),TRICKY_OPERATION(SQRT, sqrt))
DEF_CMD(SIN, COMMON_COMMAND(SIN),TRICKY_OPERATION(SIN, sin))
DEF_CMD(COS, COMMON_COMMAND(COS),TRICKY_OPERATION(COS, cos))


DEF_CMD(JMP, JUMP_COMMAND(JMP),
        case JMP:
        {
            IS_GOOD_JUMPING
            i = heap[i + 1] - 1;
        }
                break;)

DEF_CMD(JE,JUMP_COMMAND(JE),JUMP_IF_CONDITION(JE, abs(x1 - x2) < EPSILON))
DEF_CMD(JNE,JUMP_COMMAND(JNE),JUMP_IF_CONDITION(JNE,!(abs(x1 - x2) < EPSILON)))
DEF_CMD(JA,JUMP_COMMAND(JA),JUMP_IF_CONDITION(JA, (x2 > x1) && !(abs(x1 - x2) < EPSILON)))
DEF_CMD(JB,JUMP_COMMAND(JB),JUMP_IF_CONDITION(JB, (x2 < x1) && !(abs (x1 - x2) < EPSILON)))
DEF_CMD(JBE,JUMP_COMMAND(JBE),JUMP_IF_CONDITION(JBE, (x2 < x1) || (abs (x1 - x2) < EPSILON)))
DEF_CMD(JAE,COMMON_COMMAND(JAE),JUMP_IF_CONDITION(JAE,(x2 > x1) || (abs (x1 - x2) < EPSILON)))

DEF_CMD(CALL,JUMP_COMMAND(CALL),
        case CALL:
        {
            IS_GOOD_JUMPING
            cpu.calls.Push(i + 1);
            i = heap[i + 1] - 1;
        }
                break;)

DEF_CMD(RET,COMMON_COMMAND(RET),
        case RET:
        {
            i = (int)cpu.calls.Pop();
        }
                break;)

DEF_CMD(END,COMMON_COMMAND(END), )

DEF_REG(AX, REGISTER(AX))
DEF_REG(BX, REGISTER(BX))
DEF_REG(CX, REGISTER(CX))
DEF_REG(DX, REGISTER(DX))


#undef COMMAND
#undef COMMON_COMMAND
#undef JUMP_COMMAND
#undef JUMP_IF_CONDITION
#undef IS_GOOD_JUMPING
#undef IS_IT_GOOD_COMMAND
#undef IS_STACK_EMPTY
#undef IS_STACK_OK
#undef REGISTER
#undef REGISTER_POP
#undef REGISTER_PUSH
#undef UNKNOWN_REGISTER
#undef TRICKY_OPERATION
#undef USUAL_OPERATION