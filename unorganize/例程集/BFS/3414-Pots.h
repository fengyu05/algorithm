// 3414 Pots
// fengyu05
// PotsÓÎÏ·
// BFS+×´Ì¬±íÊ¾
#include <iostream>
using namespace std;

#define N 100
const int L= 128*128;

struct State{ 
	int x,y;
	State(int x=0,int y=0):x(x),y(y){}
	operator int() const{ return x*N+y; }
};
Queue<State> open;
int Pred[L],Act[L],path[100],p_cnt,tar;

int p[4],cap[4];
void init(){ for(int i=0;i<L;i++) Pred[i]=-1;} 
void FILL(int i){  p[i]=cap[i];}
void DROP(int i){  p[i]=0;}
int cntp(int i){ if(i==1) return 2;else return 1;}
void POUR(int x,int y){
	int dif=cap[y]-p[y];
	if(dif>p[x]){
		p[y]+=p[x];
		p[x]=0;
	}else{
		p[x]-=dif;
		p[y]=cap[y];
	}
}
void load(State& x){ p[1]=x.x,p[2]=x.y;}
void save(State& x){ x.x=p[1],x.y=p[2];}
bool end(State& x){
	if(x.x==tar||x.y==tar) return true;
	else return false;
}
bool search(){
	bool found=false;
	open.init(),init();
	open.push(State(0,0));
	Pred[0]=0;
	State T;
	while(open.size()&&!found){
		State cur=open.pop(),nxt;
		for(int i=0;i<6;i++){
			load(cur);
			int a=(i%2)+1;
			int b=cntp(a);
			if(i<2) FILL(a);
			else if(i<4) DROP(a);
			else POUR(a,b);
			save(nxt);
			int id_nxt=nxt;
			if(Pred[nxt]==-1){
				Pred[nxt]=cur;
				Act[nxt]=i;
				if(end(nxt)){
					T=nxt;
					found=true;
				}else
					open.push(nxt);
			}
		}
	}
	if(found){
		int tmp=T;
		p_cnt=0;
		while(tmp!=0){
			path[p_cnt++]=Act[tmp];
			tmp=Pred[tmp];
		}
	}
	return found;
}
int main()
{
	scanf("%d%d%d",&cap[1],&cap[2],&tar);
	/*
	FILL(2);
	POUR(1,2);
	DROP(2);
	POUR(1,2);
	FILL(2);
	POUR(1,2);
	//*/
	///*
	bool re=search();
	if(re){
		printf("%d\n",p_cnt);
		for(int i=p_cnt-1;i>=0;i--){
			int a=(path[i]%2)+1;
			int b=cntp(a);
			if(path[i]<2) printf("FILL(%d)\n",a);
			else if(path[i]<4) printf("DROP(%d)\n",a);
			else printf("POUR(%d,%d)\n",a,b);
		}
	}else printf("impossible\n");
	//*/
	return 0;
}