//-------------------------- Branch&bound -------------------------------
// 1. MaxLoading 分支限界-子集树形式
// f= g + h (<)
// g= cv+w[lv]*x[lv]
// h= r[lv]
//constraint: cv+w[lv]<=c
//bound: cw+r[lv]>bestw
// g(tmp)=tmp.f-r[lv-1]
// result: bestw 
#define M //估算的搜索状态数目(<状态总数)
struct bbnode{
	bbnode *p;bool lch;
	bbnode(bbnode *p,bool lch):p(p),lch(lch){}
};
struct Node{
	bbnode *ptr; int f; int lv;
	Node(bbnode *p=0,int lv=0,int f=0):ptr(p),lv(lv),f(f){}
};
bbnode* live_node;
Node heap[M];	int size; //heap
bool cmp(Node &a,Node &b){ return a.f<b.f;}
// < for maxheap, > for minheap 
void push(bool ch,int lv,int f){
	bbnode *b=new bbnode(live_node,ch);
	heap[size++]=Node(b,lv,f);
	push_heap(heap,heap+size,cmp);
}
Node pop(){
	pop_heap(heap,heap+size,cmp);
	return heap[--size];
}
bool bestx[N];//[1..n]
int w[N],c;//重量，容量

int search(int n){
	//init
	int r[N]; //剩余容量
	r[n]=0;
	for(int j=n-1;j>0;j--) r[j]=r[j+1]+w[j+1];
	int lv=1;
	live_node=0;
	int cw=0,bestw=0;
	size=0;// for heap
	// search
	while(lv!=n+1){// not a leaf
		if(cw+w[lv]<=c){//constraint
			push(1,lv+1,cw+w[lv]+r[lv]);//left
			if(cw+w[lv]>bestw) bestw=cw+w[lv];
		}
		if(cw+r[lv]>bestw){//bound
			push(0,lv+1,cw+r[lv]);//right
		}
		// next Node
		Node tmp=pop();
		lv=tmp.lv;
		live_node=tmp.ptr;
		cw=tmp.f-r[lv-1];//g(tmp)
	}
	// cotr solution
	for(int i=n;i>0;i--){
		bestx[i]=live_node->lch;
		live_node=live_node->p;
	}
	return bestw;
}
//--------------------------------------------------------------
// 2. Knapsack 分支限界-子集树形式
// f= Bound (<)
// g= cp
// h= cp+..
//constraint: cw+q[lv].w<=c
//bound: Bound(lv+1)>=bestp
// g(tmp):	cw=tmp.w, cp=tmp.p, up=tmp.f;
// result: bestp 
struct bbnode{
	bbnode *p;bool lch;
	bbnode(bbnode *p,bool lch):p(p),lch(lch){}
};
struct Node{
	bbnode *ptr;int lv;
	int f,p;
	int w;
	Node(bbnode *ptr=0,int lv=0,int f=0,int p=0,int w=0)
		:ptr(ptr),lv(lv),f(f),p(p),w(w){}
};
bbnode* live_node;
Node heap[M];	int size; //heap
bool cmp(Node &a,Node &b){ return a.f<b.f;}
void push(bool ch,int lv,int f,int p,int w){
	bbnode *b=new bbnode(live_node,ch);
	heap[size++]=Node(b,lv,f,p,w);
	push_heap(heap,heap+size,cmp);
}
Node pop(){
	pop_heap(heap,heap+size,cmp);
	return heap[--size];
}
int bestx[N];
int n,c,cw;
int cp,bestp;
struct Object{
	int ID;
	double d;
	int w,p;		
} q[N];
bool operator<(Object& a,Object& b){ return a.d<b.d;}
int Bound(int i){
	int cleft=c-cw;
	int b=cp;
	while(i<=n&&q[i].w<=cleft){
		cleft-=q[i].w;
		b+=q[i].p;
		i++;
	}
	if(i<=n) b+=q[i].p/q[i].w*cleft;
	return b;
}
void search(){
	// init
	int lv=1; live_node=0; 
	cw=0,cp=0,bestp=0;
	int up=Bound(1);
	size=0;// for heap
	// search
	while(lv!=n+1){// not a leaf
		int wt=cw+q[lv].w;
		if(wt<=c){//left
			if(cp+q[lv].p>bestp) bestp=cp+q[lv].p;
			push(1,lv+1,up,cp+q[lv].p,cw+q[lv].w);
		}
		up=Bound(lv+1);
		if(up>=bestp)
			push(0,lv+1,up,cp,cw);//right
		// next Node
		Node tmp=pop();
		lv=tmp.lv;
		live_node=tmp.ptr;
		cw=tmp.w, cp=tmp.p, up=tmp.f;
	}
	// cotr solution
	for(int k=n;k>0;k--){
		bestx[k]=live_node->lch;
		live_node=live_node->p;
	}
}
int Knap(){
	int W=0,P=0;
	for(int i=1;i<=n;i++){
		q[i].ID=i;
		q[i].d=1.0*q[i].p/q[i].w;
		P+=q[i].p,W+=q[i].w;
	}
	if(W<=c) return P;
	sort(q+1,q+n+1);
	search();
	return bestp;
}
//-------------------------------------------------------------------
// 3. TSP 分支限界-排列树形式
// b= g + h (>)
// g= cc
// h= rcost
//constraint:有边 
//bound: b<bestc
// g(tmp)=E
// result: bestc
#define INF 0x7fffffff
//求最小值，要求估算下界
int n,mat[N][N];//[0..n)
int solu[N];
struct Node{
	int lcost;//子树费用下界
	int cc;//当前费用
	int rcost;//x[s:n-1]中顶点最小边费用和
	int *x,s;//x[0:s]已搜索结点路径,x[s+1:n-1]未搜索结点
	Node(int cc=0,int rcost=0,int s=0):cc(cc),rcost(rcost),s(s){}
};
Node H[M]; int size;
bool cmp(Node &a,Node &b){ return a.lcost>b.lcost;}
// < for maxheap, > for minheap 
int TSP(){
	int m_out[N],sum=0,i;
	for(i=0;i<n;i++){
		int min=INF;
		for(int j=0;j<n;j++){
			if(mat[i][j]<min) min=mat[i][j];
		}
		if(min==INF) return INF;// false
		m_out[i]=min;
		sum+=min;
	}
	int bestc=INF;//最优
	size=0;
	Node E(0,sum,0);
	E.x=new int[n];
	for(i=0;i<n;i++) E.x[i]=i;
	while(E.s<n-1){
		if(E.s==n-2){//倒数第而点,再加2边构成回路
			int n_2=E.x[n-2],n_1=E.x[n-1];
			if(mat[n_2][n_1]!=INF&&mat[n_1][0]!=INF&&
				E.cc+mat[n_2][n_1]+mat[n_1][0]<bestc)
			{
				bestc=E.cc+mat[n_2][n_1]+mat[n_1][0];
				E.cc=bestc;
				E.lcost=bestc;
				E.s++;
				H[size++]=E;
				push_heap(H,H+size,cmp);
			}else delete[] E.x;
		}else{
			for(int i=E.s+1;i<n;i++){
				if(mat[E.x[E.s]][E.x[i]]!=INF){
					int cc=E.cc+mat[E.x[E.s]][E.x[i]];
					int rcost=E.rcost-m_out[E.x[E.s]];
					int b=cc+rcost;//下界
					if(b<bestc){
						Node E_n(cc,rcost,E.s+1);
						E_n.lcost=b;
						E_n.x=new int[n];
						for(int j=0;j<n;j++)
							E_n.x[j]=E.x[j];
						swap(E_n.x[i],E_n.x[E.s+1]);
						H[size++]=E_n;
						push_heap(H,H+size,cmp);
					}
				}
			}
			delete [] E.x;
		}
		if(size>0){
			pop_heap(H,H+size,cmp);
			E=H[--size];
		}else break;
	}
	if(bestc==INF) return INF;
	for(i=0;i<n;i++) solu[i]=E.x[i];
	while(size>0){
		if(H[size-1].x!=0){
			delete[] H[size-1].x;
			size--;
		}
	}
	return bestc;
}