/* 全局最小切割
 * fengyu05
 * test :POJ 2914 Minimum Cut
 * 2296K	5532MS	C++	2463B
最小割 Stoer-Wagner 算法 
Stoer-Wagner 算法用来求无向图 G=(V, E)的全局最小割。 
	算法基于这样一个定理：对于任意s, t ∈ V，全局最小割或者等于
	原图的s-t 最小割，或者等于将原图进行 Contract(s,t)操作所得的
	图的全局最小割。 
 
算法框架： 
1. 设当前找到的最小割MinCut 为+∞  
2. 在 G中求出任意 s-t 最小割 c，MinCut = min(MinCut, c)  
3. 对 G作 Contract(s, t)操作，得到 G'=(V', E')，
若|V'|>1，则G=G'并转 2，否则MinCut 为原图的全局最小割  
 
Contract 操作定义： 
若不存在边(p, q)，则定义边(p, q)权值w(p, q) = 0 
Contract(a, b): 删掉点 a, b 及边(a, b)，加入新节点 c，
对于任意 v∈V ，w(v, c) = w(c, v) = w(a, v) + w(b,v) 

*/
#include <iostream>
#include <algorithm>
using namespace std;

#define min(a,b) (a<b?a:b)
#define INF INT_MAX
#define N  512

class BasAugment
{
public:
    int c[N][N], maxflow;   
	int V,ss,tt,pred[N];	
	void init(){
		memset(c,0,sizeof(c));
		maxflow=0;
	}
    int MaxFlow(int s, int t,int n)
	{
		ss = s, tt = t, V=n;
		// assert(ss != tt);
		maxflow = 0; 
		while(bfs())
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
} flow;

int mat[N][N];
int Stoer_Wagner(int n){
	int re=INF;
	do{
		int s=n-2,t=n-1;
		for(int j=0;j<n;j++) for(int k=0;k<n;k++)
			flow.c[j][k]=mat[j][k];
		flow.maxflow=0;
		int tmp=flow.MaxFlow(s,t,n);
		re=min(re,tmp);
		n--;
		for(int i=0;i<n-1;i++){
			mat[i][n-1]+=mat[i][n];
			mat[n-1][i]=mat[i][n-1];
		}
	}while(n>1);
	return re;
}
int main()
{	
	int n,m;
	while(scanf("%d%d",&n,&m)==2){
		memset(mat,0,sizeof(mat));
		int x,y,z;
		while(m--){
			scanf("%d%d%d",&x,&y,&z);
			mat[x][y]+=z;
			mat[y][x]+=z;
		}
		printf("%d\n",Stoer_Wagner(n));
	}
	return 0;
}