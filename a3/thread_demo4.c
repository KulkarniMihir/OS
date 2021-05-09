#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<malloc.h>

void myturn(void *arg)
{	
	int *iptr;
	iptr = (int *)malloc(sizeof(int));
	iptr=(int *) arg;
	for(int i=0;i<3;i++)
	//while(1)
	{
		sleep(1);
		printf("My turn and id : %d\n",*iptr);
		(*iptr)++;
		//printf("My turn and id :%d\n",*iptr);

	}
	return NULL;
}

void yourturn()
{

	for (int i = 0; i < 5; i++)
	//while(1)
	{
		sleep(2);
		printf("Your turn\n");
	}
	return NULL;
}

int main()
{
	int *temp;
	temp = (int *)malloc(sizeof(int));
	*temp=10;
	pthread_t newThread;
	pthread_create(&newThread,NULL,myturn,(void *)temp);
	yourturn();
	pthread_join(&newThread,NULL);
}