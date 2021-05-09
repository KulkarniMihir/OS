#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>

void myturn()
{	
	for(int i=0;i<3;i++)
	//while(1)
	{
		sleep(2);
		printf("My turn\n");
	}
}

void yourturn()
{
	for (int i = 0; i < 5; i++)
	//while(1)
	{
		sleep(2);
		printf("Your turn\n");
	}
}

int main()
{
	pthread_t newThread;
	pthread_create(&newThread,NULL,myturn,NULL);
	yourturn();
	pthread_join(&newThread,NULL);
}