//------------------ heuristic search  -------------------------
// 子集树形式
struct bbnode{
	bbnode *p;bool lch;
	bbnode(bbnode *p,bool lch):p(p),lch(lch){}
};
struct Node{
	bbnode *ptr; Type f; int lv;
	Node(bbnode *p=0,int lv=0,Type f=0):ptr(p),lv(lv),f(f){}
};
bbnode* live_node;
Node heap[N];	int size; //heap
bool cmp(Node &a,Node &b){ return a.f<b.f;}
// < for maxheap, > for minheap 
void push(bool ch,int lv,Type f){
	bbnode *b=new bbnode(live_node,ch);
	heap[size++]=Node(b,lv,f);
	push_heap(heap,heap+size,cmp);
}
Node pop(){
	pop_heap(heap,heap+size,cmp);
	return heap[--size];
}
bool bestx[N];

void search(int n){
	// init
	int lv=1;
	live_node=0;
	Type cv=0;
	size=0;// for heap
	// search
	while(lv!=n+1){// not a leaf
		if(constraint){
			push(1,lv+1,f);//left
		}
		if(bound){
			push(0,lv+1,f);//right
		}
		// next Node
		Node tmp=pop();
		lv=tmp.lv;
		live_node=tmp.ptr;
		cv=g(tmp);
	}
	// cotr solution
	for(int i=n;i>0;i--){
		bestx[i]=live_node->lch;
		live_node=live_node->p;
	}
}

