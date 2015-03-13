// WA
#include <iostream>
using namespace std;
// segmentTree 线段树,颜色覆盖统计,二进制集,lazy implement
class segmentTree
{
public:
	struct node
	{
		int beg,end; // [beg,end]
		node *l,*r; // 
		int color;// data
		int later;
		node(int a,int b):beg(a),end(b),l(0),r(0){color=1;later=0;}
	};typedef node* link;
	link root;
	segmentTree(int a,int b){root=build(a,b);}

	link build(int a,int b){
		link p=new node(a,b);
		if(b-a>1){			
			p->l=build(a,(a+b)/2);
			p->r=build((a+b)/2,b);
		}
		return p;
	}
	void update(int a,int b,int c=1,link x=0){
		if(x==0) x=root;
		if(c==x->color) return;
		if(a<= x->beg && b>= x->end ) x->color=c,x->later=1;
		else if(x->end - x->beg >1 ){
			if(x->later>0){
				x->l->color=x->r->color=x->color;
				x->l->later=x->r->later=1;
				x->later=0;
			}
			int mid=(x->beg+x->end)/2;
			if(a< mid ) update(a,b,c,x->l);
			if(b> mid ) update(a,b,c,x->r);
			x->color=x->l->color|x->r->color;
		}
	}
	int count(int a,int b,link x=0){
		if(x==0) x=root;
		if(x->later>0&&x->end - x->beg >1){
			x->l->color=x->r->color=x->color;
			x->l->later=x->r->later=1;
			x->later=0;
		}
		if(a<= x->beg && b>= x->end ) return x->color;
		else if(x->end - x->beg >1 ){
			int mid=(x->beg+x->end)/2;
			int c1=0,c2=0;
			if(a< mid ) c1=count(a,b,x->l);
			if(b> mid ) c2=count(a,b,x->r);
			return c1|c2;
		}return x->color;
	}
};
int countbit(int t){
	int cnt=0;
	while(t>0){
		cnt+=t%2;
		t=t>>1;
	}return cnt;
}
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int l,t,o;
	scanf("%d%d%d\n",&l,&t,&o);
	segmentTree ST(1,l+1);
	char ch;
	int a,b,c;
	while(o--){
		scanf("%c",&ch);
		if(ch=='C'){
			scanf("%d%d%d\n",&a,&b,&c);
			c=1<<(c-1);
			ST.update(a,b+1,c);
		}else{
			scanf("%d%d\n",&a,&b);
			int re=ST.count(a,b+1);
			printf("%d\n",countbit(re));
		}
	}
	return 0;
}