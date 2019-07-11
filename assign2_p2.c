#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void main(){
	int choice;
	do{
		printf("\nENTER CHOICE\n\t1.ZOMBIE\n\t2.ORPHAN\n\t3.EXIT\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
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
					wait(NULL);
				}
				printf("NOW CASE 1 BREAK...\n");
			break;
			
			case 2:
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
				}
				else if(pid>0){
					printf("PARENT RUNNING...\n");
					printf("PARENT COMPLETED...\n");
				}
			break;
			
			case 3:
			
			break;
		}
	}
	while(choice!=3);
}
