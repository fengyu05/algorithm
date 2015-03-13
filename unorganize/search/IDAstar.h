// DFSID -> IDA* (IDA* 可由迭代加深DFS改进)

//--------------- IDA* on 8digit -----------------------
// sicily 1379
//IDA*, stack + 判重
#include <iostream>
using namespace std;

#define L 362880
int ar_to_int(int p[]){
	int re=p[0];
	for(int i=1;i<9;i++){
		re=(re*10)+p[i];
	}
	return re;
}
void int_to_ar(int code,int p[]){
	int pos=8;
	while(pos>=0){
		p[pos--]=code%10;
		code/=10;
	}
}
int HASH[L];
int encode(int p[]){
	int re=0,fc=1;
	for(int i=1;i<9;i++){
		fc*=i;
		int inv=0;
		for(int j=0;j<i;j++)
			if(p[j]>p[i]) inv++;
		re+=fc*inv;
	}
	HASH[re]=ar_to_int(p);
	return re;
}
int decode(int code){
	// sloth function, use only fater encode
	return HASH[code];
}
int findpos(int p[]){
	for(int i=0;i<9;i++)
		if(p[i]==0) return i;
	return -1;
}
int ofs[9][4]={
	-1, 1,3,-1,  
	-1, 2,4,0,
	-1,-1,5,1,
	0,4,6,-1,
	1,5,7,3,
	2,-1,8,4,
	3,7,-1,-1,
	4,8,-1,6,
	5,-1,7,-1
}; 
struct State{ 
	int id;
	State(){}
	State(int p[9]){
		id=encode(p);
	}
	operator int() const{ return id; }
};
int Hamilton(int a,int b){
	int x1=a/3,x2=b/3;
	int y1=a%3,y2=b%3;
	return abs(x1-x2)+abs(y1-y2);
}
int h(int code){
	int p[10];
	int_to_ar(code,p);
	int re=0;
	for(int i=0;i<9;i++){
		re+=Hamilton((p[i]+8)%9,i);
	}
	return re; 
} 
State stack[L];
int IDAstar(State S,State T){
	if(S==T) return 0;
	int Dmax=h(decode(S));
	do{
		char G[L];
		memset(G,-1,sizeof(G));
		int top=0;
		stack[top++]=S,G[S]=0;
		while(top>0){
			State cur=stack[--top],nxt;
			int p[9];
			int_to_ar(decode(cur),p);
			int pos=findpos(p);
			for(int i=0;i<4;i++){
				int dec=ofs[pos][i];
				if(dec!=-1){
					swap(p[pos] , p[dec]);
					nxt=State(p);						
					int g=G[cur] + 1;
					if(nxt==T) return g;
					if((G[nxt]==-1||G[nxt]>g)&&g+h(decode(nxt))<=Dmax){
						G[nxt]=g;
						stack[top++]=nxt;
					}
					swap(p[pos],  p[dec]);
				}
			}
		}
	}while(Dmax++);
	return -1;
}
bool exist(int n,int inv,int opos){//n^2-1迷题存在可行解
	int row=opos/n,col=opos%n;
	return (row+col+n+inv)%2!=0;
}
int main()
{
	//freopen("t.in", "r", stdin);
	int T[]={1,2,3,4,5,6,7,8,0},S[9];
	int cas;
	scanf("%d",&cas);
	while(cas--){
		int opos,inv=0;
		for(int i=0;i<9;i++){
			scanf("%d",&S[i]);
			for(int j=0;j<i;j++)
				if(S[j]>S[i]) inv++;
			if(S[i]==0) opos=i;
		}
		if(!exist(3,inv,opos)) printf("-1\n");
		else{
			int re=IDAstar(State(S),State(T));
			printf("%d\n",re);
		}
	}
	return 0;
}