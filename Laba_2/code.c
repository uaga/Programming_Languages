#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float * gen_mass(int size){
	float *mass;
	float r;
	mass = (float*)malloc(size * sizeof(float));
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
}
