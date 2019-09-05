#include<stdio.h>
#include<sys/types.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#define max 10
#define left  (num+n-1)%n
#define right  (num+1)%n

int n;      //number of philosophers
sem_t mutex;        //for locking pickup and putdown
sem_t p[max];         //semaphore for each philosopher
enum state{THINKING = 1,HUNGRY,EATING}; //states of philosophers
enum state s[max];                    //to store state of each philosopher
int philno[max];                //storing philosopher number

void test(int num){

    //if neighbours are not eating
    if(s[num] == 2 && s[left] != 3 && s[right] != 3){
        //change state to eating
        s[num] = 3;
        sleep(2);
        printf("PHILOSOPHER %d IS EATING\n",num);
        printf("CHOPSTICKS TAKEN (%d,%d)\n",num,num+1);
        sem_post(&p[num]);
    }
}

void put_down(int num){
    sem_wait(&mutex);
    //change state to thinking 
    s[num] = 1;
    printf("PHILOSOPHER  %d IS PUTTING HIS CHOPSTICK\n",num);
    printf("CHOPSTICKS PUTDOWN (%d,%d)\n",num,num+1);
    printf("PHILOSOPHER %d IS THINKING\n",num);
    test(left);
    test(right);
    sem_post(&mutex);
}

void pick_up(int num){
    sem_wait(&mutex);
        //change the state to hungry
        s[num] = 2;
        printf("HUNGRY : %d\n",num);
        //check for neighbours
        test(num);
    sem_post(&mutex);
    // for making a queue of philosophers
    sem_wait(&p[num]);
    sleep(3);
}

void * phil(void * arg){
    while(1){        //run infinite number of times
        int *pos = arg;
        //pick up chopstick
        sleep(1);
        pick_up(*pos);
        //put down chopstick
        sleep(4);
        put_down(*pos);
    }
}

void main(){
    int check,i;
    pthread_t *pth;
    printf("ENTER NUMBER OF PHILOSOPHERS : ");
    scanf("%d",&n);
    //initialize the mutex
    check = sem_init(&mutex,0,1);
    if(check != 0){
        printf("SEMAPHORE INITIALIZATION FAILED\n");
        exit(EXIT_FAILURE);
    }
    //initializing semaphores of philosophers
    for(i=0;i<n;i++){
            philno[i] = i+1;
            check = sem_init(&p[i],0,0);
            if(check != 0){
                printf("SEMAPHORE INITIALIZATION FAILED\n");
                exit(EXIT_FAILURE);
            }
    }
    //allocating memory to threads
    pth = (pthread_t *)malloc(sizeof(pthread_t)*n);
    //create threads
    for(i=0;i<n;i++){
        check = pthread_create((pth+i),NULL,phil,&philno[i]);
        if(check != 0){
            printf("THREAD CREATION FAILED\n");
            exit(EXIT_FAILURE);
        }
        printf("PHILOSOPHER %d IS THINKING\n",i+1);
    }
    //joining threads
    for(i=0;i<n;i++){
        check = pthread_join(*(pth+i),NULL);
        if(check !=0){
            printf("THREAD JOIN FAILED\n");
            exit(EXIT_FAILURE);
        }
    }
    //program finished
}
