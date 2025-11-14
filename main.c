#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100000

//define linked listnode structure
typedef struct Node {
    int data;
    int status;
    struct Node *next;
}node;


enum{
    CALL,
    RESUME
}Status;

node *stack=NULL;

node *create_node(int data){
    node *new_node=(node*)malloc(sizeof(node));

    if (new_node==NULL){
        return NULL;
    }

    new_node->data=data;
    new_node->next=NULL;
    
    return new_node;
}

int insert_node(node **head,int data){
    node *new_node=create_node(data);

    if (!new_node) {
        return -1;
    }

    if (*head==NULL){
        *head=new_node;
        
        return 1;
    }

    new_node->next=*head;
    *head=new_node;

    return 1;
}

int delete_node(node **head){
    node *temp=*head;
    if (temp==NULL){
        return -1;
    }
    *head=(*head)->next;
    free(temp);
    return 1;
}

int is_empty(node **head){
    return (*head==NULL);
}

void push(node **head,int data){
    if (insert_node(head,data)==-1){
        printf("Stack overflow\n");
    }
}

void push_value_status(node **head,int data,int status){
    if (insert_node(head,data)==-1){
        printf("Stack overflow\n");
    }

    (*head)->status=status;
}

int pop(node **head){
    if (is_empty(head)){
        printf("Stack underflow\n");
        return -1;
    }

    delete_node(head);
    return 1;
}

int peek(node **head){
    if (!is_empty(head)){
        return (*head)->data;
    }
    else{
        return -1;
    }
}

void display_stack(node **head){
    node *temp=*head;
    printf("Top->");
    while (temp!=NULL) {
        printf("%d ",temp->data);
        temp=temp->next;
    }
    printf("<-Bottom\n");
    
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

int stack_length(node **head){
    int len=0;
    node *temp=*head;
    while (temp!=NULL) {
        len++;
        temp=temp->next;
    }
    return len;
}



#define insert_push_code(n) push(&stack,n) 
#define pop_code() pop(&stack)

#define push_stack(ss,n,status) push_value_status(&ss,n,status)

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
    printf("Factorial of 15 is %d\n",factorial_stack(15));
}

int main(){


    test_factorial_with_stack();
    
    return 0;
}