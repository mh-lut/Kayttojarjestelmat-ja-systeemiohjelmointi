#include <stdio.h>
#include <stdlib.h>

int main (int argc, char * argv[])
{
	if (argc < 2)
	{
		printf("No input file!\n");
		printf("usage: ./my-cat input.txt\n");
		exit(0);
	}
	
	int number = 2;
	
	while (argc >= number)
	{
		FILE* file;
		file = fopen(argv[number-1], "r");
		char x;
		if (NULL == file) {
			printf("my-cat: cannot open file\n");
			exit(1);
		}
		x = fgetc(file);
		while (x != EOF)
		{
			printf("%c", x);
			x = fgetc(file);
		}
		printf("\n");
		fclose(file);
		number++;
	}
	return 0;
}
