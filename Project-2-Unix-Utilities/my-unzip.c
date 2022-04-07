#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getInt(char * binary, int x)
{
	double potenssi = 0;
	int result = 0;
	int num = 1;
	for (int i = x - 1; i >= 0; i--)
	{		
		if (binary[i] == '1')
		{	
			if (potenssi > 0) 
			{
				for (int k = 0; k < potenssi; k++)
				{
					num = num * 2;
				}
			}
			result += num;
			num = 1;
		}
		potenssi++;
	}
	return result;
}

int main(int argc, char ** argv)
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
		file = fopen(argv[number - 1], "r");
		if (NULL == file) {
			printf("my-unzip: cannot open file\n");
			exit(1);
		}
		char x;
		char *k = (char*)malloc(sizeof(char) * 1 + 1);
		strcpy(k, "");
		int i = 0;
		char *count = (char*)malloc(sizeof(char) * 32 + 1); 
		char *ascii = (char*)malloc(sizeof(char) * 8 + 1);
		strcpy(count, "");
		strcpy(ascii, "");
		x = fgetc(file);
		while (x != EOF)
		{	
			if (i < 32)
			{
				k[0] = x;
				strcat(count, k);
				i++;
				x = fgetc(file);
			}
			else if (i < 40)
			{
				k[0] = x;
				strcat(ascii, k);
				i++;
				x = fgetc(file);
			}
			else {
				
				int countNum = getInt(count, 32);
				int asciiNum = getInt(ascii, 8);
				for(int z = 0; z < countNum; z++)
				{
					printf("%c", asciiNum);
				}
				strcpy(count, "");
				strcpy(ascii, "");
				i = 0;
			}
			
		}
		printf("\n");
		free(count);
		free(ascii);
		fclose(file);
		number++;
	}
	return 0;
}
