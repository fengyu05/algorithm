/*
 * 2985-The k-th Largest Group
 * 18220K	982MS	C++	1932B
 * fengyu05
 * 问题:一组不相交集合(disjion set)进行一系列合并操作,
 * 求第k大的集合的大小
 * 方法:并查集+线段数(求第k大数)
*/
#include <iostream>
using namespace std;
#define N 200000

	int p[N],r[N];
	void init(int n){
		for(int i=0;i<n;i++){
			p[i]=i;
			r[i]=0;
		}
	}
	int find(int x){
		int t=x;
		while(t!=p[t]) t=p[t];
		while(x!=p[x]){int tmp=p[x];p[x]=t;x=tmp;}
		return t;
	}
	void Union(int x,int y){
		x=find(x),y=find(y);
		if(r[x]>r[y]) p[y]=x;
		else p[x]=y;
		if(r[x]==r[y]) r[y]++;
	}
class sTree//线段树-变形，对点统计,求最大nth点
{
public:
	struct node
	{
		int beg,end,cnt; // [beg,end]
		node *l,*r; // children
		node(int a,int b):beg(a),end(b),cnt(0),l(0),r(0){}
	};typedef node* link;
	link root;
	int tot;
	sTree(int a,int b){root=build(a,b);tot=0;}

	link build(int a,int b){
		link p=new node(a,b);
		if(b>a){			
			p->l=build(a,(a+b)/2);
			p->r=build((a+b)/2+1,b);
		}
		return p;
	}
	void update(int p,int val=1,link x=0){
		// val=1: insert val=-1: remove
		if(x==0){ x=root; tot+=val;}
		if(p<= x->end && p>= x->beg) x->cnt+=val;
		if(x->end > x->beg){
			int mid=(x->beg+x->end)/2;
			if(p<=mid) update(p,val,x->l);
			else update(p,val,x->r);
		}
	}
	int query(int nth,link x=0){// return the nth largest point  
		if(x==0){ x=root;nth=tot-nth+1; }   
		if(x->beg == x->end) return x->beg;
		if(nth<= x->l->cnt) return query(nth,x->l);
		else return query(nth-x->l->cnt,x->r);
	}
};
int cnt[N];
int main()
{	
	int n,m;
	scanf("%d%d",&n,&m);
	init(n);
	for(int i=0;i<n;i++) cnt[i]=1;
	sTree st(0,n);
	st.update(1,n);
	int c,x,y;
	while(m--){
		scanf("%d",&c);
		if(c==0){
			scanf("%d%d",&x,&y);// x<-y
			x--,y--;
			x=find(x),y=find(y);
			if(x==y) continue;
			Union(x,y);
			st.update(cnt[x],-1);
			st.update(cnt[y],-1);
			st.update(cnt[x]+cnt[y],1);
			cnt[x]+=cnt[y];
			cnt[y]=cnt[x];
		}else{
			scanf("%d",&x);
			int re=st.query(x);
			printf("%d\n",re);
		}
	}
	return 0;
}