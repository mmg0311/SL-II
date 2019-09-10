//	consumer program

#include<stdio.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include <sys/ipc.h>
//include the header file which has the structure 
#include"shmheader.h"

void main(){
	int run=1;
	void *shared_memory = (void *)0;
	struct shared *s;
	int shm_id;
	srand((unsigned int)getpid());
	
	//create a shared memory
	//keys in both the programs (producer and consumer) must be same
	key_t key = 1234;
	shm_id = shmget(key,sizeof(struct shared),0666|IPC_CREAT);
	//IT RETURNS THE ID OF THE SHARED MEMORY CREATED
	
	if(shm_id == -1){
		printf("SHARED MEMORY CREATION FAILED\n");
		exit(EXIT_FAILURE);
	}	
	
	//now to make the shared memory accessesible 
	//attach it to the current process
	shared_memory = shmat(shm_id,(void *)0,0);
	
	//if failed to attach shared memory
	if(shared_memory ==(void *) -1){
		printf("SHARED MEMORY ATTACHMENT FAILED\n");
		exit(EXIT_FAILURE);
	}
	
	printf("MEMORY ATTACHED AT %X\n",(int)shared_memory);
	
	s = (struct shared *)shared_memory;
	s->d = 0;
	while(run) {
		//check if data is written or not 
		if (s->d) {
			//what data is written
			printf("You wrote: %s", s->data);

			/* make the other process wait for us ! */			
			sleep( rand() % 4 ); 
			
			//NOW ONCE AGAIN CHANGE THE FLAG TO FALSE 
			s->d = 0;
			
			//after typing exit we come out from the loop
			if (strncmp(s->data, "exit", 4) == 0) {
				run = 0;
			}
		}
	}
	
	//now detach the shared memory
	if (shmdt(shared_memory) == -1) {
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	
	//to control the shared memory
	//IPC_RMID deletes the shared memory
	if (shmctl(shm_id, IPC_RMID, 0) == -1) {
		fprintf(stderr, "shmctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	
	exit(EXIT_SUCCESS);
	//end of program
}
