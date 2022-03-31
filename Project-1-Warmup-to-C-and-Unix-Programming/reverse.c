#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node for the linked list.
struct input_list
{
    char *value;
    struct input_list *pNext;
};

// Function to allocate memory for the linked list and adding items to it.
struct input_list *addItemToList(struct input_list *pStart, char *item)
{
    struct input_list *ptr, *pNew;
    if ((pNew = (struct input_list *)malloc(sizeof(struct input_list))) == NULL)
    {
        printf("Cannot allocate memory!\n");
        exit(1);
    }
    pNew->value = (char *)malloc(sizeof(char) * strlen(item) + 1);
    strcpy(pNew->value, item);
    pNew->pNext = NULL;
    if (pStart == NULL)
    {
        pStart = pNew;
    }
    else
    {
        ptr = pStart;
        while (ptr->pNext != NULL)
        {
            ptr = ptr->pNext;
        }
        ptr->pNext = pNew;
    }
    return pStart;
}

// Function that read the linked list in reverse order if the user only gives the input file.
void readList(struct input_list *pStart)
{
    if (pStart == NULL)
    {
        return;
    }

    readList(pStart->pNext);

    printf("%s", pStart->value);
}

// Function that writes the linked list in reverse order to the output file.
void writeList(struct input_list *pStart, FILE *output)
{
    if (pStart == NULL)
    {
        return;
    }

    writeList(pStart->pNext, output);

    fprintf(output, "%s", pStart->value);
}

int main(int argc, char *argv[])
{
    struct input_list *pStart = NULL;
    // No command line arguments given
    if (argc == 1)
    {
        fprintf(stderr, "No input files\nUsage: ./reverse <input> <output>\n");
        exit(1);
    }
    // One command line argument given
    else if (argc == 2)
    {
        char buf[99];
        FILE *input = fopen(argv[1], "r");
        if (input == NULL)
        {
            fprintf(stderr, "Cannot open file %s.\n", argv[1]);
            exit(1);
        }
        while (fgets(buf, 99, input))
        {
            pStart = addItemToList(pStart, buf);
        }
        readList(pStart);
        fclose(input);
    }
    // Two command line arguments given
    else if (argc == 3)
    {
        if (strcmp(argv[1], argv[2]) == 0)
        {
            printf("Input and output files must differ\n");
            exit(1);
        }
        FILE *input = fopen(argv[1], "r");
        FILE *output = fopen(argv[2], "w");
        char buf[99];
        if (input == NULL || output == NULL)
        {
            fprintf(stderr, "Cannot open file(s) %s/%s.\n", argv[1], argv[2]);
            exit(1);
        }
        while (fgets(buf, 99, input))
        {
            pStart = addItemToList(pStart, buf);
        }
        writeList(pStart, output);
        printf("Content of the %s file written to file %s in reverse order\n", argv[1], argv[2]);
        fclose(input);
        fclose(output);
    }
    // More than two command line arguments given
    else
    {
        fprintf(stderr, "Too many input files\nUsage: ./reverse <input> <output>\n");
        exit(1);
    }
    return 0;
}
