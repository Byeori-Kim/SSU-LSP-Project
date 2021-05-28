#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define Max_Int 20000

int row;
int col;
int **matrix;

int mat_check(int r, int c);
void secq_mode(int gen);
void secq_out();
void paral_mode(int par_num, int gen);
void paral_out(int par_num);
void thre_mode(int par_num, int gen);
void thre_out(int par_num);

int main(int argc, char *argv[]) 
{
    FILE *file;
	int mode;

	printf("(1)Process Termination (2)Sequential Processing (3)Parallel Processing (4)Multi-Thread Processing\nChoose mode: ");
	scanf("%d", &mode);

	while(mode != 1)
	{
		row = 1;
		col = 1;
		char *row_line;
		char line[Max_Int];
		char tmp;
		clock_t start, end;
		int result;
		start = clock();
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
		fseek(file, 0, SEEK_SET);
		row_line = fgets(line, Max_Int, file);
		char *tok = strtok(row_line, " ");
		while(tok != NULL)
		{
			col++;
			tok = strtok(NULL, " ");
		}
		col++;
		fseek(file, 0, SEEK_SET);
		for(int i = 0; i < row; i++)
		{
			matrix[i] = (int*)calloc(col, sizeof(int));
		}
		for(int i = 1; i < row-1; i++)
		{
			row_line = fgets(line, Max_Int, file);
			tok = strtok(row_line, " ");
			for(int j = 1; j < col-1; j++)
			{
				matrix[i][j] = atoi(tok);
				tok = strtok(NULL, " ");
			}
		}
		/*for(int i = 0;i<row;i++){
			for(int j=0;j<col;j++){
				printf("%d ", matrix[i][j]);
			}
			printf("\n");
		}*/

		if(mode == 2)
		{
			int generation = 0;
			printf("Put generation number: ");
			scanf("%d", &generation);
			for(int i = 1; i < generation; i++)
			{
				secq_mode(i);
			}
			secq_out();
			end = clock();
			result = (int)(end - start);
			printf("Total elapsed time is %d ms.\n", result);
		}
		else if(mode == 3)
		{
			int child = 0;
			int generation = 0;
			printf("Put child number: ");
			scanf("%d", &child);
			printf("Put generation number: ");
			scanf("%d", &generation);
			for(int i = 1; i < generation; i++)
			{
			paral_mode(child, i);
			}
			paral_out(child);
			end = clock();
			result = (int)(end - start);
			printf("Total elapsed time is %d ms.\n", result);
		}
		else if(mode == 4)
		{
			int thread = 0;
			int generation = 0;
			printf("Put Thread number: ");
			scanf("%d", &thread);
			printf("Put generation number: ");
			scanf("%d", &generation);
			for(int i = 1; i < generation; i++)
			{
			thre_mode(thread, i);
			}
			thre_out(thread);
			end = clock();
			result = (int)(end - start);
			printf("Total elapsed time is %d ms.\n", result);
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

int mat_check(int r, int c)
{
	int count = 0;
	if(matrix[r-1][c-1] == 1)
		count++;
	if(matrix[r-1][c] == 1)
		count++;
	if(matrix[r-1][c+1] == 1)
		count++;
	if(matrix[r][c-1] == 1)
		count++;
	if(matrix[r][c+1] == 1)
		count++;
	if(matrix[r+1][c-1] == 1)
		count++;
	if(matrix[r+1][c] == 1)
		count++;
	if(matrix[r+1][c+1] == 1)
		count++;
	return count;
}

void secq_mode(int gen)
{
	char fname[20];
	FILE *fp;
	sprintf(fname, "gen_%d.matrix", gen);
	fp = fopen(fname, "a");
	int **mat;
	mat = (int**)malloc(sizeof(int*)*row);
	for(int i = 0; i < row; i++)
	{
		mat[i] = (int*)calloc(col, sizeof(int));
	}
	for(int i = 1; i < row-1; i++)
	{
		for(int j = 1; j < col-1; j++)
		{
			int count = mat_check(i,j);

			if(matrix[i][j] == 0)
			{
				if(count == 4)
					mat[i][j] = 1;
				else
					mat[i][j] = 0;
				fprintf(fp, "%d ", mat[i][j]);
			}
			else if(matrix[i][j] == 1)
			{
				if(count<=2 || count>=7)
					mat[i][j] = 0;
				else
					mat[i][j] = 1;
				fprintf(fp, "%d ", mat[i][j]);
			}
		}
		fprintf(fp, "\n");
	}
	for(int i = 1; i < row-1; i++)
	{
		for(int j = 1; j < col-1; j++)
		{
			matrix[i][j] = mat[i][j];
		}
	}
}

void secq_out()
{
	char fname[] = "output.matrix";
	FILE *fp;
	fp = fopen(fname, "a");
	int **mat;
	mat = (int**)malloc(sizeof(int*)*row);
	for(int i = 0; i < row; i++)
	{
		mat[i] = (int*)calloc(col, sizeof(int));
	}
	for(int i = 1; i < row-1; i++)
	{
		for(int j = 1; j < col-1; j++)
		{
			int count = mat_check(i,j);

			if(matrix[i][j] == 0)
			{
				if(count == 4)
					mat[i][j] = 1;
				else
					mat[i][j] = 0;
				fprintf(fp, "%d ", mat[i][j]);
			}
			else if(matrix[i][j] == 1)
			{
				if(count<=2 || count>=7)
					mat[i][j] = 0;
				else
					mat[i][j] = 1;
				fprintf(fp, "%d ", mat[i][j]);
			}
		}
		fprintf(fp, "\n");
	}
	for(int i = 1; i < row-1; i++)
	{
		for(int j = 1; j < col-1; j++)
		{
			matrix[i][j] = mat[i][j];
		}
	}
}
void paral_mode( int par_num, int gen)
{
	printf("In paral_mode function\n");
}

void paral_out( int par_num)
{
	printf("In paral_mode function\n");
}

void thre_mode(int par_num, int gen)
{
	printf("In thre_mode function\n");
}

void thre_out(int par_num)
{
	printf("In thre_mode function\n");
}
