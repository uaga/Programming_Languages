#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ERROR_EXIT -1

struct product {
	char name[64];
	int price;
};

int main() {
	FILE *file_input, *file_output;
	char str[64];
	char *split_str;
	char *estr;
	int price;
	char name[1028];
	int count_line;
	printf("Открытие файла на чтение: ");
	file_input = fopen("input.txt", "r");
	
	if (file_input == NULL) {printf("ошибка\n"); return ERROR_EXIT;}
	else {printf("выполнено\n");}
	
	struct product *list;
	list = malloc(256 * (sizeof(char)*64 + sizeof(int)));
	
	printf("Считаны строки:\n");
	split_str = malloc(1028);
	int i=0;
	char *spl = "-";
	while (1) {
		estr = fgets(str, sizeof(str), file_input);
		if (estr == NULL) {
			if (feof(file_input) != 0) {printf("\nЧтение файла закончено\n"); break;}
			else {printf("\nОшибка чтения из файла\n"); break;}
		}
		split_str = strtok(str, spl);
		if (split_str == NULL) {printf("error: strtok return NULL");}
		strcpy(name, split_str);
		split_str = strtok(NULL, spl);
		price = atoi(split_str);
		strcpy(list[i].name, name);
		list[i].price = price;
		printf("\tname = %s\tprice = %d\n", list[i].name, list[i].price);
		i++;
	}
	
	printf("Закрытие файла на чтение: ");
	if (fclose(file_input) == EOF) {printf("ошибка\n");}
	else {printf("выполнено\n\n");}
	/*
	printf("\n\n%s\n\n",list[2].name);
	printf("До сортировки:\n");
	for(int z=0; z<i; z++){
		printf("\tz = %d\n", z);
		printf("\tname = %s\tprice = %d\n", list[z].name, list[z].price);
	}
	*/
	count_line = i;
	for(int i=0; i<count_line-1; i++){
		for(int j=0; j<count_line - i - 1; j++){
			if(list[j].price > list[j+1].price){
				int tmp_price = list[j].price;
				char tmp_name[64];
				strcpy(tmp_name, list[j].name);
				list[j].price = list[j+1].price;
				strcpy(list[j].name, list[j+1].name);
				list[j+1].price = tmp_price;
				strcpy(list[j+1].name, tmp_name);
			}
		}
	}
	
	printf("Открытие файла на запись: ");
	file_output = fopen("out_num_3.txt", "w");
	if(file_output == NULL) {printf("ошибка"); return ERROR_EXIT;}
	else {printf("успешно\n");}

	printf("Запись в файл: \n");
	char *write = malloc(1024);
	for(int i=0; i<count_line ; i++){
		strcpy(write, list[i].name);
		fprintf(file_output, "%s\t-\t%d\n", write, list[i].price);
		printf("\tстрока %d записана\n", i);
	}
	printf("\nЗапись завершена\n");
	printf("Закрытие файла: ");
	if(fclose(file_output) == EOF) {printf("ошибка\n");}
	else {printf("успешно\n");}
	printf("\nКонец программы...\n\n");
	return 0;
}
