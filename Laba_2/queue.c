/*
В данной проге реализован тип данных "очередь" или "queue"
Данная структура организованна по типу:
FIFO - first in - first out (первым зашел - первым вышел)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_MAX_SIZE 100
#define QUEUE_UNDERFLOW -100
#define TRUE 1
#define FALSE 0

typedef int Type_queue;
/*Струрктура хранит только int*/

typedef struct Queue_tag {
	/*Собсно сама структура массив и размер*/
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

/*Функция печатает 1 переданный агрумент*/
void printQueueValue(const Type_queue value) {printf("%d", value);}

void printQueue(const Queue_t *queue){
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

int main(){
	Queue_t queue;
	queue.size=0;

	for(int i=5; i<15; i++){
		pushQ(&queue, i);
	}
	printQueue(&queue);
	int len = queue.size;
	for(int i=0; i<len; i++){
		printf("\nДостаем элемент: %d\n", popQ(&queue));
		printQueue(&queue);
	}

	return 0;
}
