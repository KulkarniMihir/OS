#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	printf("I am execv demo\n");
	printf("PID : %d\n",getpid());
	char *args[] = {"./hello",NULL};
	execv(args[0],args);
	printf("Coming back to demo \n");	//will not execute
	return 0;
}