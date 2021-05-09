/*
	Mihir Kulkarni
	L9 33132
	Aim: Inter-process communication in linux using pipes 
	
*/
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	char filename[50] = "demo.txt";
	char read_msg[50];
	char ch;
	int fd1[2], fd2[2]; 	//fd1[0] - read of parent	fd1[1] - write of parent
	FILE *filePointer;
	pid_t pid;

	if(pipe(fd1) == -1)
	{
		printf("Unable to create pipe 1 \n");
		fprintf(stderr, "\nError while creation");
      	return 1;
	}
	if(pipe(fd2) == -1)
	{
		printf("Unable to create pipe 2 \n");
		fprintf(stderr, "Error while creation\n");
      	return 1;
	}

	pid = fork();

	if(pid<0)
	{
		fprintf(stderr, "Fork failure\n");
		return 1;
	}
	if(pid>0)
	{
		/*Parent Process*/
		//Parent writing to child
		filePointer = fopen("demo.txt","w");
		fprintf(filePointer, "%s","Hello from parent !!\n" );
		fclose(filePointer);
		//closing unwanted ends of pipe(read of parent and write of child)
		close(fd1[0]);
		close(fd2[1]);
		//sending filename through pipe
		write(fd1[1],filename,strlen(filename)+1);
		close(fd1[1]); 
		
		printf("File sent to child\n");

		sleep(2);
		//read from child end
		read(fd2[0], read_msg, 50);
		printf("Parent read the filename %s\n", read_msg);
		//reading file from child
		filePointer = fopen(read_msg,"r");
		ch=fgetc(filePointer);
		while(ch!=EOF)
		{
			printf("%c",ch );
			ch=fgetc(filePointer);
		}
		fclose(filePointer);
		close(fd2[0]);

		wait(NULL);
	}
	else
	{
		//Child Process
		sleep(2);
		//Child reading from file and writing back
		close(fd1[1]);
		read(fd1[0], read_msg, 50);
		printf("Child received filename %s\n", read_msg);
		//open the file and read
		filePointer = fopen(read_msg,"r");
		ch=fgetc(filePointer);
		while(ch!=EOF)
		{
			printf("%c",ch );
			ch=fgetc(filePointer);
		}
		fclose(filePointer);
		//close read end of parent after use
		close(fd1[0]);
		//overwriting the file
		filePointer = fopen(read_msg,"w");
		fprintf(filePointer, "%s","Hello from child !!\n" );
		fclose(filePointer);

		printf("Child sending file to parent\n");
		close(fd2[0]);
		//writing from child end
		write(fd2[1],read_msg,strlen(read_msg)+1);
		close(fd2[1]);
	}

	return 0;

}
