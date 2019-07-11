#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include <stdlib.h>

void quick_sort(int a[],int l,int r){
	int temp,i,j;
	if(l<r && l>=0){
	    i = l;
		j = r+1;
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

void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    {
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 

int main (void) {
	int n,i,c=0,choice;
	pid_t pid;
	printf("Enter number of elements in array :");
	scanf("%d",&n);
	int arr[n],arr2[n];
	printf("Enter array elements :\n");
	
	for(i=0;i<n;i++){
		scanf("%d",&arr[i]);
		arr2[i] = arr[i];
	}
	
	do{
		printf("ENTER THE CHOICE :\n\t1.SIMPLE CHILD\n\t2.ORPHAN CHILD\n\t3.ZOMBIE\n\t4.EXIT\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				pid = fork();
							//will pass this array to child process
					if(pid == -1){
						//system call fails
						printf("failed to fork\n");	
					}
					if(pid == 0){
						//child process gets created
						printf("CHILD PID: %d PPID : %d \n",getpid(),getppid());
						//perform merge sort
						printf("MERGE SORT OUTPUT\n");
						mergeSort(arr2,0,n-1);
						for(i=0;i<n;i++){
								printf("%d ",arr2[i]);
						}
						printf("\nCHILD PROCESS COMPLETED\n");
					}
					else if(pid > 0){
						printf("PARENT PROCESS ....\n");
						//perform quick sort
						printf("PARENT ID : %d\n",getpid());
						printf("QUICK SORT.....\n");
						quick_sort(arr,0,n-1); 
						printf("QUICK SORT ANSWER :\n");
						for(i=0;i<n;i++){
								printf("%d ",arr[i]);
						}
						printf("\nPARENT COMPLETED\n");
					}
				break;

			case 2:
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
				break;

			case 3:

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
						//wait(NULL);
					}
				break;

			case 4:
				printf("------EXIT-------\n");
				break;

			default:
				printf("ENTER VALID CHOICE\n");
				break;
		}
	}
	while(choice!=4);
}
