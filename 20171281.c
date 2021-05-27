#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define Max_Int 20000

void secq_mode(int **mat, int gen);
void paral_mode(int **mat, int par_num, int gen);
void thre_mode(int **mat, int par_num, int gen);

int main(int argc, char *argv[]) 
{
    FILE *file;
	int mode = 0;
	int row;
	int col;
	int **matrix;
   	char tmp;

	printf("(1)Process Termination (2)Sequential Processing (3)Parallel Processing (4)Multi-Thread Processing\nChoose mode: ");
	scanf("%d", &mode);

	while(mode != 1)
	{
		row = 1;
   		file = fopen(argv[1], "r");
   		if(file == NULL)
   		{
       		 fprintf(stderr, "fopen error for %s\n", argv[1]);
       		 exit(1);
		}

		while(fscanf(file, "%c", &tmp) != EOF)
		{
			if(tmp == '\n')
				row++;
		}
		row = row+2;
		matrix = (int**)malloc(sizeof(int*)*row);

		printf("number of row is %d\n", row);
	

		if(mode == 2)
		{
			int generation = 0;
			printf("Put generation number: ");
			scanf("%d", &generation);
			for(int i = 0; i < generation; i++)
			{
				secq_mode(matrix, i);
			}
		}
		else if(mode == 3)
		{
			int child = 0;
			int generation = 0;
			printf("Put child number: ");
			scanf("%d", &child);
			printf("Put generation number: ");
			scanf("%d", &generation);
			for(int i = 0; i < generation; i++)
			{
			paral_mode(matrix, child, i);
			}
		}
		else if(mode == 4)
		{
			int thread = 0;
			int generation = 0;
			printf("Put Thread number: ");
			scanf("%d", &thread);
			printf("Put generation number: ");
			scanf("%d", &generation);
			for(int i = 0; i < generation; i++)
			{
			thre_mode(matrix, thread, i);
			}
		}
		else
		{
			printf("Wrong number!");
			exit(1);
		}
		printf("(1)Process Termination (2)Sequential Processing (3)Parallel Processing (4)Multi-Thread Processing\nChoose mode: ");
	scanf("%d", &mode);
	}
	
	printf("Bye~!\n");

	return 0;

}

void secq_mode(int **mat, int gen)
{
	printf("In secq_mode function\n");
}

void paral_mode(int **mat, int par_num, int gen)
{
	printf("In paral_mode function\n");
}

void thre_mode(int **mat, int par_num, int gen)
{
	printf("In thre_mode function\n");
}
