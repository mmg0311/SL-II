#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

void main(){
	pid_t pid;
	pid =fork();
	if(pid==-1){
		//system call fails
		printf("CHILD NOT CREATED");
	}	
	if(pid==0){
		//child process
		printf("CHILD PROCESS GETS CREATED\n");
		printf("PID OF CHILD : %d PPID OF CHILD:%d\n",getpid(),getppid());
		sleep(1);
		printf("IN ZOMBIE STATE ...\n");
		
	}
	else if(pid>0){
	//parent process
		printf("PARENT IS RUNNING....\n");
		printf("PARENT GOES TO SLEEP...\n");
		sleep(10);
		printf("PARENT AFTER SLEEP...\n");
		//wait(NULL);
	}
	printf("PROGRAM END...\n");
	
}
