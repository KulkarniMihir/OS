/*
  Mihir Kulkarni
  33132 L9	
  Aim : Demonstrate reader writer problem with counting semaphores and mutex. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TRUE 1
//#define BUFFER_SIZE 5

//int buffer[BUFFER_SIZE];
pthread_mutex_t mutex;	//binary semaphore

sem_t wrt;				//counting semaphore

int nextIn = 0, nextOut = 0;	//count

int numreader = 0, count = 1; 


void *reader()
{
	while(TRUE)
	{
		sleep(1);
		// Reader acquire the lock before modifying numreader
	    pthread_mutex_lock(&mutex);
	    numreader++;
	    if(numreader == 1) {
	        sem_wait(&wrt); // it will block the writer
	    }
	    // other readers can enter while this current reader is inside
	    pthread_mutex_unlock(&mutex);
	    // Reading Section
	    printf("Reader id (%u): read cnt as %d\n",(unsigned int)pthread_self(),count);
		sleep(5);
	    // Reader acquire the lock before modifying numreader
	    pthread_mutex_lock(&mutex);
	    numreader--;
	    if(numreader == 0) {
	        sem_post(&wrt); // It will increment the writer.
	    }
	    pthread_mutex_unlock(&mutex);
	}
}

void *writer()
{
	int item;
	while(TRUE)
	{
		sleep(4);
		// writer requests for critical section
		sem_wait(&wrt);
		int item=2;
	    count = count*item;
	    printf("Writer id (%u) modified cnt to %d by multiplying with %d\n",(unsigned int)pthread_self(),count,item);
	    // leaves the critical section
	    sem_post(&wrt);
	}
}

int main()
{
	//Declaration of inputs
	int readThreads, writeThreads;
	int i, j;
	printf("\n ---READER WRITER PROBLEM---\n");
	//Input
	printf("\nEnter no. of readers :");
	scanf("%d",&readThreads);
	printf("\nEnter no. of writers :");
	scanf("%d",&writeThreads);
	printf("\n");
	
	//Initialization
	pthread_mutex_init(&mutex, NULL);
	//sem_init(&empty, 0, BUFFER_SIZE);
	sem_init(&wrt, 0, 1);

	pthread_t *rid,*wid;
	//Dynamic creation of threads
    rid = (pthread_t*)malloc(readThreads*sizeof(pthread_t));
    wid = (pthread_t*)malloc(writeThreads*sizeof(pthread_t));

	//pthread_t pid[producerThreads], cid[consumerThreads];

	//creating producer and consumer threads
	for(i = 0; i < readThreads; i++){
		pthread_create(&rid[i],NULL,reader,NULL);
	}

	for(j = 0; j < writeThreads; j++){
		pthread_create(&wid[j],NULL,writer,NULL);
	}
	//joining producer and consumer threads
	for(int i = 0; i < readThreads; i++) {
        pthread_join(rid[i], NULL);
    }
    for(int i = 0; i < writeThreads; i++) {
        pthread_join(wid[i], NULL);
    }

    //exit
	pthread_mutex_destroy(&mutex);
	//sem_destroy(&empty);
  	sem_destroy(&wrt);

	return 0;
}
