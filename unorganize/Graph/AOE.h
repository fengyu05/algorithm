#include <iostream>
using namespace std;
// AOE(Activity On Edge)
// 关键路径长度  (边)活动松弛时间

// DFS之后按照结束访问时间反向排序,
// 如果在DFS过程中出现后向边(成环),则无法TOPO
#define N 128
#define M 64
#define INF 1000000000
#define NaN -1

int n,m,pos,mk[N],ord[N]; //ord[1..n]
int mat[N][N];//mat[1..n] NaN for edge not exist
int ea[M],eb[M];//for edge [1..m]
bool topo;

void dfs(int v)
{
	if(mk[v]<0){ topo=false; return ;}
	if(mk[v]>0) return ;
	else mk[v]=-1;
	for(int w=1; topo && w<=n; w++)
		if(mat[v][w]>0) dfs(w);
	ord[pos--]=v; mk[v]=1;
}
void toposort(){
	topo=true; pos=n;
	memset(mk,0, sizeof(mk));
	for(int i=1;topo && i<=n; i++)
		if(!mk[i]) dfs(i);
}
void init(int n){
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			mat[i][j]=mat[j][i]=NaN;
}

int kp;//关键路径长度
int ve[N];//结点最早发生时间 max{ve[i]+mat[i][j]}
int vl[N];//结点最晚发生时间 min{vl[j]-mat[i][j]}
int e[M]; //边活动最早时间 e[x]=ve[i]  x:<i,j>
int l[M]; //边活动最晚时间 l[x]=l[j]-mat[i][j]  
int d[M]; //边活动松弛时间 d[x]=l[x]-e[x]

void main()
{
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int i,j,x;
	scanf("%d%d",&n,&m);
	init(n);
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&ea[i],&eb[i],&x);
		mat[ea[i]][eb[i]]=x;
	}
	toposort();

	memset(ve,0,sizeof(ve));
	for(i=2;i<=n;i++){
		int v=ord[i];
		int max=-1;
		for(j=1;j<i;j++){
			int u=ord[j];
			if(mat[u][v]>0){
				int tmp=ve[u]+mat[u][v];
				if(tmp>max) max=tmp;
			}
		}
		ve[v]=max;
	}
	vl[ord[n]]=kp=ve[ord[n]];
	for(i=n-1;i>=1;i--){
		int v=ord[i];
		int min=INF;
		for(j=n;j>i;j--){
			int u=ord[j];
			if(mat[v][u]>0){
				int tmp=vl[u]-mat[v][u];
				if(tmp<min) min=tmp;
			}
		}
		vl[v]=min;
	}
	// Input example
	// 7 10   
	// 1 2 3
	// 1 3 2
	// 1 4 6
	// 2 4 2
	// 2 5 4
	// 3 4 1
	// 3 6 3
	// 4 5 1
	// 5 7 3
	// 6 7 4
}
// AOE app
#include <iostream>
using namespace std;

#define N 10008
struct node
{	int u;
	node* next;
	node(int u,node *next=0):u(u),next(next){}
};

node* adj[N];
int n;
void init(){ memset(adj,0,sizeof(adj));}
void insert(int x,int y){adj[x]=new node(y,adj[x]);}
bool edge(int x,int y){
	for(node* t=adj[x];t;t=t->next)
		if(t-> u ==y) return true;
	return false;
}

int mk[N],pos,ord[N]; //ord[0,n)
bool topo; //mat[1..n]
void dfs(int v)
{
	if(mk[v]<0){ topo=false; return ;}
	if(mk[v]>0) return ;
	else mk[v]=-1;
	//for(int w=1; topo && w<=n; w++)
	for(node* pt=adj[v];pt;pt=pt->next)
		dfs(pt->u);
	ord[--pos]=v; mk[v]=1;
}
void toposort(){
	topo=true; pos=n;
	memset(mk,0, sizeof(mk));
	for(int i=1;topo && i<=n; i++)
		if(!mk[i]) dfs(i);
}

int ve[N];//结点最早发生时间 max{ve[i]+mat[i][j]}
int main()
{

	int m,a,b,i;
	while(scanf("%d%d",&n,&m)==2){
		init();
		while(m--){
			scanf("%d%d",&a,&b);
			insert(b,a);
		}
		toposort();
		if(!topo){
			printf("Poor Xed\n");
		}else{
			for(i=1;i<=n;i++) ve[i]=100;

			for(i=0;i<n;i++){
				int v=ord[i];
				int val=ve[v]+1;
				for(node* pt=adj[v];pt;pt=pt->next){
					if(ve[pt->u]<val) ve[pt->u]=val;	
				}
			}
			int re=0;
			for(i=1;i<=n;i++) re+=ve[i];
			printf("%d\n",re);
		}
	}
	return 0;
}

///*
#define N 128
struct Gnode{
	int adjv;
	int weight;
	Gnode* next;
};
struct WDigraph{
	int n,e;
	Gnode* adj[N];
	int deg[N];
	void CalDegree(){
		memset(deg,0,sizeof(deg));
		for(int j=1;j<=n;j++){
			Gnode* p=adj[j];
			while(p){
				deg[p->adjv]++;
				p=p->next;
			}
		}
	}
};

int Toplogical(WDigraph& G){
	Gnode* p;
	int j,w,top=0;
	int stack[N],ve[N]={0};
	G.CalDegree();
	for(j=1;j<=G.n;j++)
		if(G.deg[j]==0)
			stack[++top];
	while(top>0){
		w=stack[top--];
		p=G.adj[w];
		while(p){
			G.deg[p->adjv]--;
			if(G.deg[p->adjv]==0)
				stack[++top]=p->adjv;
			if(ve[w]+p->weight > ve[p->adjv] )
				ve[p->adjv]=ve[w]+p->weight;
			p=p->next;
		}
	}
	return ve[w];
}
//*/