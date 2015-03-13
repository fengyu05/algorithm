#include <iostream>
#include <algorithm>
using namespace std;
//1. -------------------------��С�������㷨-----------------------------
#define N 128
#define INF 0x7fffffff
int mat[N][N];//[0..n)
//INF for no edge
// for undirect graph mat[i][j]=mat[j][i] 
void init(int n){ for(int i=0;i<n;i++)
	for(int j=0;j<n;j++) mat[i][j]=INF;
}
//--------------------------- Prim ---------------------------------
// use heap
template<class Item,int __SIZE>class Heap{
public:
	Item array[__SIZE];
	int n;
	int size(){return n;}
	void init(){n=0;}
	void push(Item x){
		array[n++]=x;
		push_heap(array,array+n);
	}
	Item pop(){
		pop_heap(array,array+n);
		return array[--n];
	}
};
struct Node
{
	int x,y;//end-point
	int w;
	Node(int x=0,int y=0,int w=0):x(x),y(y),w(w){}
};
bool operator<(Node& a,Node& b){ return a.w>b.w;}
Heap<Node,N*(N-1)/2> heap;// size is key point
int prim(int n){
	int cost=0;
	bool flag[N]={0};
	heap.init();
	heap.push(Node(n-1,n-1,0));// start point
	int cnt=0;
	while(cnt<n){
		Node cur=heap.pop();
		if(flag[cur.y]==0)
		{
			flag[cur.y]=1,cost+=cur.w,cnt++;
			for(int i=0;i<n;i++)
			{
				int w=mat[cur.y][i];				
				if(w!=INF&&flag[i]==0)
					heap.push(Node(cur.y,i,w));
			}
		}			
	}
	return cost;
}
// mst - use queue
int mst(int n)
{
	int dist[N],re=0;
	int i,j,u;
	bool flag[N]={0};
	flag[0]=1;
	for (i=0; i<n; i++)
		dist[i] = mat[i][0];
	for (i=1;i<n; i++)
	{
		int min = INF;
		for (j=0; j<n; j++){
			if (dist[j]>=0 && !flag[j] && dist[j] < min)
				min=dist[j],u=j;			
		}
		flag[u] = 1,re += dist[u];
		for (j=0; j<n; j++){
			if (!flag[j] && mat[u][j]>=0 &&
				(dist[j]<0||dist[j]>mat[u][j]))
				dist[j] = mat[u][j];
		}
	}
	return re;
}
//-------------------- kruskal --------------------------------
// u-vΪ��ʱ,����Ҫ���v-u 
const int maxE=N*N/2;
int e_cnt;// init to 0
struct Edge{ 
	int u,v;
	int w;
	Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
} E[maxE];
int uf[N],a[N];
bool cmp(Edge &a, Edge &b){	return a.w < b.w;}
int find(int v)
{
	if (uf[v]<0)
		return v;
	return uf[v] = find(uf[v]);
}
int kruskal(int n)
{
	int cnt=0;
	int re =0;
	memset(uf,-1,sizeof(uf));
	sort(E,E+e_cnt,cmp);
	for (int i=0; i<e_cnt; i++)
	{
		int p1 = find(E[i].u);
		int p2 = find(E[i].v);
		if (p1 != p2)
		{			
			uf[p1] = p2;
			re += E[i].w;
			if(++cnt>=n-1) break;
		}
	}
	return re;
}
// test in Poj 2421(Constructiong Road) 
int main()
{
	int n,m,i,j;
	scanf("%d",&n);
	init(n);
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&mat[i][j]);
	scanf("%d",&m);
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y);
		x--,y--;
		mat[x][y]=mat[y][x]=0;
	}
	e_cnt=0;
	for(i=0;i<n;i++)
		for(j=i+1;j<n;j++){
			E[e_cnt++]=Edge(i,j,mat[i][j]);
		}
	printf("%d\n",prim(n));	//332K	0MS
	printf("%d\n",mst(n));	//240K	0MS
	printf("%d\n",kruskal(n));	//472K 32MS	
	return 0;
}

//һ����Ȥ�Ľ��ۣ���С������һ���������������������ߵ�Ȩ��С�ġ�
// minimum spanning tree = bottleneck spanning tree

//2.------------------------ ��С������ ----------------------
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
int main()//test in Poj 1679 The Unique MST: 584K	15MS
{	
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



//3. --------------- ��С���������� -----------------------------
/*
��Ҫ��һ�������н������ĸ����˵���Ǽ���һ���߱ض��γ�һ������
Ȼ��ȥ������һ���߱ض�����һ�������Ȱ�v0���ͼ�г�ȥ�����ʣ�µ�
ͼ�ĸ���ͨ��������С���������Ѹ���������v0����СȨ�ı������������
��k����ͨ��������ʱ�����һ����Сk��������������Ȼ��ͣ�ؽ�����С
���н������γ�k+1 ��,k+2�ȡ���ֱ���ﵽҪ��Ϊֹ���㷨���Ӷ�O(kn+n^2)
*/