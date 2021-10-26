#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
	int r[5];
	srand(time(NULL));
	for(int i=0; i<5; i++){
		r[i] = rand()%25;
		printf("%d\n", r[i]);
	}
	FILE *wr = fopen("out_num_1.txt", "w+");
	for(int i=0; i<5; i++){
		fprintf(wr, "%d\n", r[4-i]);
	}
	fclose(wr);
	return 0;
}
