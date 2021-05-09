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
	char *buffer,*s[15]; //array of strings
	int pid;
	printf("\nEnter the size of array: ");
	scanf("%d",&size);
	printf("\nEnter the elements in array: ");
	for(int i=0;i<size;i++)
	{
		scanf("%d",&intArray[i]);
	}
	
	printf("Now invoking fork\n");
	printf("---------------------------------------------------------\n");
	pid=fork();
	if(pid == 0)
	{
		//system("wait");
		wait(NULL);
		//child
		printf("Into the child process\n");
		printf("---------------------------------------------------------\n");
		printf("Converting the array to string\n");
		int j;
		for(int j=0;j<size;j++)
		{
			//printf("%d\n",intArray[j]);
			sprintf(buffer,"%d",intArray[j]);
			s[j] = malloc(sizeof(buffer));
			strcpy(s[j],buffer);
		}
		s[size]=NULL;
		for(int i=0;i<size;i++)
    		printf("%d ",s[i] );
		printf("Invoking another program\n");
		//char *args[] = {"./a2-2b",NULL};
		execve("./a2-2b",s,NULL);
		printf("Returned to child process\nChild exiting\n");
	}
	else if(pid > 0)
	{
		//parent
		printf("Into the parent process\n");
		printf("---------------------------------------------------------\n");
		//sort array here
		printf("Sorting array\n");
		bubble_sort(intArray,size);
		printf("\nParent sleeping to invoke child process\n");
		printf("---------------------------------------------------------\n");

		sleep(15);
		printf("Parent woke up\n");
		printf("The parent is exiting\n");
	}
	
}