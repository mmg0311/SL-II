#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

sem_t wrt,mutex;		//wrt will be used during  reading and writting process
						//mutex or binary semaphore just for locking and unlocking
int buffer;				//for reading and writing purpose
int readcount=0;			//for counting reader
//only one writer may right at a time
//If a writer is writing to the file, no reader may read it.
//Any number of readers may simultaneously read the file
//reader function
void * readerFunc(void *args){
	int p = *(int *)args;
	int temp = rand()%9;
	if(temp == 0){
		temp = 3;
	}
	while(1){
		sleep(temp);
		sem_wait(&mutex);		//lock the area for counting the reader
			readcount++;
			if(readcount == 1){		//if it is first reader
				//then lock the writer
				sem_wait(&wrt);
			}
		sem_post(&mutex);		//unlock this area

		//reading operation is performed here
		printf("\tReader ( %d ) reads data as  ( %d )\n\n",p,buffer);

		sem_wait(&mutex);		//lock the area for exiting of the reader
			readcount--;
			if(readcount == 0){		//if it is last reader
				//then unlock the writer
				sem_post(&wrt);
			}
		sem_post(&mutex);		//unlock this area		
	}
	pthread_exit(NULL);
}

//writer function
void * writerFunc(void *args){
	int p = *(int *)args;
	int temp = rand()%7;
	if(temp == 0){
		temp = 4;
	}
	while(1){
		sleep(temp);
		sem_wait(&wrt);
		//critical section
		buffer = rand()%20;
		printf("Writer ( %d ) is writing ( %d )\n",p,buffer);
		printf("Exit from writer %d \n\n",p);
		//exit form critical section
		sem_post(&wrt);
	}
	pthread_exit(NULL);
}

//main function
int main(){
	int r,w,check,i;
	int *pos;		//to pass which reader or writer to the functions
	pthread_t rT,wT;
	printf("Enter the number of 'Writers' : ");
	scanf("%d",&w);
	printf("Enter number of 'Readers' : ");
	scanf("%d",&r);

	//initialization of semaphores
	check = sem_init(&wrt,0,w+1);
	if(check != 0){
		printf("Semaphore initialization failed\n");
		exit(EXIT_FAILURE);
	}
	//initialization of binary semaphore
	check = sem_init(&mutex,0,1);
	if(check!=0){
		printf("Binary semaphore initialization failed\n");
		exit(EXIT_FAILURE);
	}

	//CREATING THREADS
	for(i=0;i<w;i++){
		pos = (int *)malloc(sizeof(int));
		* pos = i;
		printf("Creating writer thread  :: %d \n",i);
		check = pthread_create(&wT,NULL,writerFunc,pos);
		if(check != 0){
			printf("Thread creation failed\n");
		}
	}
	for(i=0;i<r;i++){
		pos = (int *)malloc(sizeof(int));
		* pos = i;
		printf("Creating reader thread  :: %d \n",i);
		check = pthread_create(&rT,NULL,readerFunc,pos);
		if(check != 0){
			printf("Thread creation failed\n");
		}
	}

	//JOINING THREADS
	check = pthread_join(wT,NULL);
	if(check!=0){
		printf("Joining of writers threads failed\n");
	}
	check = pthread_join(rT,NULL);
	if(check !=0)
	{
		printf("Joining of readers threads failed\n");
	}

	//destroy the threads
	sem_destroy(&wrt);
	sem_destroy(&mutex);
	printf("Destroyed threads\n Now exiting main program");
	return 0;
}