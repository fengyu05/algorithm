// segmentTree Ïß¶ÎÊ÷
class segmentTree
{
public:
	struct node
	{
		int beg,end,cnt, // [beg,end]
			m,//²â¶È
			line,//Á¬Ğø¶ÎÊı
			lbd,rbd;//×óÓÒ¶ËÊÇ·ñ¸²¸Ç 1Îª¸²¸Ç£¬0²»¸²¸Ç
		node *l,*r; // children
		node(int a,int b):beg(a),end(b),cnt(0),l(0),r(0),
			m(0),line(0),lbd(0),rbd(0){}
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
	void update(int a,int b,int val=1,link x=0){
		// val=1: insert val=-1: remove
		if(x==0) x=root;
		if(a<= x->beg && b>= x->end ) x->cnt+=val;
		else if(x->end - x->beg >1 ){
			int mid=(x->beg+x->end)/2;
			if(a< mid ) update(a,b,val,x->l);
			if(b> mid ) update(a,b,val,x->r);
		}
		update_m(x);
		update_lines(x);
	}
	void update_m(link x){
		if(x->cnt>0) x->m=x->end - x->beg;
		else if (x->end == x->beg+1)  x->m=0; //leaf
		else x->m=x->l->m + x->r->m;		
	}
	void update_lines(link x){
		if(x->cnt>0)
			x->lbd=x->rbd=x->line=1; // ldb, rbd , line =1		
		else if (x->end == x->beg+1) //leaf
			x->lbd=x->rbd=x->line=0; //
		else {
			x->lbd=x->l->lbd; x->rbd=x->r->rbd;
			x->line=x->l->line  +  x->r->line - (x->l->rbd * x->r->lbd);
		}
	}
};
