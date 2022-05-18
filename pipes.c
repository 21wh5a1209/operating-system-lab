#include<stdio.h>
#include<unistd.h>
int main()
{
	int pipefds1[2],pipefds2[2];
	int returnstatus1,returnstatus2;
	int pipeid;
	char pipe1writemessage[50] = "OPERATING";
	char pipe2writemessage[50] = "SYSTEM";
	char readmessage[50];
	returnstatus1 = pipe(pipefds1);
	if(returnstatus1 == -1)
	{
		printf("unable to create a pipe1\n");
		return 1;
	}
	returnstatus2 = pipe(pipefds2);
	if(returnstatus2 == -1)
	{
		printf("unable to create a pipe2\n");
		return 1;
	}
	pipeid = fork();


	if (pipeid != 0) 
	{
		close(pipefds1[0]); 
		close(pipefds2[1]); 
		printf("Parent process - Writing to pipe1 Message is %s\n", pipe1writemessage);
		write(pipefds1[1], pipe1writemessage, sizeof(pipe1writemessage));
		read(pipefds2[0], readmessage, sizeof(readmessage));
		printf("Parent process - Reading from pipe2 Message is %s\n", readmessage);
	}
       	else 
	{ 
		close(pipefds1[1]); 
		close(pipefds2[0]);
		read(pipefds1[0], readmessage, sizeof(readmessage));
		printf("Child process - Reading from pipe1 – Message is %s\n", readmessage);
		printf("Child process - Writing to pipe2 – Message is %s\n", pipe2writemessage);
		write(pipefds2[1], pipe2writemessage, sizeof(pipe2writemessage));
	}
	return 0;
}




