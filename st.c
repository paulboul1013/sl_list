#include "st.h"

node *create_node(const void *data, size_t data_size, compare_func_t compare, print_func_t print){
    node *new_node=(node*)malloc(sizeof(node));

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

int insert_node(node **head, const void *data, size_t data_size, compare_func_t compare, print_func_t print){
    node *new_node=create_node(data, data_size, compare, print);

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
    // 釋放資料記憶體
    if (temp->data != NULL) {
        free(temp->data);
    }
    free(temp);
    return 1;
}

int is_empty(node **head){
    return (*head==NULL);
}

void push(node **head, const void *data, size_t data_size, compare_func_t compare, print_func_t print){
    if (insert_node(head, data, data_size, compare, print)==-1){
        printf("Stack overflow\n");
    }
}

void multi_push(node **head, const void *data, size_t data_size, int count, compare_func_t compare, print_func_t print){
    for(int i=0;i<count;i++){
        push(head, data, data_size, compare, print);
    }
}

void push_range(node **head, const void *arr, size_t elem_size, int size, compare_func_t compare, print_func_t print){
    const char *arr_ptr = (const char *)arr;
    for(int i=0;i<size;i++){
        push(head, arr_ptr + i * elem_size, elem_size, compare, print);
    }
}

void push_value_status(node **head, const void *data, size_t data_size, int status, compare_func_t compare, print_func_t print){
    if (insert_node(head, data, data_size, compare, print)==-1){
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

void *peek(node **head){
    if (!is_empty(head)){
        return (*head)->data;
    }
    else{
        return NULL;
    }
}

void display_stack(node **head){
    node *temp=*head;
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

bool stack_equal(node **stack1, node **stack2){
    node *temp1=*stack1;
    node *temp2=*stack2;
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

bool stack_not_equal(node **stack1,node **stack2){
    return !stack_equal(stack1,stack2);
}

bool stack_less_than(node **stack1, node **stack2){
    node *temp1=*stack1;
    node *temp2=*stack2;
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

bool stack_less_than_equal(node **stack1,node **stack2){
    return stack_less_than(stack1,stack2) || stack_equal(stack1,stack2);
}

bool stack_greater_than(node **stack1, node **stack2){
    node *temp1=*stack1;
    node *temp2=*stack2;
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

bool stack_greater_than_equal(node **stack1,node **stack2){
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

