#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <sys/types.h>

void bubble_sort(int arr[],int size)
{
	int temp;
	for(int i=0;i<size-1;i++)
	{
		for(int j=0;j<size-i-1;j++)
		{
			if(arr[j]>arr[j+1])
			{
				
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}

	printf("\nSorted elements:-\n");
    for(int i=0;i<size;i++)
    	printf("%d ",arr[i] );
}

int main()
{
	int intArray[15],size;
	char buffer[15],*arg[15]; //array of strings
	int pid;
	printf("\nEnter the size of array: ");
	scanf("%d",&size);
	printf("\nEnter the elements in array: ");
	for(int i=0;i<size;i++)
	{
		scanf("%d",&intArray[i]);
	}
	printf("Sorting elements:-\n");
	bubble_sort(intArray,size);
	printf("\n---------------------------------------------------------");
	printf("\nNow invoking fork\n");
	printf("---------------------------------------------------------\n");
	pid=fork();	
	if(pid==0)
	{
		//wait(NULL);

		printf("Into the child process\n");
		printf("---------------------------------------------------------\n");
		printf("\nSorted Numbers: ");
		//converting into string format
		for(int i = 0;i < size;i++)
		{
			sprintf(buffer, "%d", intArray[i]);
			arg[i] = malloc(sizeof(buffer));
			strcpy(arg[i], buffer);
		}

		arg[size] = NULL;

		for(int i=0;i<size;i++)
    		printf("%s",arg[i]);
		printf("\nInvoking another program\n");
		printf("\nExecuting execve.\n");
		execve("./2b2",arg,NULL);
		printf("\nExecve completed.\n");
		printf("\nChild Process completed. Child exiting.\n");
		printf("---------------------------------------------------------\n");
		
	}
	else if(pid>0)
	{
		printf("\nIn Parent process. Waiting.\n");
		printf("---------------------------------------------------------\n");
		sleep(10);
		//wait(0);
		printf("\nParent execution complete. Exiting.\n");
	}
	return 0;
}