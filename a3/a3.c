/*
	Mihir Kulkarni
	33132 L9 Assigment 3
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<malloc.h>
#define MAX 10
#define MAX_THREADS 10

int mat1[MAX][MAX],mat2[MAX][MAX],mat3[MAX][MAX];
int r1,r2,c1,c2;

void *Multiply(void *args)
{
	for (int i = 0; i < r1; i++)
	{
		for (int j = 0; j < c2; j++)
		{
			mat3[i][j]=0;
			for (int k = 0; k < c1; k++)  
			{
                mat3[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}  
          
             	
}

int main()
{
	int i,j;
	printf("\nEnter the rows of matrix 1 :");
	scanf("%d",&r1);
	
	printf("\nEnter the columns of matrix 1 :");
	scanf("%d",&c1);
	
	printf("\nEnter the rows of matrix 2 : ");
	scanf("%d",&r2);
	
	if(c1 != r2){
		printf("\nMatrix multiplication is not possible!!");
		exit(0);
	}
	
	printf("\nEnter the columns of matrix 2 : ");
	scanf("%d",&c2);

	printf("\nEnter matrix 1 :\n");
	for(int i = 0; i < r1;i++){
		for(int j = 0; j < c1;j++){
			printf("Enter element matrix [%d][%d] :: ",i+1,j+1);
			scanf("%d",&mat1[i][j]);
		}
	}
	
	printf("\nEnter matrix 2	:\n");
	for(int i = 0; i < r2;i++){
		for(int j = 0; j < c2;j++){
			printf("Enter element matrix [%d][%d] :: ",i+1,j+1);
			scanf("%d",&mat2[i][j]);
		}
	}

	printf("The matrix 1 is \n");
	for(int i = 0; i < r1;i++){
		for(int j = 0; j < c1;j++){
			printf("%d\t",mat1[i][j]);
		}
		printf("\n");
	}
	printf("The matrix 2 is \n");
	for(int i = 0; i < r2;i++){
		for(int j = 0; j < c2;j++){
			printf("%d\t",mat2[i][j]);
		}
		printf("\n");
	}

	pthread_t threads[MAX_THREADS];

    // Creating four threads, each evaluating its own part 	
    for (int i = 0; i < MAX_THREADS; i++) { 
        int* result; 
        pthread_create(&threads[i], NULL, Multiply, (void*)(result)); 
    } 
    // joining and waiting for all threads to complete 
	for (int i = 0; i < MAX_THREADS; i++)  
        pthread_join(threads[i], NULL);   

	printf("The multiplied matrix is \n");
	
	for(int i = 0; i < r1;i++){
		for(int j = 0; j < c2;j++){
			printf("%d\t",mat3[i][j]);
		}
		printf("\n");
	}
	return 0;

}

