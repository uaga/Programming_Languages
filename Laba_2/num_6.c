#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "input_num_6.txt"
#define QUEUE_MAX_SIZE 100
#define STACK_MAX_SIZE 100
#define QUEUE_UNDERFLOW -101
#define STACK_UNDERFLOW -101
#define TRUE 1
#define FALSE 0

/*-----------------------------------------------------------------------------------------------*/
/* Функция для принятия данных из файла FILE_NAME */
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

/*################################################################*/
/* Очередь типа char */
/* Тут все работает */
typedef char Type_queue;

typedef struct Queue_tag {
	Type_queue data[QUEUE_MAX_SIZE];
	size_t size;
} Queue_t;

int pushQ(Queue_t *queue, const Type_queue value){
	/*
	Функиция для добавления элемента в очередь
	В конец queue добавляется элемент value,
	размер (queue->size) увеличивается на 1
	Если максимальный размер (QUEUE_MAX_SIZE) достигнут,
	то фунция ничего не запишет и вернет FALSE
	Если элемент добавлен в очередь, функция вернет TRUE
	 */
	if(queue->size >= QUEUE_MAX_SIZE) {
		printf("Error: QUEUE_OVERFLOW\n");
		return FALSE;
	}
	else{
		queue->data[queue->size] = value;
		queue->size++;
		return TRUE;
	}
}

Type_queue popQ(Queue_t *queue){
	/*
	Фунция для изъятия одного элемента из очереди
	Достается первый в очереди элемент, все остальные сдвигаются на 1 позицию к началу
	Функция возвращает первый элемент
	*/
	if(queue->size == 0){
		printf("Error: QUEUE_UNDERFLOW\n");
		exit(QUEUE_UNDERFLOW);
	}
	Type_queue out = queue->data[0];
	int len = queue->size;
	for(int i=0; i<len; i++) {queue->data[i] = queue->data[i+1];}
	queue->size--;
	return out;
}

Type_queue peekQ(Queue_t *queue){
	if(queue->size == 0){
		printf("Error: QUEUE_UNDERFLOW\n");
		exit(QUEUE_UNDERFLOW);
	}
	return queue->data[0];
}

/* Вывод одного переданного элемента */
void printQueueValue(const Type_queue value) {printf("%c", value);}

void printQ(const Queue_t *queue){
	/*
	Функция для вывода очереди в консоль
	Формат:
	queue (кол-во_элементов_в_очереди) -> элемент_1|элемнт_2|элемент_3|...|элемент_n
	*/
	int len = queue->size;
	printf("queue %d -> ", queue->size);
	for(int i=0; i<len; i++){
		printQueueValue(queue->data[i]);
		if(i<len-1) {printf("|");}
		else {printf("\n");}
	}
}

/*###################################################################*/
/* Стек типа char */
/* Тут все работает */
typedef char T_stack;

typedef struct Stack_tag {
	T_stack data[STACK_MAX_SIZE];
	size_t size;
} Stack_t;

/* Функция добавления одного элемента на вершину стека */
int pushS(Stack_t *stack, const T_stack value){
	if(stack->size >= STACK_MAX_SIZE) {
		printf("Error: STACK_OVERFLOW\n");
		return FALSE;
	}
	stack->data[stack->size] = value;
	stack->size++;
	return TRUE;
}

/* Функция изъятия одного элемента из стека */
T_stack popS(Stack_t *stack){
	if(stack->size == 0) {
		printf("Error_pop: STACK_UNDERFLOW\n");
		exit(STACK_UNDERFLOW);
	}
	stack->size--;
	return stack->data[stack->size];
}

/* Просмотр вершины стека */
T_stack peekS(const Stack_t *stack){
	if(stack->size <= 0) {
		/*printf("Error_peek: STACK_UNDERFLOW\n");*/
	}
	return stack->data[stack->size-1];
}

/* Вывод одного переданного элемента */
void printStackValue(const T_stack value) {printf("%c", value);}

/* Вывод всего переданного стека целиком */
void printS(const Stack_t *stack){
	int i;
	int len = stack->size-1;
	printf("stack_char %d > ", stack->size);
	for(i=0; i<len; i++){
		printStackValue(stack->data[i]);
		printf("|");
	}
	if(stack->size != 0) {printStackValue(stack->data[i]);}
	printf("\n");
}

/*----------------------------------------------------------------------------------------------------------*/

int main(){
	char *text = readFile();
	printf("Input:\n\t%s\n", text);

	Stack_t stack;
	stack.size = 0;
	Queue_t queue;
	queue.size = 0;

	int text_len = strlen(text);
	for(int i=0; i<text_len; i++){
		char top = peekS(&stack);
		if(text[i]=='0' || text[i]=='1' || text[i]=='2' || text[i]=='3' || text[i]=='4' || text[i]=='5' || text[i]=='6' || text[i]=='7' || text[i]=='8' || text[i]=='9'){
			pushQ(&queue, text[i]);
			continue;
		}
		if(text[i]=='+' || text[i]=='-' || text[i]=='*' || text[i]=='/' ){
			if(stack.size==0){
				pushS(&stack, text[i]);
				continue;
			}
			if(top=='(') {
				pushS(&stack, text[i]);
				continue;
			}
			if((text[i]=='*' || text[i]=='/') && (top=='*' || top=='/')){
				while((peekS(&stack)=='*' || peekS(&stack)=='/') && stack.size!=0) {pushQ(&queue, popS(&stack));}
				pushS(&stack, text[i]);
				continue;
			}
			if((text[i]=='*' || text[i]=='/') && (top!='*' || top!='/')) {
                                pushS(&stack, text[i]);
                                continue;
                        }
			if((text[i]=='+' || text[i]=='-') && (top=='*' || top=='/' || top=='+' || top=='-')){
				while(peekS(&stack)!='(' && stack.size!=0) {pushQ(&queue, popS(&stack));}
				pushS(&stack, text[i]);
				continue;
			}
		}
		if(text[i]=='(') {
			pushS(&stack, text[i]);
			continue;
		}
		if(text[i]==')') {
			while(peekS(&stack)!='(' && stack.size!=0) {pushQ(&queue, popS(&stack));}
			popS(&stack);
			continue;
		}
	}
	while(stack.size!=0) {pushQ(&queue, popS(&stack));}
	/*printQ(&queue);*/

	int out_text_len = queue.size;
	char *out_text = malloc(out_text_len);
	for(int i=0; i<out_text_len; i++){
		out_text[i] = popQ(&queue);
	}
	printf("--------------------------------------------\nOutput:\n\t%s\n", out_text);

	return 0;
}
