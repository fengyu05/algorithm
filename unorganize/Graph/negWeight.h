#define N 512
#define INF 1e99

int queue[N],front,rear;
void init(){front=-1,rear=-1;}
int next(int pos){return (pos+1)%N;}
void push(int x){ queue[rear=next(rear)]=x;}
int pop(){ return queue[front=next(front)];}

double mat[N][N],dist[N];
int st[N];

void Bellman(int n,int s){
	int i,cnt=0;
	for(i=0;i<n;i++) dist[i]=INF;
	dist[s]=0 ; st[s]=-1;//[*] root
	init();
	push(s),push(n);
	while(front<rear){
		int v=pop();
		if(v==n){
			if(cnt++>n) return;
			push(v);
		}else{
			for(int t=0;t<n;t++)
				if(dist[t]>dist[v]+mat[v][t]){
					dist[t]=dist[v]+mat[v][t];
					push(t);
					st[t]=v;//[*]
				}
		}
	}
}
bool iscycle(int n){//¸º»·¼ì²â
	for(int i=0;i<n;i++){
		int j=st[i];
		while(j!=-1){
			j=st[j];
			if(j==st[i])
				return true;
		}
	}
	return false;
}

// adj-list version
struct WEdge{int _t;double w;
    WEdge(int t=0,double w=0):_t(t),w(w){}
	operator int() const{ return _t;}
};
vector<WEdge> adj[N];
double dist[N];

void BellmanFord(int n,int s)
{
	int mk[N]={0},open[N],open1[N];
    int i,t,p=0;
	int tail,cur;
    for(i=0;i<n;i++) dist[i]=INF;
    dist[s]=tail=0; open[0]=s;
    while(++p,tail>=0){
        for(i=0;i <=tail;i++) open1[i]=open[i];
        for(cur=0,t=tail,tail=-1; cur <=t; cur++){
			int u=open1[cur];
            for(i=0;i<adj[u].size();i++){
                int v=adj[u][i];
				if( dist[v]> dist[u]+adj[u][i].w){
                    dist[v]= dist[u]+adj[u][i].w;
                    if(mk[v]!=p){
						open[++tail]=v;
						mk[v]=p;
					}
                }
            }
		}
    }
}
