class treeA{
public:
	int c[M],size; // size must be the power of 2
	int lowBit(int x) {
		return x & (x ^ (x - 1));
	}
	void add(int x, int k) { // k can be negative 
		// a[x] += k
		while (x <= size) {
			c[x-1] += k;
			x += lowBit(x);
		}
	}
	int query(int x) {// sum:a[1..x];
		int ret = 0;
		while (x > 0) {
			ret += c[x-1];
			x -= lowBit(x);
		}
		return ret;
	}
	int query(int x,int y){ // sum:a(x..y]
		return query(y)-query(x);
	}
	int other(int x){ //sum:a(x..size]
		return c[size-1]-query(x);
	}
	void init(int maxsize){
		size=maxsize;
		memset(c,0,sizeof(c));
	}
};


// segmentTree 线段树-变形，对点统计
class segmentTree
{
public:
	struct node
	{
		int beg,end,cnt; // [beg,end]
		node *l,*r; // children
		node(int a,int b):beg(a),end(b),cnt(0),l(0),r(0){}
	};typedef node* link;
	link root;
	segmentTree(int a,int b){root=build(a,b);}

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
		if(x==0) x=root;
		if(p<= x->end && p>= x->beg) x->cnt+=val;
		if(x->end > x->beg){
			int mid=(x->beg+x->end)/2;
			if(p<=mid) update(p,val,x->l);
			else update(p,val,x->r);
		}
	}
	int query(int nth,link x=0){// return the nth point 
		if(x==0) x=root;       // in the tree
		if(x->beg == x->end) return x->beg;
		if(nth<= x->l->cnt) return query(nth,x->l);
		else return query(nth-x->l->cnt,x->r);
	}
};