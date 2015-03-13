#include <iostream>
#include <algorithm>
using namespace std;

#define min(a,b) (a<b?a:b)
#define INF INT_MAX
#define N  400

//增广路定理:网络达到最大流当且仅当不存在增广路
//残余网络N(x):对于原网络中一条弧(u,v)
//  N(x)中有(1) u(u,v)=c(u,v)-f(u,v)
//          (2) u(v,u)=f(u,v) 
class BasAugment
{//     use bfs 640MS , use pfs 812MS
//no f[][]  bfs	407MS , use pfs 485MS
public:
    int c[N][N],f[N][N], maxflow;   
	int V,ss,tt,pred[N];
	
	void init(){
		memset(c,0,sizeof(c));
		memset(f,0,sizeof(f));
		maxflow=0;
	}
    int MaxFlow(int s, int t,int n)
	{
		ss = s, tt = t, V=n;
		// assert(ss != tt);
		maxflow = 0; 
		while(pfs())
			augment();
		return maxflow;
	}
	void augment()
	{
		int tiny=INF;
		int v=tt, w=pred[v];// trace back
		do{
			if(tiny > c[w][v]) tiny = c[w][v];
			v = w, w = pred[v];
		}while(v != ss);   
		v = tt, w = pred[v];
		do{
			f[w][v] += tiny;
			f[v][w] -= tiny;
			c[w][v] -= tiny;
			c[v][w] += tiny;
			v = w, w = pred[v];
		}while(v != ss);
		maxflow += tiny;   
	}
	//最短路扩充路径
	int queue[N];
    bool bfs() 
	{
		memset(pred, 0xff, sizeof(int)*V); // set pred[..]=-1
		int front=-1,end=-1;
		pred[ss] = ss;
		queue[++end]=ss;
		while(front<end)
		{
			int v = queue[++front];// v->j
			for(int j = 0; j < V; ++j)
				if(c[v][j]>0 && pred[j]<0)
				{
					pred[j] = v;
					if(j == tt)	return 1;
					queue[++end]=j;
				}   
		}   
		return 0;
	}
	// 最大容量扩充路径
	struct Node
    {   int v, wt;
        Node(int v=0, int wt=0):v(v), wt(wt){}
		bool operator<(const Node& x)const {return wt < x.wt; }
    } heap[N];	
	bool pfs() 
	{
		bool flag[N]={0};             
		int wt[N]={0};
		memset(pred, 0xff, sizeof(int)*V);   
		int size=0;
		pred[ss] = ss;
		heap[size++]=Node(ss, INF);
		while(size)
		{
			int v = heap[0].v, ww = heap[0].wt;
			pop_heap(heap,heap+size);
			size--;
			if(flag[v]) continue;
			flag[v] = 1;
			for(int j = 0; j < V; ++j)
				if(c[v][j]>0 && !flag[j])
				{
					int x =min(ww,c[v][j]);
					if(x <= wt[j]) continue;
					pred[j] = v;
					if(j == tt)	return 1;
					wt[j] = x;
					heap[size++]=Node(j, x);
					push_heap(heap, heap+size);
				}   
		}   
		return 0;
	}
};

// test in Power Network POJ(1459)
BasAugment flow;
int main()
{
	int n,e,i,cap;
	int p,c,a,b,ans;
	char ch;
	while(scanf("%d %d %d %d",&n,&p,&c,&e)==4)
	{
		flow.init();
		for(i = 0; i < e; ++i)
		{
			while((ch=getchar()) !='(');
			scanf("%d,%d)%d",&a,&b,&cap);
			flow.c[a][b] = cap;
		}
		for(i = 0; i < p; ++i)
		{
			while((ch=getchar()) !='(');
			scanf("%d)%d",&a, &cap);
			flow.c[n][a] = cap;
		}
		for(i = 0; i < c; ++i)
		{
			while((ch=getchar()) !='(');
			scanf("%d)%d",&a, &cap);
			flow.c[a][n+1] = cap;
		}      
		ans=flow.MaxFlow(n,n+1,n+2);
		printf("%d\n",ans);
	}
	return 0;
}