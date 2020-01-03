#include<stdio.h>
#include<stdlib.h>

void print_board(int** board, int height, int width)
{
    printf("printing board\n");
    for(int i=0; i < height; i++)
    {
        for(int j=0; j < width; j++)
        {
	        printf("%d,", board[i][j]);
        }
		printf("\n");
    }
    printf("-----------------\n");
}	
int number_of_neighbors(int** board, int i, int j, int height, int width)
{
    int count = 0;
    count += board[(i-1+height)%height][(j-1+width)%width];
    count += board[(i-1+height)%height][j          %width];
    count += board[(i-1+height)%height][(j+1)      %width];
    count += board[i           %height][(j-1+width)%width];
    count += board[i           %height][(j+1)      %width];
    count += board[(i+1)       %height][(j-1+width)%width];
    count += board[(i+1)       %height][j          %width];
    count += board[(i+1)       %height][(j+1)      %width];
	return count;
}
int** game_of_life(int** board, int height, int width)
{
    int** new_board=malloc((sizeof *new_board) * height); 
	for(int i=0; i < height;i++)
	{
	    new_board[i] = malloc(sizeof *(new_board[i]) * width);
    }
	for(int i=0; i < height; i++)
	{
		for(int j=0; j < width; j++)
		{
			int n = number_of_neighbors(board, i, j, height, width);
            if(board[i][j]==1)
            {
			    if(n<=1)
			    {
			        new_board[i][j] = 0;
			    }
                else if(n>=4)
                {
                    new_board[i][j] = 0;
                }
                else if(n==2 || n==3)
                {
                    new_board[i][j] = 1;
                }
                else
                {
                    new_board[i][j]=board[i][j];
                }
            }
            else if(board[i][j]==0)
            {
                if(n==3)
                {
                    new_board[i][j]=1;
                }
                else
                {
                    new_board[i][j]=board[i][j];
                }
            }
            else
            {
                new_board[i][j]=board[i][j];
            }
		}
	}
    return new_board;
}
int** initialize_board1(void)
{
    int height=5,width=5;
    int **a=malloc(sizeof *a * height);
    printf("Initializing board of size %d X %d with initial value 0\n", height,width);
    for(int i=0;i<height;i++)
    {
        a[i]=malloc(sizeof *(a[i]) * width);
        for(int j=0;j<width;j++)
        {
            a[i][j]=0;
        }
    }
    a[1][2]=1;
    a[2][0]=1;
    a[2][2]=1;
    a[3][1]=1;
    a[3][2]=1;
    printf("Printing the matrix...\n");
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    return a;
}
int main(void)
{
    int **board=initialize_board1();
    for(int i=0;i<10;i++)
    {
        board=game_of_life(board,5,5);
        print_board(board,5,5);
    }
    return 0;
}
