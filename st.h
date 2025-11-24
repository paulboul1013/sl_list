#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//define linked listnode structure
typedef struct Node {
    int data;
    int status;
    struct Node *next;
}node;

// Function declarations
node *create_node(int data);
int insert_node(node **head,int data);
int delete_node(node **head);
int is_empty(node **head);
void push(node **head,int data);
void multi_push(node **head,int data,int count);
void push_range(node **head,int *arr,int size);
void push_value_status(node **head,int data,int status);
int pop(node **head);
int multi_pop(node **head,int count);
int peek(node **head);
void display_stack(node **head);
int stack_length(node **head);
void swap_stack(node **head1,node **head2);
bool stack_equal(node **stack1,node **stack2);
bool stack_not_equal(node **stack1,node **stack2);
bool stack_less_than(node **stack1,node **stack2);
bool stack_less_than_equal(node **stack1,node **stack2);
bool stack_greater_than(node **stack1,node **stack2);
bool stack_greater_than_equal(node **stack1,node **stack2);
