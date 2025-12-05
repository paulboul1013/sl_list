#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

#include "st.h"

// 定義一個測試用的結構體
typedef struct {
    int id;
    char name[20];
    float score;
} Student;

// Student 結構體的比較函數（根據 id 比較）
int compare_student(const void *a, const void *b, size_t size) {
    (void)size; // 未使用的參數
    const Student *student_a = (const Student *)a;
    const Student *student_b = (const Student *)b;
    if (student_a->id < student_b->id) return -1;
    if (student_a->id > student_b->id) return 1;
    return 0;
}

// Student 結構體的顯示函數
void print_student(const void *data, size_t size) {
    (void)size; // 未使用的參數
    const Student *student = (const Student *)data;
    printf("Student{id:%d,name:%s,score:%.2f}", student->id, student->name, student->score);
}

int main() {
    printf("=== 測試 int 型態 ===\n");
    node *int_stack = NULL;
    int int_val;
    
    int_val = 10; push(&int_stack, &int_val, sizeof(int), compare_int, print_int);
    int_val = 20; push(&int_stack, &int_val, sizeof(int), compare_int, print_int);
    int_val = 30; push(&int_stack, &int_val, sizeof(int), compare_int, print_int);
    
    printf("int_stack: ");
    display_stack(&int_stack);
    
    int *peek_int = (int*)peek(&int_stack);
    printf("頂部元素: %d\n", peek_int ? *peek_int : -1);
    printf("長度: %d\n\n", stack_length(&int_stack));

    printf("=== 測試 float 型態 ===\n");
    node *float_stack = NULL;
    float float_val;
    
    float_val = 3.14f; push(&float_stack, &float_val, sizeof(float), compare_float, print_float);
    float_val = 2.71f; push(&float_stack, &float_val, sizeof(float), compare_float, print_float);
    float_val = 1.41f; push(&float_stack, &float_val, sizeof(float), compare_float, print_float);
    
    printf("float_stack: ");
    display_stack(&float_stack);
    
    float *peek_float = (float*)peek(&float_stack);
    printf("頂部元素: %.2f\n", peek_float ? *peek_float : -1.0f);
    printf("長度: %d\n\n", stack_length(&float_stack));

    printf("=== 測試 char 型態 ===\n");
    node *char_stack = NULL;
    char char_val;
    
    char_val = 'A'; push(&char_stack, &char_val, sizeof(char), compare_char, print_char);
    char_val = 'B'; push(&char_stack, &char_val, sizeof(char), compare_char, print_char);
    char_val = 'C'; push(&char_stack, &char_val, sizeof(char), compare_char, print_char);
    
    printf("char_stack: ");
    display_stack(&char_stack);
    
    char *peek_char = (char*)peek(&char_stack);
    printf("頂部元素: %c\n", peek_char ? *peek_char : '?');
    printf("長度: %d\n\n", stack_length(&char_stack));

    printf("=== 測試 struct (Student) 型態 ===\n");
    node *student_stack = NULL;
    Student student;
    
    student.id = 1;
    strcpy(student.name, "Alice");
    student.score = 95.5f;
    push(&student_stack, &student, sizeof(Student), compare_student, print_student);
    
    student.id = 2;
    strcpy(student.name, "Bob");
    student.score = 87.0f;
    push(&student_stack, &student, sizeof(Student), compare_student, print_student);
    
    student.id = 3;
    strcpy(student.name, "Charlie");
    student.score = 92.3f;
    push(&student_stack, &student, sizeof(Student), compare_student, print_student);
    
    printf("student_stack: ");
    display_stack(&student_stack);
    
    Student *peek_student = (Student*)peek(&student_stack);
    if (peek_student) {
        printf("頂部元素: ");
        print_student(peek_student, sizeof(Student));
        printf("\n");
    }
    printf("長度: %d\n\n", stack_length(&student_stack));

    printf("=== 測試 stack 比較操作（使用 int） ===\n");
    node *stack1 = NULL;
    node *stack2 = NULL;
    
    int_val = 1; push(&stack1, &int_val, sizeof(int), compare_int, print_int);
    int_val = 2; push(&stack1, &int_val, sizeof(int), compare_int, print_int);
    int_val = 3; push(&stack1, &int_val, sizeof(int), compare_int, print_int);
    
    int_val = 1; push(&stack2, &int_val, sizeof(int), compare_int, print_int);
    int_val = 2; push(&stack2, &int_val, sizeof(int), compare_int, print_int);
    int_val = 3; push(&stack2, &int_val, sizeof(int), compare_int, print_int);
    
    printf("stack1: ");
    display_stack(&stack1);
    printf("stack2: ");
    display_stack(&stack2);
    
    if (stack_equal(&stack1, &stack2)) {
        printf("stack1 和 stack2 相等\n");
    } else {
        printf("stack1 和 stack2 不相等\n");
    }

    printf("\n=== 測試 push_range（使用 float 陣列） ===\n");
    node *range_stack = NULL;
    float float_arr[] = {1.1f, 2.2f, 3.3f, 4.4f};
    int arr_len = sizeof(float_arr) / sizeof(float_arr[0]);
    
    push_range(&range_stack, float_arr, sizeof(float), arr_len, compare_float, print_float);
    printf("range_stack: ");
    display_stack(&range_stack);

    printf("\n=== 測試 multi_push（使用 char） ===\n");
    node *multi_stack = NULL;
    char_val = 'X';
    multi_push(&multi_stack, &char_val, sizeof(char), 5, compare_char, print_char);
    printf("multi_stack (5個'X'): ");
    display_stack(&multi_stack);

    printf("\n=== 測試 pop 操作 ===\n");
    printf("pop 前長度: %d\n", stack_length(&int_stack));
    pop(&int_stack);
    printf("pop 後: ");
    display_stack(&int_stack);
    printf("pop 後長度: %d\n", stack_length(&int_stack));

    return 0;
}