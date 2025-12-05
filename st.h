#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

// 比較函數類型定義：返回負數表示 a < b，0 表示 a == b，正數表示 a > b
typedef int (*compare_func_t)(const void *a, const void *b, size_t size);
// 顯示函數類型定義：用於顯示節點資料
typedef void (*print_func_t)(const void *data, size_t size);

// 節點結構（內部使用）
typedef struct Node {
    void *data;              // 通用資料指標
    size_t data_size;        // 資料大小（位元組）
    int status;
    compare_func_t compare;  // 比較函數指標（可選，NULL 時使用 memcmp）
                              // 僅在 stack_equal、stack_less_than 等比較操作時需要
                              // Stack 的核心操作（push/pop/peek）不需要此函數
                              // 不同資料型態（int/float/char/struct）需要不同的比較邏輯
    print_func_t print;      // 顯示函數指標（可選，NULL 時顯示記憶體位址）
                              // 僅在 display_stack 函數時需要
                              // Stack 的核心操作（push/pop/peek）不需要此函數
                              // 不同資料型態需要不同的顯示格式（%d/%f/%c 等）
    struct Node *next;
} Node;

// List 結構（封裝節點）
typedef struct List {
    Node *head;              // 指向第一個節點的指標
} List;

// Stack 結構（基於 List 實現 FILO）
typedef List Stack;

// Stack 初始化與清理
Stack* stack_create(void);
void stack_destroy(Stack *stack);

// 核心 Stack 操作（FILO）- 不需要比較函數
void push(Stack *stack, const void *data, size_t data_size);
void push_with_print(Stack *stack, const void *data, size_t data_size, print_func_t print);
int pop(Stack *stack);
int multi_pop(Stack *stack, int count);
void *peek(Stack *stack);
int is_empty(Stack *stack);
int stack_length(Stack *stack);
void swap_stack(Stack *stack1, Stack *stack2);

// 進階操作 - 需要顯示函數
void multi_push(Stack *stack, const void *data, size_t data_size, int count, print_func_t print);
void push_range(Stack *stack, const void *arr, size_t elem_size, int size, print_func_t print);
void push_value_status(Stack *stack, const void *data, size_t data_size, int status, print_func_t print);
void display_stack(Stack *stack);

// Stack 比較操作 - 需要比較函數（這些操作對 Stack 來說不是核心功能）
// 注意：這些函數需要 stack 中的節點都有 compare 函數，否則使用 memcmp
bool stack_equal(Stack *stack1, Stack *stack2);
bool stack_not_equal(Stack *stack1, Stack *stack2);
bool stack_less_than(Stack *stack1, Stack *stack2);
bool stack_less_than_equal(Stack *stack1, Stack *stack2);
bool stack_greater_than(Stack *stack1, Stack *stack2);
bool stack_greater_than_equal(Stack *stack1, Stack *stack2);

// 內部函數（通常不需要直接調用）
Node *create_node(const void *data, size_t data_size, compare_func_t compare, print_func_t print);
int insert_node(Node **head, const void *data, size_t data_size, compare_func_t compare, print_func_t print);
int delete_node(Node **head);

// 輔助函數：用於常見資料型態的比較和顯示
int compare_int(const void *a, const void *b, size_t size);
int compare_float(const void *a, const void *b, size_t size);
int compare_char(const void *a, const void *b, size_t size);
void print_int(const void *data, size_t size);
void print_float(const void *data, size_t size);
void print_char(const void *data, size_t size);
