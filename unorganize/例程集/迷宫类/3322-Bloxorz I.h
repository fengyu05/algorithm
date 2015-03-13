/* 3322-Bloxorz I
 * fengyu05
 * 题目:Bloxorz game(将1X1X2的石块滚到终点)
 * 解法:标准迷宫搜索,状态(500*500*3),BFS~
 */
#include <iostream>
#include <algorithm>
using namespace std;

#define N 500
const int L=N*N*4;

class Maze{
public:
	char map[N+12][N+12];// 0:empty -1:block -2:start -3:target 
	int n,m;//map[1..n][1..m]
	int sx[2],sy[2],ss,scnt,tx,ty;
	int i,j;
	Maze(int _n,int _m){	
		n=_n,m=_m;
		scnt=0;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				while(scanf("%c",&map[i][j]),map[i][j]=='\n');
				if(map[i][j]=='X'){
					sx[scnt]=i,sy[scnt]=j;map[i][j]='.';
					scnt++;
				}
				if(map[i][j]=='O'){ tx=i,ty=j;map[i][j]='.';}
			}
		}
		if(scnt==1){ ss=0;}
		else if(scnt==2){
			if(sx[0]==sx[1])
				ss=1;
			else ss=2;
		}
	}
	bool can_walk(int x,int y,int s){
		if(x<=0||x>=n-1) return false;
		if(y<=0||y>=m-1) return false;
		if(s==0){
			return map[x][y]=='.';
		}else if(s==1){
			return (map[x][y]=='.'||map[x][y]=='E')&&(map[x][y+1]=='.'||map[x][y+1]=='E');
		}else{
			return (map[x][y]=='.'||map[x][y]=='E')&&(map[x+1][y]=='.'||map[x+1][y]=='E');
		}
	}
	void show(){
		for(i=0;i<n;i++){
			for(j=0;j<m;j++)
				printf("%c",map[i][j]);
			printf("\n");
		}
	}
};
template<class Item,int __SIZE>class Queue{
public:
	Item array[__SIZE];
	int front,rear;
	void init(){front=-1,rear=-1;}
	int next(int pos){return (pos+1)%__SIZE;}
	void push(Item x){ array[rear=next(rear)]=x;}
	Item pop(){ return array[front=next(front)];}
	int size(){ return rear-front;}
};
// var
int G[L],F[L];
// State
struct State{ 
	int x,y;
	int s;//0 stand 1, tw-right 2, tw-down 
	State(int x=0,int y=0,int s=0):x(x),y(y),s(s){}
	operator int() const{ return s+((x*N)+y)*3; }
};
bool operator==(State& a,State &b){	return ((int)a)==((int)b);}
Queue<State,L> open;
// function
void init(){ for(int i=0;i<L;i++) G[i]=-1;} 
int h(State& a,State& b){ return abs(a.x-b.x)+abs(a.y-b.y);}

int ofs[3][4][3]={-2,0,2,//u0
				   0,1,1,//r0
				   1,0,2,//d0	
				   0,-2,1,//l0
				   -1,0,1,//u1
				   0,2,0,//r1
				   1,0,1,//d1
				   0,-1,0,//l1
				   -1,0,0,//u2
				   0,1,2,//r2
				   2,0,0,//d2
				   0,-1,2//l2
};
int dir;
void begin(){ dir=0;}
bool next_State(Maze& maze,State& cur,State& nxt){
	while(dir<4){
		int s=cur.s;
		nxt.x=cur.x+ofs[s][dir][0];
		nxt.y=cur.y+ofs[s][dir][1];
		nxt.s=ofs[s][dir][2];
		dir++;
		if(maze.can_walk(nxt.x,nxt.y,nxt.s)) return true;
	}
	return false;
}
// dir

int BFS(Maze& maze){
	State S(maze.sx[0],maze.sy[0],maze.ss),T(maze.tx,maze.ty,0);
	int Sid=S,Tid=T;
	if(S==T) return 0;
	open.init(),init();
	open.push(S);
	G[S]=0;
	while(open.size()){
		State cur=open.pop(),nxt;
		int id_cur=cur;
		int g=G[cur] + 1;
		begin();
		while(next_State(maze,cur,nxt)){
			int id_nxt=nxt;
			if(G[nxt]==-1){
				G[nxt]=g;
				if(nxt==T) return g;
				open.push(nxt);
			}
		}
	}
	return -1;
}
int main()
{
	int n,m;
	while(scanf("%d%d\n",&n,&m),n){
		Maze M(n,m);
		//M.show();
		int re=BFS(M);
		if(re==-1) printf("Impossible\n");
		else printf("%d\n",re);
	}
	return 0;
}