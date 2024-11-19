// 括号匹配算法
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义一个栈结构
typedef struct {
    char *array;
    int top;
    int capacity;
} Stack;

// 初始化栈
Stack* createStack(int capacity) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char *)malloc(stack->capacity * sizeof(char));
    return stack;
}

// 检查栈是否为空
bool isEmpty(Stack *stack) {
    return stack->top == -1;
}

// 向栈中压入元素
void push(Stack *stack, char item) {
    stack->array[++stack->top] = item;
}

// 从栈中弹出元素
char pop(Stack *stack) {
    return stack->array[stack->top--];
}

// 查看栈顶元素
char peek(Stack *stack) {
    return stack->array[stack->top];
}

// 检查括号是否配对
bool areBracketsBalanced(char *expression) {
    Stack *stack = createStack(strlen(expression));
    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        switch (ch) {
            case '(':
            case '[':
            case '{':
                push(stack, ch);
                break;
            case ')':
                if (isEmpty(stack) || pop(stack) != '(') {
                    free(stack->array);
                    free(stack);
                    return false;
                }
                break;
            case ']':
                if (isEmpty(stack) || pop(stack) != '[') {
                    free(stack->array);
                    free(stack);
                    return false;
                }
                break;
            case '}':
                if (isEmpty(stack) || pop(stack) != '{') {
                    free(stack->array);
                    free(stack);
                    return false;
                }
                break;
        }
    }
    bool balanced = isEmpty(stack);
    free(stack->array);
    free(stack);
    return balanced;
}

int main() {
    char expression[] = "{[()()]}"; // 可以修改这个字符串来测试不同的表达式
    if (areBracketsBalanced(expression)) {
        printf("The brackets are balanced.\n");
    } else {
        printf("The brackets are not balanced.\n");
    }
    return 0;
}
