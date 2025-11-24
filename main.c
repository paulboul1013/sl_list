#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

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

void multi_push(node **head,int data,int count){
    for(int i=0;i<count;i++){
        push(head,data);
    }
}

void push_range(node **head,int *arr,int size){
    for(int i=0;i<size;i++){
        push(head,arr[i]);
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

int multi_pop(node **head,int count){
    if (is_empty(head)){
        printf("Stack underflow\n");
        return -1;
    }

    for(int i=0;i<count;i++){
        pop(head);
    }

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

void swap_stack(node **head1,node **head2){
    node *temp=*head1;
    *head1=*head2;
    *head2=temp;
}

bool stack_equal(node **stack1,node **stack2){
    node *temp1=*stack1;
    node *temp2=*stack2;
    while(temp1!=NULL && temp2!=NULL){
        if(temp1->data!=temp2->data){
            return false;
        }
        temp1=temp1->next;
        temp2=temp2->next;
    }

    return (temp1==NULL && temp2==NULL);
}

bool stack_not_equal(node **stack1,node **stack2){
    return !stack_equal(stack1,stack2);
}

bool stack_less_than(node **stack1,node **stack2){
    node *temp1=*stack1;
    node *temp2=*stack2;
    while(temp1!=NULL && temp2!=NULL){
        if(temp1->data>temp2->data){
            return false;
        }
        temp1=temp1->next;
        temp2=temp2->next;
    }
    return (temp1==NULL && temp2==NULL);
}

bool stack_less_than_or_equal(node **stack1,node **stack2){
    return stack_less_than(stack1,stack2) || stack_equal(stack1,stack2);
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
    // printf("Factorial of 15 is %d\n",factorial_stack(5));


    //using pointer to function
    int (*p)(int)=&factorial_stack;
    printf("Factorial of 5 is %d\n",(*p)(5));
    // printf("Factorial of 5 address is %p\n",p);
}

static int precedence(int op){
	if (op=='+' || op=='-') return 1;
	if (op=='*' || op=='/') return 2;
	return 0;
}

static int apply_operation(int left,int right,int op){
	switch(op){
		case '+': return left+right;
		case '-': return left-right;
		case '*': return left*right;
		case '/': return left/right;
		default: return 0;
	}
}

void test_expression_evaluation() {
	node *stack_operation=NULL;
	char *expression="1*2*3+4*5";
	for (size_t i=0;i<strlen(expression);i++){
		char ch=expression[i];
		if (ch>='0' && ch<='9') {
			push(&stack,ch-'0');
		}
		else if (ch=='+' || ch=='-' || ch=='*' || ch=='/') {
			while(!is_empty(&stack_operation) && precedence(peek(&stack_operation))>=precedence(ch)){
				int op=peek(&stack_operation); pop(&stack_operation);
				int right=peek(&stack); pop(&stack);
				int left=peek(&stack); pop(&stack);
				int res=apply_operation(left,right,op);
				push(&stack,res);
			}
			push(&stack_operation,ch);
		}
	}
	while(!is_empty(&stack_operation)){
		int op=peek(&stack_operation); pop(&stack_operation);
		int right=peek(&stack); pop(&stack);
		int left=peek(&stack); pop(&stack);
		int res=apply_operation(left,right,op);
		push(&stack,res);
	}
	printf("Result: %d\n",peek(&stack));
	display_stack(&stack);
}


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



    if (stack_equal(&stack4,&stack5)){
        printf("stack4 and stack5 are equal\n");
    }
    else{
        printf("stack4 and stack5 are not equal\n");
    }


    if (stack_not_equal(&stack3,&stack2)){
        printf("stack3 and stack2 are not equal\n");
    }
    else{
        printf("stack3 and stack2 are equal\n");
    }


    display_stack(&stack2);
    display_stack(&stack3);
    if (stack_less_than(&stack2,&stack3)){
        printf("stack2 is less than stack3\n");
    }
    else{
        printf("stack2 is not less than stack3\n");
    }

    if (stack_less_than_or_equal(&stack4,&stack5)){
        printf("stack4 is less than or equal to stack5\n");
    }
    else{
        printf("stack4 is not less than or equal to stack5\n");
    }


    return 0;
}