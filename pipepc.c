#include<stdio.h>
#include<unistd.h>
int main() 
{
	int pipefds[2];
	int returnstatus;
	int pipeid;
	char writemessage[2][20]={"Heii","How r uh"};
	char readmessage[20];
	returnstatus = pipe(pipefds);
	if (returnstatus == -1) 
	{
		printf("Unable to create pipe\n");
		return 1;
	}
	pipeid = fork();
	
	if(pipeid==0)
	{
		read(pipefds[0], readmessage, sizeof(readmessage));
		printf("Child process Reading from pipe Message 1 is %s\n", readmessage);
		read(pipefds[0], readmessage, sizeof(readmessage));
		printf("Child process Reading from pipe Message 2 is %s\n", readmessage);
	}
	else
	{
		printf("Parent process Writing to pipe Message 1 is %s\n", writemessage[0]);
        	write(pipefds[1], writemessage[0], sizeof(writemessage[0]));
		printf("Parent process Writing to pipe Message 2 is %s\n", writemessage[1]);
        	write(pipefds[1], writemessage[1], sizeof(writemessage[1]));
		return 0;
	}
}

