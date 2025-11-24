#include "st.h"

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
        if(temp1->data<temp2->data){
            return true;
        }
        temp1=temp1->next;
        temp2=temp2->next;
    }
    
    return false;
}

bool stack_less_than_equal(node **stack1,node **stack2){
    return stack_less_than(stack1,stack2) || stack_equal(stack1,stack2);
}

bool stack_greater_than(node **stack1,node **stack2){
    node *temp1=*stack1;
    node *temp2=*stack2;
    while(temp1!=NULL && temp2!=NULL){
        if(temp1->data>temp2->data){
            return true;
        }
        temp1=temp1->next;
        temp2=temp2->next;
    }
    
    return false;
}

bool stack_greater_than_equal(node **stack1,node **stack2){
    return stack_greater_than(stack1,stack2) || stack_equal(stack1,stack2);
}

