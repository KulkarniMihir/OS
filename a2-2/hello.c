#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	printf("Hello\n");
	printf("PID : %d\n",getpid());
	return 0;
}