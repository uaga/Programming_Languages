#include <stdlib.h>
#include <stdio.h>

#define STACK_MAX_SIZE 20
#define STACK_OVERFLOW -100
#define STACK_UNDERFLOW -101

typedef int T;

typedef struct Stack_tag {
	T data[STACK_MAX_SIZE];
	size_t size;
} Stack_t;

void push(Stack_t *stack, const T value){
	if(stack->size >= STACK_MAX_SIZE) {
		printf("Error: STACK_OVERFLOW\n");
		exit(STACK_OVERFLOW);
	}
	stack->data[stack->size] = value;
	stack->size++;
}

T pop(Stack_t *stack){
	if(stack->size == 0) {
		printf("Error: STACK_UNDERFLOW\n");
		exit(STACK_UNDERFLOW);
	}
	stack->size--;
	return stack->data[stack->size];
}

T peek(const Stack_t *stack){
	if(stack->size <= 0) {
		printf("Error: STACK_UNDERFLOW\n");
		exit(STACK_UNDERFLOW);
	}
	return stack->data[stack->size-1];
}

void printStackValue(const T value){
	printf("%d", value);
}

void printStack(const Stack_t *stack){
	int i;
	int len = stack->size-1;
	printf("stack %d > ", stack->size);
	for(i=0; i<len; i++){
		printStackValue(stack->data[i]);
		printf("|");
	}
	if(stack->size != 0) {printStackValue(stack->data[i]);}
	printf("\n");
}

int main(){
	Stack_t stack;
	stack.size = 0;
	
	printf("Введите размер стека: ");
	int size_stack;
	scanf("%d", &size_stack);
	
	for(int i=0; i<size_stack; i++){
		push(&stack, i);
		printStack(&stack);
	}
	printf("\nВерхний элемент: %d\n", peek(&stack));
	printf("\nСостояние стека:\n");
	printStack(&stack);
	printf("\nВзяли верхний элемент: %d\n", pop(&stack));
	printf("\nНынешний верхний элемент: %d\n", peek(&stack));
	printf("\nСостояние стека:\n");
	printStack(&stack);
}
