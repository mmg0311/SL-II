#include<stdio.h>
#include<stdlib.h>			//for malloc
#include<time.h>			//to calculate the time for a process/program to run
#include<pthread.h>

struct parameters{
    int i,j,c;
};

int *m1,*m2,*m3;		//will have matrix addresses

void inputFunc(int *m,int r,int c){
	int i,j;
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
				printf("[%d][%d] : ",i,j);
				scanf("%d",(m+c*i+j));
		}	
	}

}

void printFunc(int *m,int r,int c){
	int i,j;
	for(i=0;i<r;i++){
		printf("{ ");
		for(j=0;j<c;j++){
				printf("%d ",*(m+c*i+j));
		}	
		printf(" }\n");	
	}

}

void * multiply(void *args){
    int k;
	struct parameters *p = args;
    //take the values from the structure ....
	*(m3 + p->i*p->c + p->j)=0;
	for (k = 0; k < p->c; k++){     
		*(m3 + p->i*p->c + p->j)  +=  *(m1 + p->i*p->c + k) * *(m2 + k*p->c + p->j);
	}
	pthread_exit("EXITING FROM MULTIPLICATION FUNCTION\n");
}

void main(){
	int r1,c1,r2,c2,check,i,j,k;
	double cpu_time_used=0;
	//declaring clock variables
	clock_t start,end;

    //declaring thread
    pthread_t *T;

    //struct pointer
    struct parameters *p;

	//	taking row number and column number
	printf("Enter the number of rows for matrix A : ");
	scanf("%d",&r1);
	printf("Enter the number of columns for matrix A : ");
	scanf("%d",&c1);
	printf("Enter the number of rows for matrix B : ");
	scanf("%d",&r2);
	printf("Enter the number of columns for matrix B : ");
	scanf("%d",&c2);

	if(r2 != c1){
		printf("Multiplication cannot be preformed \n");
		exit(0);
	}

	//taking the input matrices
	//allocating memory
	m1 = (int *) malloc(r1*c1*sizeof(int));
	m2 = (int *) malloc(r2*c2*sizeof(int));
	m3 = (int *) calloc(r1*c2,sizeof(int));		//to initialize to zero 
    T = (pthread_t *) malloc(r1*c2*sizeof(pthread_t));
	//taking input of matrices
	printf("For matrix  A :\n");
	inputFunc(m1,r1,c1);
	printf("Matrix A : \n");
	printFunc(m1,r1,c1);
	printf("For matrix  B :\n");
	inputFunc(m2,r2,c2);
	printf("Matrix B : \n");
	printFunc(m2,r2,c2);

	//start the clock 
	start = clock();
    //creating threads
    for (i = 0; i < r1; i++) 
        for (j = 0; j <c2; j++){
            p = (struct parameters*)malloc(sizeof(struct parameters));
            p->i=i;
            p->j=j;
            p->c=c2;
            check = pthread_create((T+i*c2+j),NULL,multiply,p);
            // check for thread creation failure
            if (check != 0) {
                printf("Thread creation failed");
                exit(EXIT_FAILURE);
            }
	}
	//call to multiply 
	// multiply(m1,m2,m3,r1,c1,c2);
    //now joining the threads
    printf("Now joining the threads\n");
    for (i = 0; i < r1; i++) 
		for (j = 0; j <c2; j++){
			check = pthread_join(*(T+i*c2+j), NULL);	
			// check for thread join failure
			if (check != 0) {
				printf("Thread join failed");
				exit(EXIT_FAILURE);
			}
	}

    printf("Multiplication A and B matrices is :\n");
	printFunc(m3,r1,c2);
    
	end = clock();
	//calculating the cpu time for multiplication
	cpu_time_used = ((double) (end-start))/CLOCKS_PER_SEC;
	printf("MULTITHREAD MULTIPLICATION TOOK %f TIME\n",cpu_time_used);

}