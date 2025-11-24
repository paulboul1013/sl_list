#pragma once
#include "st.h"


int precedence(int op);
int apply_operation(int left,int right,int op);
void test_expression_evaluation();