#pragma once
#include "st.h"

#define insert_push_code(n) push(&stack,n) 
#define pop_code() pop(&stack)
#define push_stack(ss,n,status) push_value_status(&ss,n,status)

typedef enum{
    CALL,
    RESUME
}Status;

extern node *stack;


int factorial(int n);
int factorial_stack(int n);
int simulate_stack();
void display_stack_status(node **head);
void test_factorial_with_stack();
