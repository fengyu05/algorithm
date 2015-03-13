#include <iostream>
#include <algorithm>
using namespace std;
// h(s)<=h'(s) *估算下界少于真实下界
//h(s1)<=h(s2)+c(s1,s2) *估算下界的减少量最多为状态转移的代价
//在这 c(s1,s2)=1, h(s1)-hs(2)<=1
#define N 100
#define M 100
const int L=N*M;
#define blockP 0.35
const char BK='#';
const char ST='S';
const char TG='T';
const char TR='.';
class Maze{
public:
	char map[N][M];// 0:empty -1:block -2:start -3:target 
	int n,m;//map[1..n][1..m]
	int sx,sy,tx,ty;
	int i,j;
	void ctorblock(){
		for(i=0;i<=m+1;i++)
			map[0][i]=map[n+1][i]=-1;
		for(i=0;i<=n+1;i++)
			map[i][0]=map[i][m+1]=-1;
	}
	Maze(int _n,int _m,int rn=0){	
		n=_n,m=_m;
		ctorblock();
		if(rn==0) rnd();
	}
	bool can_walk(int x,int y){ return map[x][y]!=-1;}
	int rand2(int d){return (rand()%(d-1))+1;}// return 1-d
	void rnd(){
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++){
				map[i][j]=rand()/(double)(RAND_MAX)>blockP?0:-1;
			}
		sx=rand2(n),sy=rand2(m),tx=rand2(n),ty=rand2(m);
		map[sx][sy]=-2,map[tx][ty]=-3;
	}
	void show(){
		printf("  ");
		for(i=0;i<10;i++) printf("%d",i);printf("\n");
		for(i=0;i<=n+1;i++){
			printf("%02d",i);
			for(j=0;j<=m+1;j++)
				if(map[i][j]==-1)
					putchar(BK);
				else if(map[i][j]==0)
					printf(" ");
				else if(map[i][j]==-2)
					putchar(ST);
				else if(map[i][j]==-3)
					putchar(TG);
				else
					putchar(TR);
			printf("\n");
		}
		printf("\n");
	}
};
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
// var
int G[L],Pred[L],path[100],p_cnt;
// State
struct State{ 
	int x,y,f,g;
	State(int x=0,int y=0):x(x),y(y){}
	operator int() const{ return x*M+y; }
};
bool operator<(State& a,State &b){ return a.f > b.f;}
Heap<State> open;
// function
void init(){ for(int i=0;i<L;i++) G[i]=Pred[i]=-1;} 
int h(State& a,State& b){ return abs(a.x-b.x)+abs(a.y-b.y);}

int ofs[4][2]={-1,0,0,1,1,0,0,-1},dir;
void begin(){ dir=0;}
bool next_State(Maze& maze,State& cur,State& nxt){
	while(dir<4){
		nxt.x=cur.x+ofs[dir][0];
		nxt.y=cur.y+ofs[dir][1];
		dir++;
		if(maze.can_walk(nxt.x,nxt.y)) return true;
	}
	return false;
}
int distance(State& cur,State& nxt){ return 1;}
// dir

bool Astar(State S,State T,Maze& maze){
	if(S==T) return true;
	bool found=false;
	open.init(),init();
	open.push(S);
	G[S]=0,  S.f=0,S.g=0,  Pred[S]=-1;
	while(open.size()&&!found){
		State cur=open.pop(),nxt;
		if(cur.g>G[cur]) continue;
		//printf("[ %d , %d ] : ",cur.x,cur.y);
		int id_cur=cur;
		begin();
		while(next_State(maze,cur,nxt)){
			int g=G[cur] + distance(cur,nxt);
			//int id_nxt=nxt;
			if(G[nxt]==-1||g<G[nxt]){
				bool new_st=false;
				if(G[nxt]==-1) new_st=true;
				G[nxt]=g;
				nxt.g=g;
				nxt.f=g+h(nxt,T);
				Pred[nxt]=cur;
				if(nxt==T) found=true;
				else{
					open.push(nxt);
				}
			}
		}
	}
	if(found){
		int tmp=path[p_cnt=0]=T;
		while(tmp!=-1){
			tmp=path[++p_cnt]=Pred[tmp];
		}
	}
	return found;
}

void main()
{
	Maze m(20,75);
	Astar(State(m.sx,m.sy),State(m.tx,m.ty),m);
	for(int i=1;i<p_cnt-1;i++){
		int x=path[i]/M;
		int y=path[i]%M;
		//printf("[%d %d] ",x,y);
		m.map[x][y]=2;
	}
	m.show();
}