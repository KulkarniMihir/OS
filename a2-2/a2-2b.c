#include <stdio.h>


int main(int argc,char *argv[])
{
	int arr[15];
	int noOfElements = argc; 
	for(int i = 0; i < noOfElements;i++)
	{
		arr[i] = atoi(argv[i]);
		printf("%d\n",arr[i]);
	}
	int low = 0,mid, high = noOfElements;
	
	int temp;
	printf("Enter the number to be searched  ::\n");
	scanf("%d",&temp);
	
	while(low <= high){
		mid = low + (high-low)/2;
		if(arr[mid] == temp){
			printf("The number %d is at position %d!\n",temp,mid+1);
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
		printf("Not found");
	}
	
}