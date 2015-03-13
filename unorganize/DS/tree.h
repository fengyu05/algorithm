#define N 20010
struct Linknode
{   int v;
    Linknode *next;
	Linknode(int v=0,Linknode* next=0):v(v),next(next){}
};
typedef Linknode *link;
struct TreeNode
{   link child;
	int descends;
	int p;
};
struct Tree
{   TreeNode li[N];
    //int root;
	//int n;
	Tree(){memset(li,0,sizeof(li));}
	void addchild(int p,int c){
		li[c].p=p;
		link ch=new Linknode(c,li[p].child);
		li[p].child=ch;
		if(li[p].descends==0) li[p].descends=1;
		if(li[c].descends==0) li[c].descends=1;
		while(1)
		{   li[p].descends += li[c].descends;
			p=li[p].p;
			if(p==0) break;
		}
	}
	
	void MinBalance(int n){
		int min_bla=INT_MAX,dex=0;
		for(int i=1;i<=n;i++){
			int maxs=0;
			link ch=li[i].child;
			while(ch){
				int tmp=li[ li[i].child->v ].descends;
				if(tmp > maxs)
					maxs=tmp;
				ch=ch->next;
			}
			int p=i;
			while(li[p].p!=0) p=li[p].p;
			int tmp=li[p].descends-li[i].descends;
			if(tmp>maxs) maxs=tmp;
			if(min_bla>maxs)
				min_bla=maxs,dex=i;
		}
		printf("%d %d\n",dex,min_bla);
	}
}; 