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

//define linked listnode structure
typedef struct Node {
    void *data;              // 通用資料指標
    size_t data_size;        // 資料大小（位元組）
    int status;
    compare_func_t compare;  // 比較函數指標（可選，NULL 時使用 memcmp）
                              // 用於 stack_equal、stack_less_than 等比較操作
                              // 不同資料型態（int/float/char/struct）需要不同的比較邏輯
    print_func_t print;      // 顯示函數指標（可選，NULL 時顯示記憶體位址）
                              // 用於 display_stack 函數
                              // 不同資料型態需要不同的顯示格式（%d/%f/%c 等）
    struct Node *next;
}node;

// Function declarations
node *create_node(const void *data, size_t data_size, compare_func_t compare, print_func_t print);
int insert_node(node **head, const void *data, size_t data_size, compare_func_t compare, print_func_t print);
int delete_node(node **head);
int is_empty(node **head);
void push(node **head, const void *data, size_t data_size, compare_func_t compare, print_func_t print);
void multi_push(node **head, const void *data, size_t data_size, int count, compare_func_t compare, print_func_t print);
void push_range(node **head, const void *arr, size_t elem_size, int size, compare_func_t compare, print_func_t print);
void push_value_status(node **head, const void *data, size_t data_size, int status, compare_func_t compare, print_func_t print);
int pop(node **head);
int multi_pop(node **head, int count);
void *peek(node **head);
void display_stack(node **head);
int stack_length(node **head);
void swap_stack(node **head1, node **head2);
bool stack_equal(node **stack1, node **stack2);
bool stack_not_equal(node **stack1, node **stack2);
bool stack_less_than(node **stack1, node **stack2);
bool stack_less_than_equal(node **stack1, node **stack2);
bool stack_greater_than(node **stack1, node **stack2);
bool stack_greater_than_equal(node **stack1, node **stack2);

// 輔助函數：用於常見資料型態的比較和顯示
int compare_int(const void *a, const void *b, size_t size);
int compare_float(const void *a, const void *b, size_t size);
int compare_char(const void *a, const void *b, size_t size);
void print_int(const void *data, size_t size);
void print_float(const void *data, size_t size);
void print_char(const void *data, size_t size);
