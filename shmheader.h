#define size 50
struct shared{
	int d;				//to decide  data is written in producer or not
						//if written d= 1
						//else d=0
	char data[size];
};
