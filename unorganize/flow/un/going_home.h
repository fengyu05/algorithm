#include <iostream>
#include <algorithm>
using namespace std;

#define N 256
#define INF 1000000000
#define _clr(ar) memset(ar,0,sizeof(ar))
#define _min(a,b) (a<b?a:b)

int c[N][N] , f[N][N] ,w[N][N] ,pnt[N];
int value[N] ,d[N] ,mk[N] ,open[N] , oldque[N];
int flow,cost;

void mincost(int n, int s , int t)
{
	int cur , tail , tl , i ,u,v;
	_clr(f);
	flow=0; cost=0;
	do{ 
		_clr(d);
		for(i=1;i<=n; i++)
			value[i]=INF ;
		open[0]=s;
		d[s]=INF;
		tail=value[s]=0;
		while( tail >=0){
		_clr(mk);
		memcpy(oldque ,open , sizeof(open ));
		for( tl=tail ,pnt[s]=cur=0,tail=-1; cur<=tl ; cur++)
			for(u=oldque[cur],v=1; v<=n; v++)
			if(f[u][v]<c[u][v] && value [u]<INF && value[u]+w[u][v]<value[v])
			{
				if(!mk[v]){
					mk[v]=1;
					open[++tail]=v;
				}
				pnt[v]=u;
				value[v]=value[u]+w[u][v];
				d[v]=_min(d[u],c[u][v]-f[u][v]);
			}
		}
		if (value[t]==INF ) return;
		flow+=d[t];
		cost+=d[t]* value[t];
		for(u=t ;u!=s;)
		{
			v=u; u=pnt[v];
			f[u][v]+=d[t];
			f[v][u]=-f[u][v];
			if ( f[u][v]<0 ) w[u][v]=-w[v][u];
			else if ( f[v][u]<0 ) w[v][u]=-w[u][v];
		}
	} while(d[t]>0);
}

int hu[128][2],man[128][2];
int h_cnt,m_cnt;
int main()
{
#ifndef ONLINE_JUDGE
  	freopen("t.in", "r", stdin);
#endif
	int n,m,i,j;
	while(scanf("%d%d\n",&n,&m),n!=0&&m!=0){
		h_cnt=m_cnt=1;
		char ch;
		for(i=1;i<=n;i++){
			for(j=1;j<=m;j++){
				while(scanf("%c",&ch),ch!='.'&&ch!='m'&&ch!='H');
				if(ch=='H'){
					hu[h_cnt][0]=i;
					hu[h_cnt][1]=j;
					h_cnt++;
				}else if(ch=='m'){
					man[m_cnt][0]=i;
					man[m_cnt][1]=j;
					m_cnt++;
				}
			}
			scanf("%c",&ch);
		}
		memset(c,0,sizeof(c));
		memset(w,0,sizeof(w));
		int ss=m_cnt+h_cnt+1;
		int tt=ss+1;
		for(i=1;i<=m_cnt;i++){
			c[ss][i]=1;
		}
		for(i=1;i<=m_cnt;i++){
			for(j=1;j<=h_cnt;j++){
				int we=abs(hu[i][0]-man[j][0])+abs(hu[i][1]-man[j][1]);
				c[i][j+m_cnt]=1;
				w[i][j+m_cnt]=we;
			}
		}
		for(i=1;i<=h_cnt;i++){
			c[i+m_cnt][tt]=1;
		}
		mincost(tt,ss,tt);
		printf("%d\n",cost);
	}
    return 0;
}