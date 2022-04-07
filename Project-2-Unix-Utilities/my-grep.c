#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    }
    else if (argc == 2)
    {
        char buffer[256];
        while (1)
        {
            fgets(buffer, 256, stdin);
            if (strstr(buffer, argv[1]) != NULL)
            {
                printf("%s", buffer);
            }
            if (strcmp(buffer, "exit\n") == 0)
            {
                break;
            }
        }
    }
    else
    {
        int filePointer = 2;
        while (filePointer < argc)
        {
            FILE *file = fopen(argv[filePointer], "r");
            if (file == NULL)
            {
                perror("my-grep: cannot open file\n");
                exit(1);
            }
            char *line = NULL;
            size_t len = 0;
            while (getline(&line, &len, file) != -1)
            {
                if (strstr(line, argv[1]) != NULL)
                {
                    printf("%s", line);
                }
            }
            filePointer++;
            fclose(file);
            free(line);
        }
    }
    return 0;
}
