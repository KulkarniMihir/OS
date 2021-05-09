#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char *argv[])
{
	int arr[15];
	int noOfElements = argc; 
	for(int i = 0; i < noOfElements;i++)
	{
		arr[i] = atoi(argv[i]);		//conversion back to int
		printf("%d\n",arr[i]);
	}
	
	int low = 0,mid, high = noOfElements-1;
	
	int temp;
	printf("Enter the number to be searched  ::");
	scanf("%d",&temp);
	while(low <= high)
	{
		mid = (high+low)/2;
		if(arr[mid] == temp)
		{
			printf("\nThe number %d is at position %d!\n",temp,mid+1);
			break;
		}
		else if (arr[mid] > temp){
			high = mid-1;
			continue;
		}
		else{
			low = mid+1;
			continue;
		}
	}
	if(low > high){
		printf("\nNot found");
	}
	printf("\nChild Process completed. Child exiting.\n");
	printf("---------------------------------------------------------\n");
}
