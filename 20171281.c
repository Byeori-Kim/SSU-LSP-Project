#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) 
{
    FILE *file;
    int **matrix;
    file = fopen(argv[1], "r");
    if(file == NULL)
    {
        fprintf(stderr, "fopen error for %s\n", argv[1]);
        exit(1);
    }
    else
    {
        printf("Success!\nFilename: %s", argv[1]);

        exit(0);
    }



}
