#include<stdio.h>
#include<stdlib.h>			//for malloc
#include<time.h>			//to calculate the time for a process/program to run

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

void multiply(int *m1,int *m2,int *m3,int r1,int c1,int c2){
	int i,j,k;
	for(i=0;i<r1;i++){
		for(j=0;j<c2;j++){
			for(k=0;k<c1;k++){
				*(m3+c2*i+j) += *(m1+c1*i+k) * *(m2+c2*j+k);
			}
		}
	}
}

void main(){
	int r1,c1,r2,c2;
	int *m1,*m2,*m3;		//will have matrix addresses
	double cpu_time_used=0;
	//declaring clock variables
	clock_t start,end;

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
	//call to multiply 
	multiply(m1,m2,m3,r1,c1,c2);
	printf("Multiplication A and B matrices is :\n");
	printFunc(m3,r1,c2);
	end = clock();
	//calculating the cpu time for multiplication
	cpu_time_used = ((double) (end-start))/CLOCKS_PER_SEC;
	printf("SIMPLE MULTIPLICATION TOOK %f TIME\n",cpu_time_used);

}