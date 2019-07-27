#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/types.h>

sem_t full,empty,binary;		//declaring semaphore


void * producer(void *args){		//will pass number of arguments
	printf("IN PRODUCER...\n");
	while(1){
		
		sem_wait(&empty);
		sem_wait(&binary);
		
		printf("HELLO FROM PRODUCER...\n");
		
		sem_post(&binary);
		sem_post(&full);
	}

}

void * consumer(void *args){		//will pass number of arguments
	printf("IN CONSUMER...\n");
	while(1){

		sem_wait(&full);
		sem_wait(&binary);
		
		printf("HELLO FROM CONSUMER...\n");
		
		sem_post(&binary);
		sem_post(&empty);
	}
}

void main(){
	int buffer,err;

	pthread_t *thread1,*thread2;		//declaration of thread
	pthread_mutex_t mutex;		//declaration of mutex
	int pshared;	//wheather semaphore is shared between the threads i.e = 0
					//or shared between the processes i.e != 0
	err = sem_init(&binary,0,1);
	sem_init(&full,0,3);
	sem_init(&empty,0,0);
	
	thread1 = (pthread_t *) malloc(sizeof(pthread_t));
	thread2 = (pthread_t *) malloc(sizeof(pthread_t));
	
	err = pthread_create(thread1,NULL,producer,NULL);
	if(err!=0){
		printf("THREAD CREATION FAILED...\n");
		exit(EXIT_FAILURE);
	}

	err = pthread_create(thread2,NULL,consumer,NULL);
	if(err!=0){
		printf("THREAD CREATION FAILED...\n");
		exit(EXIT_FAILURE);
	}

	err = pthread_join(*thread1, NULL);	
			// check for thread join failure
			if (err != 0) {
				printf("Thread join failed");
				exit(EXIT_FAILURE);
			}
	err = pthread_join(*thread2, NULL);	
			// check for thread join failure
			if (err != 0) {
				printf("Thread join failed");
				exit(EXIT_FAILURE);
			}
	printf("PROGRAM FINISHED...\n");
	
}
