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
    printf("=== 測試 int 型態（核心 Stack 操作，不需要比較函數）===\n");
    Stack *int_stack = stack_create();
    int int_val;
    
    // 使用 push_with_print 以便正確顯示資料
    int_val = 10; 
    if (push_with_print(int_stack, &int_val, sizeof(int), print_int) != 0) {
        printf("錯誤：push 失敗\n");
    }
    int_val = 20; push_with_print(int_stack, &int_val, sizeof(int), print_int);
    int_val = 30; push_with_print(int_stack, &int_val, sizeof(int), print_int);
    
    // peek 操作不需要比較函數（現在返回 const void*）
    const int *peek_int = (const int*)peek(int_stack);
    printf("頂部元素: %d\n", peek_int ? *peek_int : -1);
    printf("長度: %zu\n", stack_length(int_stack));  // size_t 使用 %zu
    
    printf("int_stack: ");
    display_stack(int_stack);
    printf("\n");

    printf("=== 測試 float 型態（使用 push_with_print 以便顯示）===\n");
    Stack *float_stack = stack_create();
    float float_val;
    
    // 如果需要顯示功能，使用 push_with_print（現在返回錯誤碼）
    float_val = 3.14f; push_with_print(float_stack, &float_val, sizeof(float), print_float);
    float_val = 2.71f; push_with_print(float_stack, &float_val, sizeof(float), print_float);
    float_val = 1.41f; push_with_print(float_stack, &float_val, sizeof(float), print_float);
    
    printf("float_stack: ");
    display_stack(float_stack);
    
    const float *peek_float = (const float*)peek(float_stack);
    printf("頂部元素: %.2f\n", peek_float ? *peek_float : -1.0f);
    printf("長度: %zu\n\n", stack_length(float_stack));  // size_t 使用 %zu

    printf("=== 測試 char 型態（使用 push_with_print 以便顯示）===\n");
    Stack *char_stack = stack_create();
    char char_val;
    
    char_val = 'A'; push_with_print(char_stack, &char_val, sizeof(char), print_char);
    char_val = 'B'; push_with_print(char_stack, &char_val, sizeof(char), print_char);
    char_val = 'C'; push_with_print(char_stack, &char_val, sizeof(char), print_char);
    
    printf("char_stack: ");
    display_stack(char_stack);
    
    const char *peek_char = (const char*)peek(char_stack);
    printf("頂部元素: %c\n", peek_char ? *peek_char : '?');
    printf("長度: %zu\n\n", stack_length(char_stack));  // size_t 使用 %zu

    printf("=== 測試 struct (Student) 型態（使用 push_with_print 以便顯示）===\n");
    Stack *student_stack = stack_create();
    Student student;
    
    student.id = 1;
    strcpy(student.name, "Alice");
    student.score = 95.5f;
    push_with_print(student_stack, &student, sizeof(Student), print_student);
    
    student.id = 2;
    strcpy(student.name, "Bob");
    student.score = 87.0f;
    push_with_print(student_stack, &student, sizeof(Student), print_student);
    
    student.id = 3;
    strcpy(student.name, "Charlie");
    student.score = 92.3f;
    push_with_print(student_stack, &student, sizeof(Student), print_student);
    
    printf("student_stack: ");
    display_stack(student_stack);
    
    const Student *peek_student = (const Student*)peek(student_stack);
    if (peek_student) {
        printf("頂部元素: ");
        print_student(peek_student, sizeof(Student));
        printf("\n");
    }
    printf("長度: %zu\n\n", stack_length(student_stack));  // size_t 使用 %zu

    printf("=== 測試 stack 比較操作（使用 memcmp，因為沒有設置 compare 函數）===\n");
    Stack *stack1 = stack_create();
    Stack *stack2 = stack_create();
    
    // 使用簡化版本的 push（不需要比較函數，現在返回錯誤碼）
    int_val = 1; push(stack1, &int_val, sizeof(int));
    int_val = 2; push(stack1, &int_val, sizeof(int));
    int_val = 3; push(stack1, &int_val, sizeof(int));
    
    int_val = 1; push(stack2, &int_val, sizeof(int));
    int_val = 2; push(stack2, &int_val, sizeof(int));
    int_val = 3; push(stack2, &int_val, sizeof(int));
    
    // stack_equal 會使用 memcmp 進行位元組比較（因為沒有 compare 函數）
    if (stack_equal(stack1, stack2)) {
        printf("stack1 和 stack2 相等（使用 memcmp 比較）\n");
    } else {
        printf("stack1 和 stack2 不相等\n");
    }
    printf("注意：比較操作對 Stack 來說不是核心功能，通常不需要\n\n");

    printf("=== 測試 push_range（使用 float 陣列，需要 print 函數以便顯示）===\n");
    Stack *range_stack = stack_create();
    float float_arr[] = {1.1f, 2.2f, 3.3f, 4.4f};
    int arr_len = sizeof(float_arr) / sizeof(float_arr[0]);
    
    push_range(range_stack, float_arr, sizeof(float), arr_len, print_float);
    printf("range_stack: ");
    display_stack(range_stack);

    printf("\n=== 測試 multi_push（使用 char，需要 print 函數以便顯示）===\n");
    Stack *multi_stack = stack_create();
    char_val = 'X';
    multi_push(multi_stack, &char_val, sizeof(char), 5, print_char);
    printf("multi_stack (5個'X'): ");
    display_stack(multi_stack);

    printf("\n=== 測試 pop 操作 ===\n");
    printf("pop 前長度: %zu\n", stack_length(int_stack));  // size_t 使用 %zu
    pop(int_stack);
    printf("pop 後: ");
    display_stack(int_stack);
    printf("pop 後長度: %zu\n", stack_length(int_stack));  // size_t 使用 %zu

    // 清理所有 stack
    stack_destroy(int_stack);
    stack_destroy(float_stack);
    stack_destroy(char_stack);
    stack_destroy(student_stack);
    stack_destroy(stack1);
    stack_destroy(stack2);
    stack_destroy(range_stack);
    stack_destroy(multi_stack);

    return 0;
}