#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OUT_FILE "output_num_2.txt"

float * gen_mass(int size){
	float *mass;
	float r;
	mass = malloc(size * sizeof(float));
	srand(time(NULL));
	for (int i=0; i<size; i++){
		r = rand() %1000;
		mass[i] = 1/r;
	}
	return mass;
}

void print_mass(float* mass, int size){
	printf("\nRead_in_mass:\n");
	for(int i=0; i<size; i++){
		printf("%f\n", mass[i]);
	}
}

int main(int argc, char **argv){
	int m_size = atoi(argv[1]);
	float *mass = gen_mass(m_size);

	print_mass(mass, m_size);

	for(int i=0; i<m_size-1; i++) {
		for(int j=0; j<m_size-i-1; j++) {
			if(mass[j] > mass[j+1]) {
				float tmp = mass[j];
				mass[j] = mass[j+1] ;
				mass[j+1] = tmp;
			}
		}
	}

	FILE *wr = fopen(OUT_FILE, "w+");
        for(int i=0; i<m_size; i++){
                fprintf(wr, "%f\n", mass[i]);
        }
        fclose(wr);
}
