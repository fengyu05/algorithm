//--------------- A* on 8digit -----------------------
// sicily 1379
// A* ,heap ,判重

#include <iostream>
#include <algorithm>
using namespace std;
// h(s)<=h'(s) *估算下界少于真实下界
//h(s1)<=h(s2)+c(s1,s2) *估算下界的减少量最多为状态转移的代价
//在这 c(s1,s2)=1, h(s1)-hs(2)<=1
#define L 362880
template<class Item>class Heap{
public:
	Item heap[L];
	int n;
	int size(){return n;}
	void init(){n=0;}
	void push(Item x){
		heap[n++]=x;
		push_heap(heap,heap+n);
	}
	Item pop(){
		pop_heap(heap,heap+n);
		return heap[--n];
	}
};
int HASH[L]={0};
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
int ofs[9][4]={//0~8的4个方向的相邻位置
	-1, 1,3,-1,  
	-1, 2,4,0,
	-1,-1,5,1,
	0,4,6,-1,
	1,5,7,3,
	2,-1,8,4,
	3,7,-1,-1,
	4,8,-1,6,
	5,-1,-1,7
};
char of[]={'u','r','d','l'};//方向名
// var
int G[L],Pred[L];
char path[100],act[L];
int p_cnt;
// State 
struct State{ 
	int id,f,g;
	State(){}
	State(int p[]){
		id=encode(p);
	}
	operator int() const{ return id; }
};
bool operator<(State& a,State &b){ return a.f > b.f;}
Heap<State> open;
// function
void init(){ for(int i=0;i<L;i++) G[i]=Pred[i]=-1;}

int Hamilton(int a,int b){
	int x1=a/3,x2=b/3;
	int y1=a%3,y2=b%3;
	return abs(x1-x2)+abs(y1-y2);
}
/*
//Hamilton((p[i]+len-1)%len,i)
int Hamilton(int a,int b){ //dist[a-b]
	int x1=a/n,x2=b/n;
	int y1=a%n,y2=b%n;
	return abs(x1-x2)+abs(y1-y2);
}//*/
int h(int code){
	int p[10];
	int_to_ar(code,p);
	int re=0;
	for(int i=0;i<9;i++){
		re+=Hamilton((p[i]+8)%9,i);
	}
	return re; 
}
// dir
int Astar(State S,State T){
	if(S==T) return 0;
	bool found=false;
	open.init(),init();
	G[S]=0,  S.f=0,S.g=0,  Pred[S]=-1;
	open.push(S);
	while(open.size()&&!found){
		State cur=open.pop(),nxt;
		if(cur.g>G[cur]) continue;
		int p[9];
		int_to_ar(decode(cur),p);
		int pos=findpos(p);
		for(int i=0;i<4;i++){
			int dec=ofs[pos][i];
			if(dec!=-1){
				swap(p[pos] , p[dec]);
				nxt=State(p);						
				int g=G[cur] + 1;
				if(G[nxt]==-1||g<G[nxt]){
					G[nxt]=g;
					nxt.g=g;
					nxt.f=g+h(decode(nxt));
					Pred[nxt]=cur;
					act[nxt]=of[i];
					if(nxt==T){ found=true;break;}
					open.push(nxt);
				}
				swap(p[pos],  p[dec]);
			}
		}
	}
	if(found){
		p_cnt=0;
		int tmp=T;
		while(tmp!=-1){
			path[p_cnt++]=act[tmp];
			tmp=Pred[tmp];
		}
	}
	if(found) return G[T];
	else return -1;
}
bool exist(int n,int inv,int opos){//n^2-1迷题存在可行解
	int row=opos/n,col=opos%n;
	return (row+col+n+inv)%2!=0;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int T[]={1,2,3,4,5,6,7,8,0},S[9];
	char tmp;
		int opos,inv=0;
		for(int i=0;i<9;i++){
			while(scanf("%c",&tmp),tmp==' ');
			if(tmp=='x') S[i]=0;
			else S[i]=tmp-'0';
			for(int j=0;j<i;j++)
				if(S[j]>S[i]) inv++;
			if(S[i]==0) opos=i;
		}
		if(!exist(3,inv,opos)) printf("unsolvable\n");
		else{
			int re=Astar(State(S),State(T));
			for(int i=re-1;i>=0;i--){
				printf("%c",path[i]);
			}//*/
			printf("\n%d\n",re);
		}


}