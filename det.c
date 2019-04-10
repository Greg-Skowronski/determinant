#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <time.h>

#define MAX 7

void EnterSize();
double Det(double **, int);
void FreeMatrix(double **, int);

int COLUMNS, ROWS; // Matrix[Y][X] where Y - rows and X - columns
int ERROR = 0;
double DET_RESULT = 0;

int main()
{
    
    srand(time(NULL));
    
    int CurrentRow;
    int CurrentColumn;
    char ClearBuffor;
    
    printf("\nEnter size of matrix: \n");
    
        EnterSize();
        
        printf("\nYour matrix: %d x %d \n",ROWS,ROWS);
	
    double **Matrix = NULL;
    Matrix = (double **)malloc(ROWS * sizeof(double *));
        if(Matrix==NULL) 
	{
	  if(ROWS<=0)
	    printf("\nWrong argument.\nToo small value.\n");
	  else if(ROWS>0)
	  printf("\nWrong argument.\nNot enough memory to allocate data.\n");
	  return 0;
	}
	for (CurrentRow = 0; CurrentRow < ROWS; CurrentRow++)
      {
         Matrix[CurrentRow] = (double *)malloc(COLUMNS * sizeof(double));
	if(Matrix[CurrentRow]==NULL) 
	{
	  if(CurrentRow>0)
	  FreeMatrix(Matrix,CurrentRow-1);
	  printf("\nERROR\n");
	  return 0;
	}
      }
    if(Matrix!=NULL)
    {
    
    printf("\n");
    for (CurrentRow = 0; CurrentRow <  ROWS; CurrentRow++)
    {
        for (CurrentColumn = 0; CurrentColumn < COLUMNS; CurrentColumn++)
            while(scanf("%lf",&Matrix[CurrentRow][CurrentColumn])!=1)
            {
                while ((ClearBuffor = getchar()) != '\n' && ClearBuffor != EOF)
                printf("\nWrong number. Try again.\n\n");
            }
        printf("\n");
    }
        

    for (CurrentRow = 0; CurrentRow <  ROWS; CurrentRow++)
    {
        for (CurrentColumn = 0; CurrentColumn < COLUMNS; CurrentColumn++)
		printf("%lf     ",Matrix[CurrentRow][CurrentColumn]);
        printf("\n");
    }
    
    DET_RESULT = Det(Matrix,COLUMNS);
    if(ERROR==0)
    printf("\nDeterminant of your matrix: %lf\n\n", DET_RESULT);
    else
      printf("\nERROR\n");
    
    
    
    }else printf("\nERROR\n");
    
    FreeMatrix(Matrix,COLUMNS);

    
	return 0;
}

void EnterSize()
{
    char Correct;
    int Correctness=0;
    char ClearBuffor;
    
    while(Correctness==0)
    {

    if(scanf("%d%c", &ROWS, &Correct) != 2 || Correct != '\n')
    {
        printf("\nWrong number. Try again.\n\n");
        while ((ClearBuffor = getchar()) != '\n' && ClearBuffor != EOF)
        Correctness=0;
        continue;
    }
    else
        Correctness=1;
    
    }
    COLUMNS=ROWS;

}

double Det(double **Matrix, int Size)
{
    int CurrentRow;
    
    int MatrixColumn, SubRow, SubColumn;

    double Result=0;
    
    int NextColumn=0;
    
    //RESULT FOR 1X1 MATRIX
    if(Size == 1)
    {
        Result = Matrix[0][0];
        return Result;
    }
    //RESULT FOR 2X2 MATRIX - SIMPLE EQUATION
    else if(Size == 2)
    {
        Result = Matrix[0][0] * Matrix[1][1] - Matrix[1][0] * Matrix[0][1];
        return Result;
    }
    //CALCULATE DET USING LAPLACE
    else 
    {
    //CREATE SUB-MATRIX (ROW-1 AND COLUMN-1)
	double **SubMatrix = NULL;
        SubMatrix = (double **)malloc((Size - 1) * sizeof(double *));
	if(SubMatrix==NULL) 
	{
	  printf("\nWrong argument.\nToo small value.\n");
	  ERROR = 1;
	  return -1;
	}
        for (CurrentRow = 0; CurrentRow < (Size - 1); CurrentRow++)
         SubMatrix[CurrentRow] = (double *)malloc((Size - 1) * sizeof(double));
    //LAPLACE    
        
        if(SubMatrix!=NULL)
        {
        
        for(MatrixColumn=0; MatrixColumn<Size; MatrixColumn++)
        {
            for(SubRow=0; SubRow<Size-1; SubRow++)
            {
                
                for(SubColumn=0; SubColumn<Size-1; SubColumn++)
                {
                    if(SubColumn==MatrixColumn) NextColumn=1;
                    SubMatrix[SubRow][SubColumn]=Matrix[SubRow+1][SubColumn+NextColumn];
                    
                }
            NextColumn=0;
            }
        
        NextColumn=0;
        
	    Result=Result+Matrix[0][MatrixColumn]*pow(-1.0,1+(MatrixColumn+1))*Det(SubMatrix,Size-1);
	  
          
        }
        
        FreeMatrix(SubMatrix, Size-1);
        }else printf("\nERROR\n");
    }
    
	return Result;

}

void FreeMatrix(double **Matrix, int Size)
{
int CurrentColumn;
for(CurrentColumn=0;CurrentColumn<Size;CurrentColumn++)
		{
			free(Matrix[CurrentColumn]);
		}
		free(Matrix);
}
