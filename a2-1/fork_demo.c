#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	pid_t pid;
	char *msg;
	int n;

	printf("Fork program ....");
	pid = fork();
	switch(pid)
	{
	case -1:
		perror("fork failed");
		exit(1);
	case 0:
		msg="This is a child";
		n=5;
		break;
	default:
		msg="This is the parent";
		n=3;
		break;

	}

	for(;n>0;n--)
	{
		puts(msg);
		sleep(1);
	}
	exit(0);
}