#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_NAME "input_num_5.txt"
#define STACK_MAX_SIZE 100
#define ERROR_STACK_OVERFLOW -100
#define ERROR_STACK_UNDERFLOW -101

char* readFile(){
	char *buffer = NULL;
	int str_size, read_size;
	FILE *file = fopen(FILE_NAME, "r");
	if(file){
		fseek(file, 0, SEEK_END);
		str_size = ftell(file);
		rewind(file);
		buffer = (char*) malloc(str_size+1);
		read_size = fread(buffer, sizeof(char), str_size, file);
		buffer[str_size] = '\0';

		if(str_size != read_size){
			free(buffer);
			buffer = NULL;
		}
		fclose(file);
	}
	return buffer;
}

typedef int T;

typedef struct Stack_tag {
        T data[STACK_MAX_SIZE];
        size_t size;
} Stack_t;

void push(Stack_t *stack, const T value){
        if(stack->size >= STACK_MAX_SIZE) {
                printf("Error_push: STACK_OVERFLOW\n");
                exit(ERROR_STACK_OVERFLOW);
        }
        stack->data[stack->size] = value;
        stack->size++;
}

T pop(Stack_t *stack){
        if(stack->size == 0) {
                printf("Error_pop: STACK_UNDERFLOW\n");
           	exit(ERROR_STACK_UNDERFLOW);
        }
        stack->size--;
        return stack->data[stack->size];
}

T peek(const Stack_t *stack){
        if(stack->size <= 0) {
                printf("Error_peek: STACK_UNDERFLOW\n");
		exit(ERROR_STACK_UNDERFLOW);
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
	char *text = readFile();
	printf("Input:\n\t%s\n", text);
	int len_text = strlen(text);
	Stack_t stack;
	stack.size=0;

	for(int i=0; i<len_text; i++){
		if(isdigit(text[i])) {push(&stack, (int)(text[i]-'0'));}
		if(text[i]=='+' || text[i]=='-' || text[i]=='*' || text[i]=='/'){
			int b = pop(&stack);
			int a = pop(&stack);
			switch(text[i]){
				case '+' : {push(&stack, a+b);break;}
				case '-' : {push(&stack, a-b);break;}
				case '*' : {push(&stack, a*b);break;}
				case '/' : {push(&stack, a/b);break;}
			}
		}
	}
	printf("-----------------------------\nOutput:\n\t%d\n", pop(&stack));

	return 0;
}
