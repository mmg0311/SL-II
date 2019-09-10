//		PRODUCER PROGRAM

#include<stdio.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include <sys/ipc.h>
//include the header file which has the structure 
#include"shmheader.h"


int main()
{
	int running = 1;
	void *shared_memory = (void *)0;
	struct shared *shared_stuff;
	char buffer[50];
	int shmid;
	//create a shared memory
	//keys in both the programs (producer and consumer) must be same
	key_t key = 1234;
	shmid = shmget(key, sizeof(struct shared), 0666 | IPC_CREAT);
	//IT RETURNS THE ID OF THE SHARED MEMORY CREATED
	
	if (shmid == -1) {
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}
	
	//now to make the shared memory accessesible 
	//attach it to the current process
	shared_memory = shmat(shmid, (void *)0, 0);
	if (shared_memory == (void *)-1) {
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Memory attached at %X\n", (int)shared_memory);
	shared_stuff = (struct shared *)shared_memory;
	
	while(running) {
		//this loop will make the program wait for data to be read by the client
		while(shared_stuff->d == 1) {
			sleep(1);
			printf("waiting for client...\n");
		}
		//taking the data
		printf("Enter some text: ");
		//fgets used just to take whole line as input of length upto 50
		fgets(buffer, 50, stdin);
		
		//writing the data from variable in structure
		strncpy(shared_stuff->data, buffer, 50);
		//to signal that the data is written
		shared_stuff->d = 1;
		//after typing exit we come out from the loop
		if (strncmp(buffer, "exit", 4) == 0) {
			running = 0;
		}
	}
	
	//now detach the shared memory
	if (shmdt(shared_memory) == -1) {
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
