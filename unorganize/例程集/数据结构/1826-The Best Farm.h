/* 1826 The Best Farm
 * 21032K	2907MS	C++	2118B
 * 
 * 链式HashTable +BFS
 */
#include<iostream>
#include<deque>
using namespace std;
#define N 1047291

int Hash(int x,int y){
	return (((x*98909+y*87943)%N)+N)%N;
}
/*
char tt[N];
void test_hash(){
	int n=200000;
	int cnt=0,cas=n;
	while(cas--){
		int x=(rand()%N)*((rand()%2==0)?-1:1);
		int y=(rand()%N)*((rand()%2==0)?-1:1);
		int id=Hash(x,y);
		if(tt[id]==0){
			tt[id]=1;
		}else cnt++;
	}
	printf("%.4lf\n",(double)cnt/n);
	return;
}//*/
struct state{
	short val;
	int x,y;
	state(int x=0,int y=0,short val=0):
		x(x),y(y),val(val){}
	operator int() const{ return val; }
}; state null;
struct node{
	short val;
	int x,y;
	node* next;
	node(int x,int y,short val,node* next=0)
		:x(x),y(y),val(val),next(next){}
};
typedef node* link;
link hash[N];

void init(){
	memset(hash,0,sizeof(hash));
}
void insert(int x,int y,int val){
	int id=Hash(x,y);
	hash[id]=new node(x,y,val,hash[id]);
}
state find_del(int x,int y){
	int id=Hash(x,y);
	link p=0;
	for(link lk=hash[id];lk;lk=lk->next){
		if(lk->x==x&&lk->y==y){
			int val=lk->val;
			if(p==0){//front
				hash[id]=lk->next;
			}else p->next=lk->next;
			delete lk;
			return state(x,y,val);
		}
		p=lk;
	}return null;
}
int of[4][2]={
	0,-1,
	-1,0,
	0,1,
	1,0
};
int main()
{	
	test_hash();
	int n;
	while(scanf("%d",&n),n){
		init();
		deque<state> lis;
		for(int i=0;i<n;i++){
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			lis.push_back(state(x,y,z));
			insert(x,y,z);
		}
		int _max=0;
			while(lis.size()){//对每个点BFS
				state ss=lis.front();
				lis.pop_front();
				deque<state> que;
				//BFS
				state S=find_del(ss.x,ss.y);
				if(S!=0) que.push_back(ss);
				int re=0;
				while(que.size()){
					state cur=que.front();
					que.pop_front();
					re+=cur.val;
					for(int i=0;i<4;i++){
						int nx=cur.x+of[i][0];
						int ny=cur.y+of[i][1];
						state next=find_del(nx,ny);
						if(next!=0)
							que.push_back(next);
					}
				}
				if(re>_max) _max=re;
			}
		printf("%d\n",_max);
	}
	return 0;
}