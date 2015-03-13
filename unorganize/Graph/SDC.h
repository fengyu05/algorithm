// 差分约束系统
int a[N][N];//[1..n]
double b[N];   //[1..n]

void SDC(int n,int m){
	//v[1..n],v0
	int i,j;
	for(j=1;j<=n;j++) mat[0][j]=0;
	for(i=1;i<=n;i++)
		for(j=0;j<=n;j++)
			mat[i][j]=INF;
	for(j=1;j<=m;j++){
		int x,y;
		for(i=1;i<=n;i++){
			if(a[j][i]==1){
				x=i;
				continue;
			}else if(a[j][i]==-1){
				y=i;
				continue;
			}
		}
		mat[y][x]=b[j];
	}
	Bellman(n+1,0);
}

//Intervals
#include <iostream>
#include <vector>
using namespace std;

#define _max(a,b) ((a)>(b)?(a):(b))
#define _min(a,b) ((a)<(b)?(a):(b))
#define N 50003
#define INF 0x7fffffff

int queue[N],front,rear;
void init(){front=-1,rear=-1;}
int next(int pos){return (pos+1)%N;}
void push(int x){ queue[rear=next(rear)]=x;}
int pop(){ return queue[front=next(front)];}

struct WEdge{int _t,w;
    WEdge(int t=0,int w=0):_t(t),w(w){}
	operator int() const{ return _t;}
};
vector<WEdge> adj[N];
int dist[N];
int st[N],tail,cur;
/////////////////////////////////////////////
void BellmanFord(int n,int src)
{
	int open[N],open1[N];
    int i,t,u,v,p=0;
    for(i=1;i<=n;i++) dist[i]=INF;
    dist[src]=tail=0; open[0]=src;
    while(++p,tail>=0){
        for(i=0;i <=tail;i++) open1[i]=open[i];
        for(cur=0,t=tail,tail=-1; cur <=t; cur++)
            for(u=open1[cur],i=0;i <adj[u].size();i++){
                v=adj[u][i];
				if( dist[v]> dist[u]+adj[u][i].w){
                    dist[v]= dist[u]+adj[u][i].w;
                    if(st[v]!=p){
						open[++tail]=v;
						st[v]=p;
					}
                }
            }
    }
}
int main()
{
#ifndef ONLINE_JUDGE
  	freopen("t.in", "r", stdin);
#endif
    int m;
    while(scanf("%d",&m)!=EOF)
    {
        int i;
        for(i=0;i<N;i++) adj[i].clear();
        int a,b,c;
        int max=-INF,min=INF;
        while(m--)
        {
            scanf("%d%d%d",&a,&b,&c);
            min=_min(min,a); max=_max(max,b);
            adj[b].push_back(WEdge(a-1,-c));    
        }
        for(i=min;i <=max;i++)
        {
            adj[i].push_back(WEdge(i-1,0));
            adj[i-1].push_back(WEdge(i,1));
            adj[max+1].push_back(WEdge(i,0));
        }
        BellmanFord(max,max+1);
        printf("%d\n",dist[max]-dist[min-1]);
    }
    return 0;
}