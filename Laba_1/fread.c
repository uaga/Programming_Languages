#include <stdio.h>
#include <stdlib.h>

char* Read_file(char *file_name)
{
	char *buffer = NULL;
	int str_size, read_size;
	FILE *fw = fopen(file_name, "r");

	if (fw)
	{
		/* Ищем конец файла и ставим туда "курсор" */
		fseek(fw, 0, SEEK_END);
		/* Записываем текущее положение курсора 
		(отступ - кол-во байтов от начала файла) */
		str_size = ftell(fw);
		/* Возвращаем указатель в начало файла */
		rewind(fw);

		/* Создаем строку в которю влезет весь файл */
		buffer = (char*) malloc(sizeof(char) * (str_size + 1));

		/*
		Теперь, наконец-то, читаем файл:
		Считываем str_size объектов из потока fw
		Каждый объект длинной sizeof(char) - один символ
		И записываем все это в buffer
		*/
		read_size = fread(buffer, sizeof(char), str_size, fw);

		/* Для того чтобы buffer был 100% строкой,
		надо в конец установить "\0" - символ конца строки
		так советуют статьи в интернете :)
		*/
		buffer[str_size] = '\0';

		/* И на всякий случай, если произойдет ошибка */
		if (str_size != read_size)
		{
			/* выкидываем память и ставим buffer в NULL */
			free(buffer);
			buffer = NULL;
		}

		/* Закрываем файл */
		fclose(fw);
	}

	return buffer;
}


int main(int argc, char **argv)
{
	char *str = Read_file(argv[1]);
	if (str)
	{
		puts(str);
		free(str);
	}

	return 0;
}
