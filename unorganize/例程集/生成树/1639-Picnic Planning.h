#pragma warning(disable: 4786)

#include <iostream>
#include <algorithm>
#include <utility>
#include <string>
#include <map>

using namespace std;  // tested by PKU 1639

const int maxn=509;
const int maxm=10009;
const int inf =0x3fffffff;

struct Heap
{
	int v, w;
	Heap() : v(0), w(0) {}
	Heap(int v_,int w_) : v(v_), w(w_) {}
	bool operator < (const Heap &b) const
	{
		return w>b.w || (w==b.w && v>b.v); 
	}
};

struct Edge
{
	int to, w;
	Edge *next;
};

Edge edgeM[maxm], *g[maxn], *gt[maxn];
Heap heap[maxm];
int ID;
int d[maxn], mk[maxn], pnt[maxn], best[maxn];

void link(Edge *g[],int u,int v,int w)
{
	Edge *p=&edgeM[ID++];
	p->to=v;
	p->w=w; 
	p->next=g[u];
	g[u]=p;
}
void deleteEdge(Edge *g[],int u,int v)
{
	Edge *p, *prev;
	for(prev=p=g[u]; p; prev=p, p=p->next)
		if(p->to==v) break;
	prev==p ? g[u]=p->next : prev->next=p->next;
}

void MST(int src)
{
	int u, hn=0; Edge *p;
	d[src]=0; heap[hn++]=Heap(src,0);
	for( ; ; )
	{
		for( ; hn&&mk[heap[0].v]; hn--) pop_heap(heap,heap+hn);
		if(!hn) return ;
		mk[u=heap[0].v]=1;
		for(p=g[u]; p; p=p->next)
			if(!mk[p->to]&&p->w<d[p->to])
			{
				d[p->to]=p->w;
				best[p->to]=d[p->to]>best[u] ? d[p->to] : best[u];
				pnt[p->to]=u;
				heap[hn++]=Heap(p->to,p->w);
				push_heap(heap,heap+hn);
			}
	}
}

void dfs(int u,int prev)
{
	Edge *p;
	for(p=gt[u]; p; p=p->next) if(p->to!=prev)
	{
		pnt[p->to]=u;
		d[p->to]=p->w;
		best[p->to]=d[p->to]>best[u] ? d[p->to] : best[u];
		dfs(p->to,u);
	}
}

int degreeMST(int N,int K,int src)
{
	int i, j, count, ans=0; Edge *p;
	pair<int,int> edge[maxn];
	for(i=0; i<N; i++) { d[i]=inf; mk[i]=0; }
	mk[src]=1; pnt[src]=-1; best[src]=-inf; d[src]=0;
	for(i=0, p=g[src]; p; p=p->next, i++) edge[i]=pair<int,int>(p->w,p->to);
	sort(edge,edge+i);
	for(count=j=0, p=g[src]; p; p=p->next, j++)
	{
		p->to=edge[j].second; p->w=edge[j].first;
		if(!mk[p->to]) 
		{
			++count;
			pnt[p->to]=src;
			best[p->to]=-inf;
			MST(p->to);
			d[p->to]=p->w;
		}
	}
	if(count>K) return -1;
	for(i=0; i<N; i++)
		if(i!=src) 
		{
			link(gt,pnt[i],i,d[i]);
			link(gt,i,pnt[i],d[i]);
			ans+=d[i];
		}
	for(i=count; i<K; i++)
	{
		int min=inf, v, w, maxCost;
		for(p=g[src]; p; p=p->next)
			if(p->to!=src&&pnt[p->to]!=src)
			{
				if(p->w-best[p->to]<min)
				{
					min=p->w-best[p->to];
					maxCost=best[p->to];
					w=p->w;
					v=p->to;
				}
			}
		if(min>=inf) break; 
		if(min<0) ans+=min;
		for(j=v; j!=src; j=pnt[j]) 
			if(d[j]==maxCost) break;  // or return -1;
	    	deleteEdge(gt,pnt[j],j);
		deleteEdge(gt,j,pnt[j]);
		link(gt,src,v,w);
		link(gt,v,src,w);
		d[v]=w; best[v]=-inf; pnt[v]=src;
		dfs(v,src);
	}
	return ans;
}

class Dictionary{
public:
	map<string,int> mm;
	typedef map<string,int>::iterator mit;
	int cnt;
	Dictionary(){cnt=0;}
	int word(char str[]){
		string s(str);
		mit pos=mm.find(s);
		if(pos==mm.end()){
			mm.insert(make_pair(s,cnt++));
			return cnt-1;
		}else return pos->second;		
	}
};
		
int main()
{
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int i, a, b, c,K,m;
	char namea[109], nameb[109];
	scanf("%d",&m);
	Dictionary dic;
	dic.word("Park");
	for(i=0; i<m; i++)
	{
		scanf("%s%s%d",namea,nameb,&c);
		a=dic.word(namea); b=dic.word(nameb);
		link(g,a,b,c);
		link(g,b,a,c);
	}
	scanf("%d",&K);
	printf("Total miles driven: %d\n",degreeMST(dic.cnt,K,0));
	return 0;
}