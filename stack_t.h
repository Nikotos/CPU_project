///STACK
#pragma once

#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <iostream>
#include <assert.h>

typedef double Stack_elem;

const int Min_stack_size = 1024;
const int Canary_1 = 1234567, Canary_2 = 7654321;
const Stack_elem Body_canary_1 = 123456789, Body_canary_2 = 987654321;;
const int Start_value = 11;
const double Epsilon = 0.000001;

class Stack_t {

    private:
        int canaryleft;

        Stack_elem* body;
        int count_st;       // last index
        int size_st;    // the size of stack
        int _hash_val;
        int _hash_body;

        int canaryright;

        int Hash_val();
        int Hash_body();
        void dump(const int value, FILE* dump_file);
        void dump(const double value, FILE* dump_file);
        void dump(const void* value, FILE* dump_file);
        void Double_size();
    public:
        Stack_t();
        ~Stack_t();
        bool All_Correct();
        void Dump();
        void Push(Stack_elem value);
        Stack_elem Pop();
        Stack_elem get();
        int Size();        // number of elements in stack
        bool Empty();
};
