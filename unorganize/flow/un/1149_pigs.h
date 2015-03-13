#include <iostream>
using namespace std;

#define N 128
#define INF INT_MAX

    int c[N][N],f[N][N],V,maxflow; 
	int ss,tt;
	int father[N];

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

    int MaxFlow(int s, int t){
		ss = s, tt = t;
		memset(f, 0, sizeof(f));
		maxflow = 0;
		while(pfs())
			augment();
		return maxflow;
	}
int main()
{
#ifndef ONLINE_JUDGE
  	freopen("t.in", "r", stdin);
#endif
	int n,m,x,y,i;
	int val[1024]={0};
		scanf("%d%d",&m,&n);
		memset(c,0,sizeof(c));
		V=n+2;
		for(i=1;i<=m;i++){
			scanf("%d",&val[i]);
		}
		for(i=1;i<=n;i++){
			scanf("%d",&x);
			while(x--){
				scanf("%d",&y);
				if(val[y]>0){
					c[0][i]+=val[y];
					val[y]=-i;
				}else{
					c[-val[y]][i]=INF;
				}
			}
			scanf("%d",&x);
			c[i][n+1]=x;
		}		
		printf("%d\n",MaxFlow(0,n+1));

	return 0;
}