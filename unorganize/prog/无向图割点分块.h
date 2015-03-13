bool mat[N][N],mk[N];
int n,d[N],low[N],len,que[N];
int time, cnt, cutv[N], blocknum;
void dfs_rc(int u, int p)
{
	int v, s=0,bCutvertex=0;
	low[u]=d[u]=++time ;
	mk[u]=1;
	que[++len]=u;
	for(v=1; v<=n; v++) if (mat[u][ v] && v!=p)
		if(mk[v]==0)
		{
			dfs_rc (v,u); s++;
			if (low[v]<low[u]) low[u]=low[v ];
			if (low[v]>=d[u]){
				while(que[len]!=v) cout<<que[len--]<<" ";
					cout<<que[len--]<<" "<<u<<endl ;
				bCutvertex=1; blocknum++;
			}
		} else if (d[v]<low[u]) low[u]=d[v ];
	if ((p && bCutvertex ) || (! p && s>1)) cutv[cnt++]=u;
}
void block()
{	
	memset(mk,0,sizeof(mk));
	time=cnt=blocknum=0;
	for(int i=1;i<=n;i++) if(!mk[i]){
		len=0;
		dfs_rc(i,0);
		if (len >1 || d[i]==time ){
			while(len >1) cout<<que[len--]<<" ";
			cout<<i<<endl;blocknum++;
		}
	}
	printf("Block Number : %d\n",blocknum);
	printf("Cutvertex Number: %d\n",cnt);
	for( i=0;i<cnt; i++) printf("%d ",cutv[i]);
	printf("\n");
}