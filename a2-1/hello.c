#include<stdio.h>
#include<unistd.h>

int main()
{
	fork();
	//fork();   
	printf("Hello world!\n"); 
	printf("PID:%d\n",getpid());
	printf("PPID:%d\n",getppid());
	return 0;
}