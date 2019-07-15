
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void print(int ar[],int n){
	int i;
	printf("{ ");
	for(i=0;i<n;i++){
		printf("%d ",ar[i]);
	}
	printf(" }\n\n");
	
}




void quick_sort(int a[],int l,int r){
	int temp,i,j;
	if(l<r && l>=0){
	    i = l;
		j = r;
		while(i<j){
			while(a[i]<a[l] && i<r){
				i++;
			}
			while(a[j]>a[l] && j>0){
				j--;
			}
			if(i<j){
				//swap
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
		temp = a[j];
		a[j] = a[l];
		a[l] = temp;
		quick_sort(a,l,j-1);
		quick_sort(a,j+1,r);
	}
}


void main(){
	int n,i;
	//buffer used so that the array can be passed in second program
	//char * buffer = (char *)malloc(sizeof(char)*20);
	
	printf("IN MAIN OF FIRST PROG.....\n");
	printf("ENTER THE SIZE OF ARRAY\n");
	scanf("%d",&n);
	int arr[n];
	char * buffer[n+2];
	
	printf("ENTER THE ELEMENTS OF ARRAY\n");
	for(i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	
	printf("THE ARRAY IS : \n");
	print(arr,n);
	
	quick_sort(arr,0,n-1);
	printf("THE ARRAY IS AFTER SORT : \n");
	print(arr,n);
	
	pid_t pid;
	pid = fork();	//making child
	if(pid==0){
		//child process 
		printf("IN CHILD....\n");
		
		printf("THE ARRAY IS : \n");
		print(arr,n);
		
		printf("USING SPRINTF.....\n");
		
		//strcpy(buffer,"./b");
		buffer[0] = "./b";
		
		for(i=0;i<n;i++){
			buffer[i+1] = (char *)malloc(7);
			sprintf(buffer[i+1],"%d",arr[i]);
		}
		buffer[i+1] = NULL;
		execv("./b",buffer);
		//execve("./b",buffer,NULL);
	}
	else if(pid > 0){
		printf("IN THE PARENT PROCESS ...\n");
		wait(NULL);	//will wait till child executes
		printf("AFTER CHILD EXECUTION...\n");
	}
	printf("END OF MAIN\n");
	
}
