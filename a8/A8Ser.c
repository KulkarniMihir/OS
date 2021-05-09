#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>

int main(){
	
	// ftok to generate unique key 
	// convert a pathname and a project identifier to a System V IPC key
    key_t key=ftok("a8",8);
    
    // shmget creates shared memory and returns an identifier in shmid 
    int shmid=shmget(key,1024,0666|IPC_CREAT);	//1024 - size
	
    // shmat to attach to shared memory  and gain access
    char *str=(char*) shmat(shmid,(void*)0,0);
	if (shmid == -1) {
	      perror("Could not get shared memory");     
	}
    printf("Enter Account Details(Name - Account balance): \n");
    gets(str);
    printf("Fine\n");
    //detach from shared memory  
    shmdt(str);
   
    return 0;
}
