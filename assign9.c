#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>

struct student{
	int roll_no;
	char name[20];
	int class;
	float percent;
};

void main(){
	int fd,ch,d,fd2,check,count;
	long int size;
	int class;
	float percent;
	//structure to store data
	struct student s;

	do{
		printf("ENTER THE CHOICE\n\t1.INSERT STUDENT DATA\n\t2.DELETE STUDENT DATA\n\t3.DISPLAY STUDENT DATA\n\t4.SEARCH \n\t5.UPDATE\n\t6.EXIT\n");
		scanf("%d",&ch);
		switch(ch){
			case 1:	//inserting student data in file
				//accepting data
				printf("ENTER THE ROLL NUMBER OF STUDENT\n");
				scanf("%d",&s.roll_no);
				printf("ENTER THE NAME OF THE STUDENT\n");
				scanf("%s",&s.name);
				printf("ENTER THE CLASS OF STUDENT\n");
				scanf("%d",&s.class);
				printf("ENTER THE PERCENT\n");
				scanf("%f",&s.percent);
				//open the file in writing mode
				fd = open("file",O_WRONLY | O_APPEND | O_CREAT,0777);
				if(fd == -1){
					printf("ERROR IN OPENING FILE\n");
					exit(EXIT_FAILURE);
				}
				//insert the data in file
				write(fd,&s,sizeof(struct student));
				close(fd);
				break;

			case 2:
				check = 0;
				fd = open("file",O_RDONLY);
				if(fd == -1){
					printf("ERROR IN OPENING THE FILE\n");
					exit(EXIT_FAILURE);
				}
				fd2 = open("file2", O_RDWR | O_CREAT, 0777);
				if(fd2 == -1){
					printf("ERROR IN OPENING THE FILE\n");
					exit(EXIT_FAILURE);
				}
				printf("Enter the roll no of student whose record is to be deleted\n");
				scanf("%d",&d);
				size = read(fd,&s,sizeof(struct student));
				while(size){
					if(s.roll_no != d){
						write(fd2,&s,sizeof(struct student));
					}else{
						check++;
					}
					size = read(fd,&s,sizeof(struct student));
				}
				close(fd);
				close(fd2);
				remove("file");
				rename("file2","file");
				if(check == 0){
					printf("NO STUDENT HAS THIS ROLL NO\n");
				}else{
					printf("RECORD DELETED SUCCESSFULLY\n");
				}
				break;
				
			case 3:
				//keep reading till end of file
				count = 0;
				fd = open("file",O_RDWR);
				if(fd == -1){
					printf("ERROR IN OPENING FILE\n");
					exit(EXIT_FAILURE);
				}
				size = read(fd,&s,sizeof(struct student));
				while(size){
					printf("***RECORD NO : %d***\n",count);
					printf("roll no : %d\nname : %s\nclass : %d\npercent : %f\n\n",s.roll_no,s.name,s.class,s.percent);
					size = read(fd,&s,sizeof(struct student));
				}
				close(fd);
				break;
				
			case 4:
				check = 0;
				fd = open("file",O_RDONLY);
				if(fd == -1){
					printf("ERROR IN OPENING THE FILE\n");
					exit(EXIT_FAILURE);
				}
				printf("Enter the roll no of student whose record is to be searched\n");
				scanf("%d",&d);
				size = read(fd,&s,sizeof(struct student));
				while(size){
					if(d == s.roll_no){
						printf("roll no : %d\nname : %s\nclass : %d\npercent : %f\n",s.roll_no,s.name,s.class,s.percent);
						check++;
					}
					size = read(fd,&s,sizeof(struct student));
				}
				close(fd);
				if(check == 0){
					printf("NO STUDENT HAS THIS ROLL NO\n");
				}else{
					printf(" STUDENT PRESENT\n");
				}
				break;
				
			case 5:
				check = 0;
				fd = open("file",O_RDWR);
				fd2 = open("file2",O_RDWR | O_CREAT ,0777);
				if(fd == -1){
					printf("ERROR IN OPENING THE FILE\n");
					exit(EXIT_FAILURE);
				}
				if(fd2 == -1){
					printf("ERROR IN OPENING THE FILE\n");
					exit(EXIT_FAILURE);
				}
				printf("Enter the roll no of student whose record is to be updated\n");
				scanf("%d",&d);
				size = read(fd,&s,sizeof(struct student));
				while(size){
					if(d == s.roll_no){
						check++;
						break;
					}
					write(fd2,&s,sizeof(struct student));
					size = read(fd,&s,sizeof(struct student));
				}
				if(check == 0){
					printf("NO STUDENT HAS THIS ROLL NO\n");
				}else{
					printf(" STUDENT PRESENT\n");
					printf("roll no : %d\nname : %s\nclass : %d\npercent : %f\n",s.roll_no,s.name,s.class,s.percent);
					printf("ENTER THE NEW CLASS AND PERCENT\n");
					scanf("%d %f",&class,&percent);
					s.class = class;
					s.percent = percent;
					write(fd2,&s,sizeof(struct student));

					size = read(fd,&s,sizeof(struct student));
					
					while(size){
						write(fd2,&s,sizeof(struct student));
						size = read(fd,&s,sizeof(struct student));
					}
				}
				close(fd);
				close(fd2);
				remove("file");
				rename("file2","file");
				printf("UPDATED SUCCESSFULLY\n");
				break;
				
			case 6:
				break;
			default:
				printf("ENTER VALID INPUT\n");
		}
	}while(ch!=6);
}
