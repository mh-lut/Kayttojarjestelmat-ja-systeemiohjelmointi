#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getBinary(int n, int x)
{
    int *binaryNum = (int*)calloc(x, sizeof(int));
    char *binary = (char*)malloc(sizeof(char) * 32 + 1);
    strcpy(binary, "");
 
    int i = 0;
    while (n > 0) {
 
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    char k[8] = "";
    for (int j = x - 1; j >= 0; j--){
    	sprintf(k, "%d", binaryNum[j]);
        strcat(binary, k);
    }
    printf("%s", binary);
    free(binary);
    free(binaryNum);
}

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		printf("No input file!\n");
		printf("usage: ./my-zip input.txt\n");
		exit(0);
	}
	
	int number = 2;
	
	while (argc >= number)
	{
		FILE* file;
		file = fopen(argv[number-1], "r");
		char x;
		char x2;
		if (NULL == file) {
			printf("my-cat: cannot open file\n");
			exit(1);
		}
		int count = 1;
		x = fgetc(file);
		while (x != EOF)
		{
			x2 = fgetc(file);
			if (x2 == EOF)
			{
				printf("%c", x);
				fclose(file);
				break;
			}
			if (x != x2)
			{
				getBinary(count, 32);
				getBinary(x, 8);
				count = 1;
				x = x2;
			}else
			{
				count++;
				x = x2;
			}
		}
		number++;
	}
}
