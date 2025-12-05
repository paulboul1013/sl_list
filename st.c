#include "st.h"

// Stack 初始化與清理
Stack* stack_create(void) {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        return NULL;
    }
    stack->head = NULL;
    return stack;
}

void stack_destroy(Stack *stack) {
    if (stack == NULL) {
        return;
    }
    // 釋放所有節點
    while (stack->head != NULL) {
        Node *temp = stack->head;
        stack->head = stack->head->next;
        if (temp->data != NULL) {
            free(temp->data);
        }
        free(temp);
    }
    free(stack);
}

Node *create_node(const void *data, size_t data_size, compare_func_t compare, print_func_t print){
    Node *new_node=(Node*)malloc(sizeof(Node));

    if (new_node==NULL){
        return NULL;
    }

    // 分配記憶體並複製資料
    new_node->data = malloc(data_size);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    memcpy(new_node->data, data, data_size);
    
    new_node->data_size = data_size;
    new_node->compare = compare;
    new_node->print = print;
    new_node->status = 0;
    new_node->next=NULL;
    
    return new_node;
}

int insert_node(Node **head, const void *data, size_t data_size, compare_func_t compare, print_func_t print){
    Node *new_node=create_node(data, data_size, compare, print);

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

int delete_node(Node **head){
    Node *temp=*head;
    if (temp==NULL){
        return -1;
    }
    *head=(*head)->next;
    // 釋放資料記憶體
    if (temp->data != NULL) {
        free(temp->data);
    }
    free(temp);
    return 1;
}

int is_empty(Stack *stack){
    return (stack == NULL || stack->head == NULL);
}

// 簡化版本：核心 Stack 操作，不需要比較和顯示函數
void push(Stack *stack, const void *data, size_t data_size){
    if (stack == NULL) {
        printf("Stack is NULL\n");
        return;
    }
    if (insert_node(&(stack->head), data, data_size, NULL, NULL)==-1){
        printf("Stack overflow\n");
    }
}

// 帶顯示函數的版本（用於需要顯示的情況）
void push_with_print(Stack *stack, const void *data, size_t data_size, print_func_t print){
    if (stack == NULL) {
        printf("Stack is NULL\n");
        return;
    }
    if (insert_node(&(stack->head), data, data_size, NULL, print)==-1){
        printf("Stack overflow\n");
    }
}

void multi_push(Stack *stack, const void *data, size_t data_size, int count, print_func_t print){
    for(int i=0;i<count;i++){
        push_with_print(stack, data, data_size, print);
    }
}

void push_range(Stack *stack, const void *arr, size_t elem_size, int size, print_func_t print){
    const char *arr_ptr = (const char *)arr;
    for(int i=0;i<size;i++){
        push_with_print(stack, arr_ptr + i * elem_size, elem_size, print);
    }
}

void push_value_status(Stack *stack, const void *data, size_t data_size, int status, print_func_t print){
    if (stack == NULL) {
        printf("Stack is NULL\n");
        return;
    }
    if (insert_node(&(stack->head), data, data_size, NULL, print)==-1){
        printf("Stack overflow\n");
    }

    stack->head->status=status;
}

int pop(Stack *stack){
    if (stack == NULL || is_empty(stack)){
        printf("Stack underflow\n");
        return -1;
    }

    delete_node(&(stack->head));
    return 1;
}

int multi_pop(Stack *stack, int count){
    if (stack == NULL || is_empty(stack)){
        printf("Stack underflow\n");
        return -1;
    }

    for(int i=0;i<count;i++){
        pop(stack);
    }

    return 1;
}

void *peek(Stack *stack){
    if (stack != NULL && !is_empty(stack)){
        return stack->head->data;
    }
    else{
        return NULL;
    }
}

void display_stack(Stack *stack){
    if (stack == NULL) {
        printf("Stack is NULL\n");
        return;
    }
    Node *temp=stack->head;
    printf("Top->");
    while (temp!=NULL) {
        if (temp->print != NULL) {
            temp->print(temp->data, temp->data_size);
            printf(" ");
        } else {
            // 如果沒有提供顯示函數，使用預設方式（顯示記憶體位址）
            printf("[%p] ", temp->data);
        }
        temp=temp->next;
    }
    printf("<-Bottom\n");
    
}



int stack_length(Stack *stack){
    if (stack == NULL) {
        return 0;
    }
    int len=0;
    Node *temp=stack->head;
    while (temp!=NULL) {
        len++;
        temp=temp->next;
    }
    return len;
}

void swap_stack(Stack *stack1, Stack *stack2){
    if (stack1 == NULL || stack2 == NULL) {
        return;
    }
    Node *temp=stack1->head;
    stack1->head=stack2->head;
    stack2->head=temp;
}

bool stack_equal(Stack *stack1, Stack *stack2){
    if (stack1 == NULL || stack2 == NULL) {
        return false;
    }
    Node *temp1=stack1->head;
    Node *temp2=stack2->head;
    while(temp1!=NULL && temp2!=NULL){
        // 如果兩個節點都有比較函數，使用比較函數
        if(temp1->compare != NULL && temp2->compare != NULL){
            if(temp1->compare(temp1->data, temp2->data, temp1->data_size) != 0){
                return false;
            }
        } else {
            // 否則使用 memcmp 進行位元組比較
            if(memcmp(temp1->data, temp2->data, 
                     temp1->data_size < temp2->data_size ? temp1->data_size : temp2->data_size) != 0){
                return false;
            }
        }
        temp1=temp1->next;
        temp2=temp2->next;
    }

    return (temp1==NULL && temp2==NULL);
}

bool stack_not_equal(Stack *stack1, Stack *stack2){
    return !stack_equal(stack1,stack2);
}

bool stack_less_than(Stack *stack1, Stack *stack2){
    if (stack1 == NULL || stack2 == NULL) {
        return false;
    }
    Node *temp1=stack1->head;
    Node *temp2=stack2->head;
    while(temp1!=NULL && temp2!=NULL){
        int cmp_result;
        if(temp1->compare != NULL && temp2->compare != NULL){
            cmp_result = temp1->compare(temp1->data, temp2->data, temp1->data_size);
        } else {
            // 使用 memcmp 進行比較
            cmp_result = memcmp(temp1->data, temp2->data, 
                               temp1->data_size < temp2->data_size ? temp1->data_size : temp2->data_size);
        }
        if(cmp_result < 0){
            return true;
        }
        temp1=temp1->next;
        temp2=temp2->next;
    }
    
    return false;
}

bool stack_less_than_equal(Stack *stack1, Stack *stack2){
    return stack_less_than(stack1,stack2) || stack_equal(stack1,stack2);
}

bool stack_greater_than(Stack *stack1, Stack *stack2){
    if (stack1 == NULL || stack2 == NULL) {
        return false;
    }
    Node *temp1=stack1->head;
    Node *temp2=stack2->head;
    while(temp1!=NULL && temp2!=NULL){
        int cmp_result;
        if(temp1->compare != NULL && temp2->compare != NULL){
            cmp_result = temp1->compare(temp1->data, temp2->data, temp1->data_size);
        } else {
            // 使用 memcmp 進行比較
            cmp_result = memcmp(temp1->data, temp2->data, 
                               temp1->data_size < temp2->data_size ? temp1->data_size : temp2->data_size);
        }
        if(cmp_result > 0){
            return true;
        }
        temp1=temp1->next;
        temp2=temp2->next;
    }
    
    return false;
}

bool stack_greater_than_equal(Stack *stack1, Stack *stack2){
    return stack_greater_than(stack1,stack2) || stack_equal(stack1,stack2);
}

// 輔助函數實現：常見資料型態的比較和顯示

int compare_int(const void *a, const void *b, size_t size){
    (void)size; // 未使用的參數
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

int compare_float(const void *a, const void *b, size_t size){
    (void)size; // 未使用的參數
    float float_a = *(const float*)a;
    float float_b = *(const float*)b;
    if (float_a < float_b) return -1;
    if (float_a > float_b) return 1;
    return 0;
}

int compare_char(const void *a, const void *b, size_t size){
    (void)size; // 未使用的參數
    char char_a = *(const char*)a;
    char char_b = *(const char*)b;
    if (char_a < char_b) return -1;
    if (char_a > char_b) return 1;
    return 0;
}

void print_int(const void *data, size_t size){
    (void)size; // 未使用的參數
    printf("%d", *(const int*)data);
}

void print_float(const void *data, size_t size){
    (void)size; // 未使用的參數
    printf("%f", *(const float*)data);
}

void print_char(const void *data, size_t size){
    (void)size; // 未使用的參數
    printf("%c", *(const char*)data);
}

