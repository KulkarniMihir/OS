#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<malloc.h>
#include<semaphore.h>

void *thread_function(void *arg);
sem_t bin_sem;
#define work_size 1024
char work_area[work_size];

int main()
{
	int res;
	pthread_t a_thread;
	void *thread_result;

	res = sem_init(&bin_sem, 0, 0);
	if(res!=0)
	{
		perror("Semaphore initialization failed");
		exit(EXIT_FAILURE);
	}
	res = pthread_create(&a_thread, NULL, thread_function, NULL);
	if(res!=0)
	{
		perror("Semaphore creation failed");
		exit(EXIT_FAILURE);
	} 
	printf("Input some text. Enter 'end' to finsih\n");
	while(strncmp("end", work_area, 3) != 0)
	{
		fgets(work_area, work_size, stdin);
		sem_post(&bin_sem);
	}
	printf("\nWaiting for thread to finish.....");
	res = pthread_join(a_thread, &thread_result);
	if(res != 0)
	{
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined\n");
	sem_destroy(&bin_sem);
	exit(EXIT_FAILURE);
}

void *thread_function(void *arg) 
{
	sem_wait(&bin_sem);
	while(strncmp("end", work_area, 3) != 0)
	{
		printf("You input %ld characters\n",strlen(work_area) -1);
		sem_wait(&bin_sem);
	}
	pthread_exit(NULL);
}