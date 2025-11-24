#include "eval.h"

int precedence(int op){
	if (op=='+' || op=='-') return 1;
	if (op=='*' || op=='/') return 2;
	return 0;
}

int apply_operation(int left,int right,int op){
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
	node *stack_values=NULL;
	char *expression="1*2*3+4*5";
	for (size_t i=0;i<strlen(expression);i++){
		char ch=expression[i];
		if (ch>='0' && ch<='9') {
			push(&stack_values,ch-'0');
		}
		else if (ch=='+' || ch=='-' || ch=='*' || ch=='/') {
			while(!is_empty(&stack_operation) && precedence(peek(&stack_operation))>=precedence(ch)){
				int op=peek(&stack_operation); pop(&stack_operation);
				int right=peek(&stack_values); pop(&stack_values);
				int left=peek(&stack_values); pop(&stack_values);
				int res=apply_operation(left,right,op);
				push(&stack_values,res);
			}
			push(&stack_operation,ch);
		}
	}
	while(!is_empty(&stack_operation)){
		int op=peek(&stack_operation); pop(&stack_operation);
		int right=peek(&stack_values); pop(&stack_values);
		int left=peek(&stack_values); pop(&stack_values);
		int res=apply_operation(left,right,op);
		push(&stack_values,res);
	}
	printf("Result: %d\n",peek(&stack_values));
	display_stack(&stack_values);
}