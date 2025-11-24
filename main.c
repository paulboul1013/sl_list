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
    push(&stack2,1);
    push(&stack2,2);
    push(&stack2,3);
    push(&stack2,4);
    push(&stack2,5);
    push(&stack2,6);
    push(&stack2,7);
    push(&stack2,8);
    push(&stack2,9);

    display_stack(&stack2);
    node *stack3=stack2;
    display_stack(&stack3);
    
    printf("stack2 is %d\n",peek(&stack2));
    printf("stack3 is %d\n",peek(&stack3));

    if (is_empty(&stack2)){
        printf("stack2 is empty\n");
    }
    else{
        printf("stack2 is not empty\n");
    }


    printf("stack2 length is %d\n",stack_length(&stack2));
    multi_push(&stack2,10,5);
    display_stack(&stack2);

    int arr[]={1,2,3};
    int arr_len=sizeof(arr)/sizeof(arr[0]);
    push_range(&stack2,arr,arr_len);
    display_stack(&stack2);

    multi_pop(&stack2,14);
    display_stack(&stack2);

    stack3=NULL;
    push(&stack3,4);
    push(&stack3,5);
    push(&stack3,6);
    display_stack(&stack3);

    swap_stack(&stack2,&stack3);
    display_stack(&stack2);
    display_stack(&stack3);

    node *stack4=NULL;
    push(&stack4,1);
    push(&stack4,2);
    push(&stack4,3);
    node *stack5=NULL;
    push(&stack5,1);
    push(&stack5,2);
    push(&stack5,3);
    push(&stack5,4);


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