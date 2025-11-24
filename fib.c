#include "fib.h"

node *stack=NULL;


int factorial(int n){

    if (n<=1){
        insert_push_code(1);
        return 1;
    }
    insert_push_code(n);
    return n*factorial(n-1);
}


int factorial_stack(int n){
    int temp=n;
    node *s=NULL;
    int result=0;
    push_stack(s,temp,CALL);


    while(!is_empty(&s)){
        
        display_stack_status(&s);
        int data=peek(&s);
        int action=s->status;
        pop(&s);
        

        if (action==CALL){
            temp=data; //factorial () args
            if (temp==1){
                result=1;
                printf("Result: %d \t",result);
            }
            else{
                push_stack(s,temp,RESUME);
                push_stack(s,temp-1,CALL);
            }

        }

        else if (action==RESUME){
            temp=data;//local variable
            result*=temp;
            printf("Result: %d \t",result);
        }
    }

    return result;
}


int simulate_stack(){
    display_stack(&stack);
    int sum=1;
    int len=stack_length(&stack);
    for(int i=0;i<len;i++){
        sum*=peek(&stack);
        pop_code();
    }
    return sum;
}

void test_factorial_with_stack() {
    
    //normal recursion version
    // printf("normal recursion version Factorial of 15 is %d\n",factorial(15));
    
    //global stack version
    // printf("Sum of factorial is %d\n",simulate_stack());

    //local stack version
    // show call and resume status like real stack save local variable and results
    // printf("Factorial of 15 is %d\n",factorial_stack(5));


    //using pointer to function
    int (*p)(int)=&factorial_stack;
    printf("Factorial of 5 is %d\n",(*p)(5));
    // printf("Factorial of 5 address is %p\n",p);
}


void display_stack_status(node **head){
    node *temp=*head;
    printf("Top->");
    while (temp!=NULL) {
        printf("%d(%s) ",temp->data,temp->status==CALL?"CALL":"RESUME");
        temp=temp->next;
    }
    printf("<-Bottom\n");
}