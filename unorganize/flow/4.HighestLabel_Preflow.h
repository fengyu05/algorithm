#include <iostream>
#include <algorithm>
using namespace std;

struct node{
	int dat; node* next;
	node(int d=0,node* n=0):dat(d),next(n){}
};
void Insert(node* head, int i){
   node * p=new node(i,head->next);
   head->next = p;
}
void Erase(node* p){
   node* q=p->next;
   p->next = q->next;
   delete q;
}
void Destroy(node* & head){
   node* q;   
   while(q=head->next){
      head->next = q->next;
      delete q;
   }
   delete head;
   head = NULL;
}

#define N 400
#define _clr(ar) (memset(ar,0,sizeof(ar)))
#define _min(a,b) (a<b?a:b)
#define _linkitr(itr,l)	for(itr = l->next; itr; itr = itr->next)

// 最高标号预流推进算法
class HighestLabel_Preflow
{
public:
    int V,c[N][N],f[N][N],maxflow;
    int e[N],h[N]; // excess & height
    node* nb[N];   //Neighbour lists

	void init(){
		memset(c,0,sizeof(c));
		memset(f,0,sizeof(f));
		maxflow=0;
	}
	void preprocess(int s)
	{
	   int u;
	   node *itr;
	   for(u=0; u<V; ++u){ h[u]=e[u]=0; }
	   h[s] = V;
	   //   
	   _linkitr(itr,nb[s])
	   {
		  u = itr->dat;
		  f[s][u] = c[s][u];
		  f[u][s] = -c[s][u];
		  e[u] = c[s][u];
		  e[s] -= c[s][u];
	   }
	}
	void push(int u, int v){
	   //Applies when: u is overflowing, cf[u][v]>0, and h[u] = h[v] +1.
	   //cf[u][v] = c[u][v] - f[u][v];
	   //Action: Push df[u][v] = min{e[u], cf[u][v]) units of flow from u to v
	   int Cf = c[u][v] - f[u][v];
	   int Df = _min(e[u],Cf);
	   f[u][v] += Df;
	   f[v][u] = -f[u][v];
	   e[u] -= Df;
	   e[v] += Df;      
	}
	void relabel(int u){
	   //Applies when: u is overflowing and for all v in V such that (u,v) is in Ef,
	   //        we have h[u] <= h[v].
	   //Action: h[u] = 1 + min{h[v] : (u,v) in Ef
	   int min = V * 2;   //在前推流中,顶点高度总是小于2V
	   node *itr;
	   _linkitr(itr,nb[u])
	   {
		  int w = itr->dat;
		  if( c[u][w]>f[u][w] && min > h[w] )
			 min = h[w];
	   }         
	   h[u] = 1 + min;
	}
	void discharge(int u){
	   node *cur = nb[u]->next;   
	   while(e[u] > 0)
	   {
		  if( !cur ) {
			 relabel(u);
			 cur = nb[u]->next;
		  }else {
			 int v = cur->dat;
			 if( c[u][v]>f[u][v] && h[u] == h[v] + 1)
				push(u, v);
			 else cur=cur->next;
		  }
	   }
	}
	void neighborDestroy(){
	   for(int i = 0; i<V; ++i)
		  Destroy(nb[i]);
	}
	int Maxflow(int s, int t,int n)
	{
	   V=n;
	   node *L, *itr;
	   int i, u, oldheight;
	   //构造每个结点的Neightbour list;
	   for(u = 0; u < V; ++u)
		  nb[u] = new node;

	   for(u = 0; u < V; ++u)
	   {
		  for(i = 0; i < u; ++i)
			 if( c[u][i] || c[i][u] ){
				Insert(nb[u],i);
				Insert(nb[i],u);
			 }
	   }
	   //构造L
	   L = new node;
	   for( i = 0; i < V; ++i)
	   {
		  if(i == s || i == t) continue;
		  Insert(L,i);
	   }
	   //初始化preflow
	   preprocess(s);
	   //   
	   for(itr = L; itr->next; itr = itr->next )
	   {
		  u = itr->next->dat;
		  oldheight = h[u];
		  discharge(u);
		  if(h[u] > oldheight)
		  {
			 Erase(itr);
			 Insert(L,u);
			 itr = L;
		  }
	   }
	   Destroy(L);
	   maxflow = 0;
	   _linkitr(itr,nb[s]){
		  if( f[s][itr->dat] )
			 maxflow += f[s][itr->dat];
	   }
	   neighborDestroy();
	   return maxflow;
	}

}; 
// test in Power Network POJ(1459) 1700K	187MS
HighestLabel_Preflow flow;
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
		ans=flow.Maxflow(n,n+1,n+2);
		printf("%d\n",ans);
	}
	return 0;
}