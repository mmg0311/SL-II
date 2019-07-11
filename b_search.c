#include<stdio.h>
#include<string.h>
#include<math.h>
int binary_search(int arr[],int l,int r,int d){
	int m;
	while(l<=r){
		m = l+(r-1);
		m = m/2;
		if(arr[m]<d){
			//use the right side
			l = m+1;
		}
		else if(arr[m]>d){
			//use the left side
			r = m-1;
		}
		else{
			return arr[m];
		}
	}
	return -1;		//search is unsuccessfull
}


//we will pass the string buffer and data to be searched
//i.e	argc = 3
//argv[0] = filename , argv[1] = buffer 
int main(int argc,char* argv[],char *envp){
	int arr[argc-1],d,i;	//cause first position has exec. file
	for(i=1;i<argc;i++){
		arr[i-1] = atoi(argv[i]);
	}
		printf("ENTER THE DATA TO BE SEARCHED : ");
		scanf("%d",&d);
		binary_search(arr,0,argc-1,d);
	return 0;
}
