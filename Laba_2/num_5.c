#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_NAME "input_num_5.t"
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

typedef char T;

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
        printf("%c", value);
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
	char *in_text = readFile();
	char *text;
	char ch[1];
	text = (char*)malloc(strlen(in_text));
	strcpy(text, in_text);
	printf("strlen = %d\n", strlen(text));
	puts(text);
	Stack_t rev_digit;
	rev_digit.size = 0;
	Stack_t rev_opers;
	rev_opers.size = 0;
	for(int i=0; i < strlen(text)-1; i++){
		ch[0] = *(text+i);
		if(isdigit(ch[0])){
			push(&rev_digit, ch[0]);
		}
		if( ch[0]=='+' || ch[0]=='-' || ch[0]=='*' || ch[0]=='/' ){
			push(&rev_opers, ch[0]);
		}
	}

	Stack_t digit;
	digit.size = 0;
	Stack_t opers;
	opers.size = 0;

	printStack(&rev_opers);
	printStack(&rev_digit);

	int size = rev_digit.size;
	for(int i=0; i<size; i++) {push(&digit, pop(&rev_digit));}
	size = rev_opers.size;
	for(int i=0; i<size; i++) {push(&opers, pop(&rev_opers));}

	printStack(&digit);
	printStack(&opers);

	printf("Вывод:\n");

	while(digit.size != 1){
		int result = 0;
		int a = (int)pop(&digit)-48;
		int b = (int)pop(&digit)-48;
		char oper = pop(&opers);
		switch(oper){
			case '+' : {result=a+b; break;}
			case '-' : {result=a-b; break;}
			case '*' : {result=a*b; break;}
			case '/' : {result=a/b; break;}
		}
		push(&digit, result+'0');
		printf("%d%c%d=%c\n", a, oper, b, peek(&digit));
	}
	printf("\nresult = %c", pop(&digit));

	return 0;
}
