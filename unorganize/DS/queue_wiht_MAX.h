// queue with max query
#define N 128
int queue[N],vptr[N];
int front,rear,cnt;
void init(){ 
	memset(vptr,0,sizeof(0));
	front=rear=cnt=0;}
int max(){ return queue[front];}
void pop(){
	if(vptr[front]==1){
		front++;
		cnt--;
	}else{ 
		vptr[front]--,cnt--;
	}
}
void push(int x){
	cnt++;
	int del=1;
	while(rear>front&&queue[rear-1]<x){
		rear--;
		del+=vptr[rear];
	}
	vptr[rear]=del;
	queue[rear++]=x;
}