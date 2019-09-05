/*#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

void main(){
	pid_t p;
	int fd[2];
	char msg[10]  = "hello";
	char msgpassed[10];
	p = fork();
	if(pipe(fd) == -1){
		//if failed to create pipe
		printf("ERROR IN CREATING PIPE\n");
		exit(EXIT_FAILURE);
	}
	if(p == -1){
		//system call failed
		printf("FAILES TO FORK\n");
		exit(EXIT_FAILURE);
	}
	if(p == 0){
		//child process gets created
		sleep(2);
		close(fd[1]);	//close the writing part		
		read(fd[0],msgpassed,10);
		printf("MSG PASSED :%s",msgpassed);
		printf("\nCHILD PROCESS COMPLETED\n");
		close(fd[0]); 	//close the reading part
	}
	else if(p > 0){
		//parent process
		close(fd[0]);	//close the reading part
		write(fd[1],msg,10);
    	printf("\nPARENT COMPLETED\n");
    	close(fd[1]);	//close writing part
	}
}*/
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1
int main(void)
{
	/*char write_msg[BUFFER_SIZE]="hello";
	char read_msg[BUFFER_SIZE];
	char write_msg1[BUFFER_SIZE]="world";
	char read_msg1[BUFFER_SIZE];*/
	FILE *file;

	int fd[2],fd1[2];
	pid_t pid;
	if (pipe(fd) == -1) {
		fprintf(stderr,"Pipe failed");
		return 1;
	}
	if(pipe(fd1) == -1){
		fprintf(stderr,"Pipe failed");
		return 1;
	}
	pid = fork();
	if (pid < 0) { 
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	if (pid > 0) { //parent process
		close(fd[READ_END]);		//closing reading end of 1st pipe
		//close(fd1[WRITE_END]);		//closing write end of 2nd pipe
		file = fopen("hello.txt","w");		//opening in write mode
		//write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
		
		sleep(1);
		
		//read(fd1[READ_END],read_msg1,BUFFER_SIZE);
		//printf("%s",read_msg1);
		close(file);
		close(fd[READ_END]);		//closing the reading end of 1st pipe
		//close(fd1[WRITE_END]);		//closing the writing end of 2nd pipe
	}
	else { //child process
		close(fd[WRITE_END]);	//closing wirting end of 1st pipe
		//close(fd1[READ_END]);	//closing reading end of 2nd pipe
		file = fopen("hello.txt","r");
		
		//read(fd[READ_END], read_msg, BUFFER_SIZE);
		//printf (" %s", read_msg) ;
		
		//write(fd1[WRITE_END],write_msg1,strlen(write_msg1)+1);
		close(file);
		close(fd[READ_END]);		//closing the reading end of 1st pipe
		//close(fd1[WRITE_END]);		//closing the writing end of 1st pipe

	}
return 0;
}
