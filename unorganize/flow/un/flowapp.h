#include <iostream>
using namespace std;

// Snipers
// 顶点容量的最大流
// s:0 
// 1  .. n-1 
// n+1.. 2n-1
// t:n
#define N 128
#define INF INT_MAX
class Flow
{
public:
    int c[N][N],f[N][N],V,maxflow; 
	int ss,tt;
	int father[N];
    int MaxFlow(int s, int t){
		ss = s, tt = t;
		memset(f, 0, sizeof(f));
		maxflow = 0;
		while(pfs())
			augment();
		return maxflow;
	}
	void augment(){
		int tiny=INF;
		int v=tt, w=father[v];
		do{
			if(tiny > c[w][v]) tiny = c[w][v];
			v = w, w = father[v];
		}while(v != ss);   
		v = tt, w = father[v];
		do{
			f[w][v] += tiny;
			f[v][w] -= tiny;
			c[w][v] -= tiny;
			c[v][w] += tiny;
			v = w, w = father[v];
		}while(v != ss);
		maxflow += tiny;   
	}
	int queue[N];
    bool pfs(){
		memset(father, 0xff, sizeof(int)*V);
		int front=0,end=-1;
		father[ss] = ss;
		queue[++end]=ss;
		while(front<=end){
			int v = queue[front++];
			for(int j = 0; j < V; ++j)
				if(c[v][j]>0 && father[j]<0)
				{
					father[j] = v;
					if(j == tt)	return true;
					queue[++end]=j;
				}   
		}   
		return false;
	}
};
Flow F;
int main()
{
#ifndef ONLINE_JUDGE
  	freopen("t.in", "r", stdin);
#endif
	int cas,n,m;
	scanf("%d",&cas);
	while(cas--){
		scanf("%d%d",&n,&m);
		memset(F.c,0,sizeof(F.c));
		F.V=2*n;
		int p;
		for(int i=1;i<n;i++){
			scanf("%d",&p);
			F.c[i][i+n]=F.c[i+n][i]=p;
		}
		while(m--){
			int x,y;
			scanf("%d%d",&x,&y);
			if(x==0){
				F.c[x][y]=INF;
			}else if(y==n){
				F.c[x+n][y]=INF;
			}else{
				F.c[x+n][y]=F.c[y+n][x]=INF;
			}
		}
		printf("%d\n",F.MaxFlow(0,n));
	}
	return 0;
}