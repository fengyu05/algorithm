struct tnode{
	int id;
	tnode *l,*r,*p;
};
typedef tnode* ct;

ct ctree=new ct[maxN];

bool _cmp(item a,item b){return a<b;}
void BuildCTree(item a[],int n)
{// build the cartesian tree form a[0..n-1]
	int i,j,p;
	root=-1,cnt=0;
	for(i=0;i<n;i++)
	{
		p=cnt++;
		ctree[p].l=ctree[p].r=-1;
		ctree[p].d=i;
		if(root<0||_cmp(a[i],a[ctree[root].d]))
		{
			ctree[p].l=root;
			root=p;
		}else{
			j=i-1;
			while(1)
			{
				if(!_cmp(a[i],a[ctree[j].d]))
				{
					ctree[i].l=ctree[j].r;
					ctree[j].r=i;
					ctree[i].p=j;
					break;
				}
				j=ctree[j].p;
			}
		}
	}
}

struct tnode{
	int val;
	int l,r,p;
} ctree[maxN];

bool _cmp(int a,int b){return ctree[a].val<ctree[b].val;}
void BuildCTree(int n)
{// build the cartesian tree form ctree[0..n-1]
	int i,j,k;
	int root=-1;
	for(i=0;i<n;i++)
	{
		ctree[i].l=ctree[i].r=ctree[i].p=-1;
		if(root<0||_cmp(i,root)
		{
			ctree[i].l=root;
			ctree[root].p=i;
			root=i;			
		}else{
			j=i-1;
			while(1)
			{
				if(!_cmp(i,j))
				{
					ctree[i].l=ctree[j].r;
					ctree[j].r=i;
					ctree[i].p=j;
					break;
				}
				k=j;
				j=ctree[j].p;
				ctree[i].p=k;
			}
		}
	}
	return root;
}