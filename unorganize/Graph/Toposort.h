#include <iostream>
using namespace std;
#define N 256
struct node
{	int id;
	node* next;
	node(int id,node *next=0):id(id),next(next){}
}; typedef node* link;
link adj[N];
int in_deg[N];
void insert(int x,int y){
	adj[x]=new node(y,adj[x]);
	in_deg[y]++;
}
void init(){
	memset(adj,0,sizeof(adj));
	memset(in_deg,0,sizeof(in_deg));
}
int ord[N];//拓扑序 ord[0..n)
int len[N],p[N];//拓扑最长路 (*)
//(*)为可选部分
void tpsort(int n){
	int ss=-1,tt=-1;
	memset(len,0,sizeof(len));//(*)
	memset(p,-1,sizeof(p));//(*)
	for(int i=0;i<n;i++) if(in_deg[i]==0) ord[++tt]=i;
	while(ss<tt){
		int cur=ord[++ss];
		for(link lk=adj[cur];lk;lk=lk->next){
			int v=lk->id;
			//(*)
			if(len[cur]+1>len[v]){
				len[v]=len[cur]+1;
				p[v]=cur;
			}//(*)
			if(--in_deg[v]==0)
				ord[++tt]=v;
		}
	}
}
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	init();
	int n,m;
	scanf("%d%d",&n,&m);
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y);
		insert(x,y);//x->y;
	}
	tpsort(n);
	return 0;
}