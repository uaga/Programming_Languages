#include <stdio.h>

int main(void)
{
	char text[20];
	printf("Input text:\n");
	scanf("%19s", text);
	printf("Вы ввели:\n %s", text);
	return 0;
}
