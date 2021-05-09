/*
  Mihir Kulkarni
  33132 L9	
  A solution to the producer-consumer problem with a bounded-buffer using counting semaphores and mutex
  locks, for a number of threads provided by user.
*/
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

#define BufferSize 4
#define FULL 0
#define EMPTY 0
int buffer[BufferSize];
int nextIn = 0;
int nextOut = 0;

sem_t empty;	//produce
sem_t full;		//consume 
//sem_t mutex;

void * Producer()
{
  int i=0;
  //for(i = 0; i < 10; i++)
  while(1)
    {
      	int item=rand()%10;

 	  	sem_wait(&empty); //get the mutex to fill the buffer
 	  	//sem_wait(&mutex);
  		buffer[nextIn] = item;
  		printf("Producer %d, nextIn %d, item %d\n",(i++)%4,nextIn,item);
  		nextIn = (nextIn + 1) % BufferSize;
  		if(nextIn==FULL)
    	{
      		sem_post(&full);
      		//sleep(5);
    	}
  		sem_post(&empty);
  		sleep(5);
  		//sem_post(&mutex);
    }
}

void * Consumer()
{
  int i=0;
  //for(i = 0; i < 10; i++)
  while(1)
    {
  		sem_wait(&full); // gain the mutex to consume from buffer
  		//sem_wait(&mutex);
  		int item = buffer[nextOut];
  		printf("\tConsumer %d, nextOut %d, item %d\n",(i++)%4,nextOut,item);
  		nextOut = (nextOut + 1) % BufferSize;
  		
  		if(nextOut==EMPTY) //its empty
    	{
      		//sleep(5);
    	}

  		sem_post(&full);
  		sleep(1);
  		//sem_post(&mutex);
    }
}

int main()
{
  	pthread_t ptid,ctid;
  	//initialize the semaphores

  	sem_init(&empty,0,1);
  	sem_init(&full,0,0);
  	//sem_init(&mutex,0,1);
  	//creating producer and consumer threads

  	if(pthread_create(&ptid, NULL,Producer, NULL))
    {
      printf("\n ERROR creating thread 1");
      exit(1);
    }

  	if(pthread_create(&ctid, NULL,Consumer, NULL))
    {
      printf("\n ERROR creating thread 2");
      exit(1);
    }

    //joining producer and consumer threads

  	if(pthread_join(ptid, NULL)) /* wait for the producer to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

  	if(pthread_join(ctid, NULL)) /* wait for consumer to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

  	sem_destroy(&empty);
  	sem_destroy(&full);
  	//sem_destroy(&mutex);
  	//exit the main thread

  	pthread_exit(NULL);
  	return 1;
}