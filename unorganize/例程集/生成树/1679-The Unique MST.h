/* 1679 The Unique MST
 * fengyu05
 */
#include <iostream>
#include <algorithm>
using namespace std;
/*
����"���н���"���������С��������Ȼ��ö�ٲ������ϵıߣ�����Ѹñ߼ӽ�ȥ
����ȥ�������ߺ��Ȩֵ�ͣ�ȡ��С��һ����Ϊ��С��������ע�������С����
����Ҫ��O(n^2)��Ԥ���������������������ϵ�·�������ߵ�Ȩֵ.
�㷨���Ӷ�O(n^2)
*/
#define N 128
#define INF 0x7fffffff
int mat[N][N];//[0..n)
int G[N][N];
//INF for no edge
// for undirect graph mat[i][j]=mat[j][i] 
void init(int n){ for(int i=0;i<n;i++)
	for(int j=0;j<n;j++) mat[i][j]=G[i][j]=INF;
}
//--------------------------- Prim ---------------------------------
// use heap
struct Edge
{
	int x,y;//x->y
	int w;
	Edge(int x=0,int y=0,int w=0):x(x),y(y),w(w){}
} heap[N*N/2];
bool operator<(Edge& a,Edge& b){ return a.w>b.w;}

int prim(int n){
	int size=0;
	int cost=0;
	bool flag[N]={0};
	heap[size++]=Edge();
	while(size){
		Edge cur=heap[0];
		pop_heap(heap,heap+size--);
		if(flag[cur.y]==0)
		{
			flag[cur.y]=1,cost+=cur.w;
			G[cur.x][cur.y]=G[cur.y][cur.x]=cur.w;
			for(int i=0;i<n;i++)
			{
				int w=mat[cur.y][i];				
				if(w!=INF&&flag[i]==0)
				{
					heap[size++]=Edge(cur.y,i,w);
					push_heap(heap,heap+size);
				}
			}
		}			
	}
	return cost;
}
int cost[N];//��iС�������ĳ���,i=[0..]
int cnt;
Edge pl[N][N];//��¼�����·�������
bool flag[N];
void dfs(int u,int o,int n){
	flag[u]=1;
	for(int i=0;i<n;i++)
		if(G[u][i]!=INF&&flag[i]==0){
			if(G[u][i]>pl[o][u].w)
				pl[o][i]=Edge(u,i,G[u][i]);
			else
				pl[o][i]=pl[o][u];
			dfs(i,o,n);
		}
}
void next(int n){
	int i,j;
	for(i=0;i<n;i++){
		memset(flag,0,sizeof(flag));
		pl[i][i]=Edge(i,i,0);
		dfs(i,i,n);
	}
	int _min=INF,idx,idy;
	for(i=0;i<n;i++)
		for(j=i+1;j<n;j++)
			if(G[i][j]==INF&&mat[i][j]!=INF){
				int tmp=mat[i][j]-pl[i][j].w;
				if(tmp<_min)
					_min=tmp,idx=i,idy=j;
			}
	cost[cnt]=cost[cnt-1]+_min;//��������������
	cnt++;
	G[idx][idy]=G[idx][idy]=mat[idx][idy];//add
	int nx=pl[idx][idy].x,ny=pl[idx][idy].y;
	G[nx][ny]=G[ny][nx]=INF;//delete
}
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int cas;
	scanf("%d",&cas);
	while(cas--){
		int n,m;
		scanf("%d%d",&n,&m);
		init(n);
		while(m--){
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			x--,y--;
			mat[x][y]=mat[y][x]=z;
		}
		cost[0]=prim(n);
		cnt=1;
		next(n);
		if(cost[0]!=cost[1])
			printf("%d\n",cost[0]);
		else
			printf("Not Unique!\n");
	}
	return 0;
}