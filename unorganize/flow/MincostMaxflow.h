// Minimum Cost Maximum Flow in Matrix
#define N 256
#define INF 1000000000
#define _clr(ar) memset(ar,0,sizeof(ar))
#define _min(a,b) (a<b?a:b)

int c[N][N],f[N][N],w[N][N];//[1..n]
int pnt[N],value[N],d[N],open[N],oldque[N];
int flow,cost;
void mincost(int n, int s , int t)
{
	int cur,tail,tl,i,u,v;
	_clr(f);
	flow=0; cost=0;
	do{ 
		_clr(d);
		for(i=1;i<=n; i++)
			value[i]=INF ;
		open[0]=s;
		d[s]=INF;
		tail=value[s]=0;
		while( tail>=0){
		bool mk[N]={0};
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