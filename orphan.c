#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

void main(){
	pid_t pid;
	pid = fork();
	if(pid==-1){
		//system call fails
		printf("CHILD NOT CREATED\n");	
	}
	if(pid==0){
		printf("CHILD PROCESS IS RUNNING....\n");
		printf("PID OF CHILD : %d PPID OF CHILD : %d \n",getpid(),getppid());
		printf("CHILD WILL SLEEP...\n");
		sleep(10);		//keep child till parent gets completed
		printf("BACK IN CHILD ...\n");
		printf("PID OF CHILD : %d PPID OF CHILD : %d \n",getpid(),getppid());
		exit(0);
	}
	else if(pid>0){
		printf("PARENT RUNNING...\n");
		printf("PARENT COMPLETED...\n");
	}
	printf("END OF PROGRAM..\n");
}
