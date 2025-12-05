#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

#include "fib.h"
#include "st.h"
#include "eval.h"



int main(){



    node *stack2=NULL;
    int val;
    val = 1; push(&stack2, &val, sizeof(int), compare_int, print_int);
    val = 2; push(&stack2, &val, sizeof(int), compare_int, print_int);
    val = 3; push(&stack2, &val, sizeof(int), compare_int, print_int);
    val = 4; push(&stack2, &val, sizeof(int), compare_int, print_int);
    val = 5; push(&stack2, &val, sizeof(int), compare_int, print_int);
    val = 6; push(&stack2, &val, sizeof(int), compare_int, print_int);
    val = 7; push(&stack2, &val, sizeof(int), compare_int, print_int);
    val = 8; push(&stack2, &val, sizeof(int), compare_int, print_int);
    val = 9; push(&stack2, &val, sizeof(int), compare_int, print_int);

    display_stack(&stack2);
    node *stack3=stack2;
    display_stack(&stack3);
    
    int *peek_val = (int*)peek(&stack2);
    printf("stack2 is %d\n", peek_val ? *peek_val : -1);
    peek_val = (int*)peek(&stack3);
    printf("stack3 is %d\n", peek_val ? *peek_val : -1);

    if (is_empty(&stack2)){
        printf("stack2 is empty\n");
    }
    else{
        printf("stack2 is not empty\n");
    }


    printf("stack2 length is %d\n",stack_length(&stack2));
    val = 10; multi_push(&stack2, &val, sizeof(int), 5, compare_int, print_int);
    display_stack(&stack2);

    int arr[]={1,2,3};
    int arr_len=sizeof(arr)/sizeof(arr[0]);
    push_range(&stack2, arr, sizeof(int), arr_len, compare_int, print_int);
    display_stack(&stack2);

    multi_pop(&stack2,14);
    display_stack(&stack2);

    stack3=NULL;
    val = 4; push(&stack3, &val, sizeof(int), compare_int, print_int);
    val = 5; push(&stack3, &val, sizeof(int), compare_int, print_int);
    val = 6; push(&stack3, &val, sizeof(int), compare_int, print_int);
    display_stack(&stack3);

    swap_stack(&stack2,&stack3);
    display_stack(&stack2);
    display_stack(&stack3);

    node *stack4=NULL;
    val = 1; push(&stack4, &val, sizeof(int), compare_int, print_int);
    val = 2; push(&stack4, &val, sizeof(int), compare_int, print_int);
    val = 3; push(&stack4, &val, sizeof(int), compare_int, print_int);
    node *stack5=NULL;
    val = 1; push(&stack5, &val, sizeof(int), compare_int, print_int);
    val = 2; push(&stack5, &val, sizeof(int), compare_int, print_int);
    val = 3; push(&stack5, &val, sizeof(int), compare_int, print_int);
    val = 4; push(&stack5, &val, sizeof(int), compare_int, print_int);


    if (stack_greater_than_equal(&stack5,&stack4)){
        printf("stack5 is greater than or equal to stack4\n");
    }
    else{
        printf("stack5 is not greater than or equal to stack4\n");
    }

    
    if (stack_greater_than(&stack5,&stack4)){
        printf("stack5 is greater than stack4\n");
    }
    else{
        printf("stack5 is not greater than stack4\n");
    }

        
    if (stack_less_than(&stack5,&stack4)){
        printf("stack5 is less than stack4\n");
    }
    else{
        printf("stack5 is not less than stack4\n");
    }

        
    if (stack_less_than_equal(&stack5,&stack4)){
        printf("stack5 is less than or equal to stack4\n");
    }
    else{
        printf("stack5 is not less than or equal to stack4\n");
    }


    return 0;
}