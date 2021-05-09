/*
  Mihir Kulkarni
  33132 L9 
  Assignment 3 : Matrix multiplication using pthreads
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
// 3*3 matrix solution using 27 threads
void *multiply(void *arg)
{
	//Function to multiply element by element of each row in matrix A
	//with each element in columns of matrix B
	int *data = (int *)arg;
	int k = 0;
	
	k = data[0] * data[1];
	
	int *p = (int *)malloc(sizeof(int));
	*p = k;
	
	pthread_exit(p);
}


int main()
{
	int res, r1, c1, r2, c2, max, count = 0;
	pthread_t *threads;
	
	printf("\nEnter the number of rows of columns for matrix matA:\n");
	scanf("%d %d", &r1, &c1);
	//Initialize matA
	int matA[r1][c1];
	
	printf("\n");
	//Input of matrix A
	for(int i=0; i<r1; i++)
	{
		for(int j=0; j<c1; j++)
		{
			printf("Enter the [%d][%d] element of matrix matA:", i, j);
			scanf("%d", &matA[i][j]);
		}
	}
	
	
	printf("\nEnter the number of rows of columns for matrix matB:\n");
	scanf("%d %d", &r2, &c2);
	//Initialize matB
	int matB[r2][c2];
	
	printf("\n");
	//Input of matrix B
	for(int i=0; i<r2; i++)
	{
		for(int j=0; j<c2; j++)
		{
			printf("Enter the [%d][%d] element of matrix matB:", i, j);
			scanf("%d", &matB[i][j]);
		}
	}
	
	//each row will take r1*c2 traversals for c1 columns
	//for e.g. in 3*3 matrices each resultant element requires sumation of 3 multiplications
	//i.e. 3 threads and for 9 elements : 9*3= 27 threads
	max = r1 * c2 * c1;
	threads = (pthread_t *)malloc(max*sizeof(pthread_t));
	
	int *data = NULL;
	for(int i=0; i<r1; i++)
	{
		for(int j=0; j<c2; j++)
		{
			for(int k=0; k<c1; k++)
			{
				//taking 2 elements at a time
				data = (int *)malloc(2*sizeof(int));
				data[0] = matA[i][k];
				data[1] = matB[k][j];
				//thread creation 
				res = pthread_create(&threads[count++], NULL, multiply, (void *)data);
				
				if (res != 0) 
				{
					perror("\nThread creation failed!\n");
					exit(EXIT_FAILURE);
				}
			}
		}
	}
	
	printf("\n---------------------------------------------------------\n");
	printf("\nThe resultant matrix is:\n\n");
	
	for(int i=0; i<max; i++)
	{
		void *k;
		int ans;
		//Joining threads 
		res = pthread_join(threads[i], &k);
		
		if (res != 0) 
		{
			perror("\nThread joining failed!\n");
			exit(EXIT_FAILURE);
		}
		//if first sub-part of r1*c2
		if(i % 3 == 0)
		{
			ans = *(int *)k;
		}
		//if second sub-part of r1*c2
		else if(i % 3 == 1)
		{
			ans += *(int *)k;
		}
		//added all three elements and print value of resultant matrix element
		else 
		{
			ans += *(int *)k;
			printf("%d ", ans);
			//if all elements in rows are over of resultant marix => next line
			if((i+1) % (r1*c2) == 0)
				printf("\n");
		}
	}
	
	return 0;
}
