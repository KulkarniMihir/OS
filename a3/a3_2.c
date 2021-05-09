/*
  Mihir Kulkarni
  33132 L9 
  Assignment 3 : Matrix multiplication using pthreads
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<malloc.h>
#define MAX 4
/* 9 thread solution for a 3*3 matrix */

//Each thread computes single element in the resultant matrix 
void *mult(void* arg) 
{ 
    int *data = (int *)arg; 
    int k = 0, i = 0; 
      
    int x = data[0];
    //r1=c2=x number of sumations of multiplications in array 
    for (i = 1; i <= x; i++) 
           k += data[i]*data[i+x]; 
      
    int *p = (int*)malloc(sizeof(int)); 
    *p = k; 
      
    //Used to terminate a thread and the return value is passed as a pointer 
    pthread_exit(p); 
} 
  
//Driver code 
int main() 
{
  int r1,c1,r2,c2,i,j,k; 
   
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
  //Initialize matA
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
      
      
    int max = r1*c2; 
      
      
    //declaring array of threads of size r1*c2         
    pthread_t *threads; 
    threads = (pthread_t*)malloc(max*sizeof(pthread_t)); 
      
    int count = 0; 
    int* data = NULL; 
    for (i = 0; i < r1; i++) 
    {  
        for (j = 0; j < c2; j++) 
        { 
                 
            //storing row and column elements in data  
            data = (int *)malloc((r1*c2)*sizeof(int)); 
            //number of sumations of  multiplications in array
            data[0] = c1; 
            //Inserting row
            for (k = 0; k < c1; k++) 
                data[k+1] = matA[i][k]; 
            //Inserting column after row elements
            for (k = 0; k < r2; k++) 
                data[k+c1+1] = matB[k][j]; 
               
            //creating threads 
            pthread_create(&threads[count++], NULL, mult, (void*)(data)); 
                                
                  
        } 
    }  
    printf("---------------------------------------------\n");
    printf("RESULTANT MATRIX IS :- \n"); 
    for (i = 0; i < max; i++)  
    { 
      void *k; 
        
      //Joining all threads and collecting return value  
      pthread_join(threads[i], &k); 
             
            
      int *p = (int *)k; 
      printf("%d ",*p); 
      if ((i + 1) % c2 == 0) 
          printf("\n"); 
    } 
    printf("---------------------------------------------\n");

      
  
  return 0; 
} 