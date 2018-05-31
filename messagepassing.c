#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

int number;
int square;
pid_t pid;

void main() 
{
    number = rand()%10;

	int fd[2];
	int fdd[2];
	int status = 0;
    if(pipe(fd)==-1){
        printf("Error while creating pipe");
        exit(-1);
    }
	if(pipe(fdd)==-1){
        printf("Error while creating pipe");
        exit(-1);
    }

    pid = fork();

	if(pid == 0) 
	{		/*Child */
	
		read(fd[0], &number, sizeof(int)+1);
        //close(fd[0]);
        square = number * number;
		printf("child: Parent generated the number %d \n", number);

		write(fdd[1], &square, sizeof(int)+1);
        //close(fd[1]);
		exit(status);
        
	}	
	else if(pid>0)
	{      /*Parent */

        //write the initial number
		write(fd[1], &number, sizeof(int)+1);
        //close(fd[1]);
		
		wait(0);
		read(fdd[0], &square, sizeof(int)+1);
		printf("parent: Child generated the square %d \n", square);
		//close(fd[0]);

	}else{
        printf("error while forking");
        exit(-1);
    }


}
