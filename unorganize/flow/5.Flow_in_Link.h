//---------------- Flow in Link ---------------------------------------
#include <iostream>
using namespace std;
#define N  400
#define M N*N
#define INF 0x3fffffff
#define _clr(arr) (memset(arr,0,sizeof(arr)))

int c[M],f[M],ev[M],be[M],next[M],e_cnt=0;
int nbs[N],pnt[N],open[N],d[N],mk[N];
void AddEdge(int u, int v, int cc ) // Remember to set nbs[1..n]=e_cnt=0
{
	next[++e_cnt]=nbs[u]; nbs[u]=e_cnt; be[e_cnt]=e_cnt+1;
	ev[e_cnt]=v; c[e_cnt]=cc ; f[e_cnt]=0;
	next[++e_cnt]=nbs[v]; nbs[v]=e_cnt; be[e_cnt]=e_cnt-1;
	ev[e_cnt]=u; c[e_cnt]=0  ; f[e_cnt]=0;
}
int maxflow(int n, int s , int t)
{
	int cur , tail , j ,u,v, flow=0; // f has been set zero when AddEdge
	do{
		_clr(mk),_clr(d);
		open[0]=s ; mk[s]=1; d[s]=INF;
		for(pnt[ s]=cur=tail =0; cur<=tail && !mk[ t ]; cur++)
		for(u=open[cur] , j=nbs[u];j; j=next[j]){
			v=ev[j];
			if (!mk[v]&&f [ j]<c[ j ]){
				mk[v]=1; open[++tail]=v; pnt[v]=j ;
				if (d[u]<c[ j]-f [ j ]) d[v]=d[u];
				else d[v]=c[ j]-f [ j ];
			}
		}
		if(!mk[t]) break;
		flow+=d[t];
		for(u=t ;u!=s ;u=ev[be[j]]){
			j=pnt[u];
			f [ j]+=d[ t ];
			f [be[ j]]=-f [ j ];
		}
	} while(d[t] >0);
	return flow ;
}

// test in Power Network POJ(1459)
// 608K	1343MS	C++	1795B
int main()
{
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int n,e,i,cap;
	int p,c,a,b,ans;
	char ch;
	while(scanf("%d %d %d %d",&n,&p,&c,&e)==4)
	{
		e_cnt=0;
		_clr(nbs);
		for(i = 0; i < e; ++i)
		{
			while((ch=getchar()) !='(');
			scanf("%d,%d)%d",&a,&b,&cap);
			AddEdge(a,b,cap);
		}
		for(i = 0; i < p; ++i)
		{
			while((ch=getchar()) !='(');
			scanf("%d)%d",&a, &cap);
			AddEdge(n,a,cap);
		}
		for(i = 0; i < c; ++i)
		{
			while((ch=getchar()) !='(');
			scanf("%d)%d",&a, &cap);
			AddEdge(a,n+1,cap);
		}      
		ans=maxflow(n+2,n,n+1);
		printf("%d\n",ans);
	}
	return 0;
}