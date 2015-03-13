// 双向欧拉回路
int d[N],time,path[N*2],cnt;
void dfs(int v,int w){
	//printf("%d\n",w);
	path[cnt++]=w;
	d[w]=++time;
	for(int j=0;j<deg[w];j++){
		int u=adj[w][j];
		if(d[u]==0) dfs(w,u);
		else if(d[u]<d[v]){
			path[cnt++]=u;
			path[cnt++]=w;
			//printf("%d\n%d\n",u,w);
		}
	}
	if(v!=w){
		//printf("%d\n",v);
		path[cnt++]=v;
	}
}
void twowayEuler(int v){
	memset(d,0,sizeof(d));
	time=cnt=0;
	dfs(v,v);	
}

// 欧拉路径存在性
bool exist(){ // tour
	int odd=0;
	for(int t=0;t<n;t++)//[0,n)
		if(deg[t]%2) odd++;
	return odd==0||odd==2;
}
bool exist(int v,int w){
	int t=deg[v]+deg[w];
	if(t%2) return false;
	for(t=0;t<n;t++){ //[0,n)
		if(t!=v&&t!=w&&deg[t]%2)
			return false;
	}
	return true;
}

// 有向图欧拉回路
bool flag[N][E];
int path[E*N],cnt;
int stack[N],top;

void FindEluer(int v){
	memset(flag,0,sizeof(flag));
	top=cnt=0;
	stack[top++]=v;
	while(top>0){
		v=stack[top-1];
		bool isfind=false;
		for(int j=0;j<deg[v];j++) if(flag[v][j]==0&&flag[j][v]==0){
			flag[v][j]=1;
			stack[top++]=adj[v][j];
			isfind=true;
			break;
		}
		if(!isfind){
			path[cnt++]=stack[--top];
		}
	}
	//	reverse(path,path+cnt);
}

//无向图欧拉回路 
bool mat[N][N],flag[N][N];
int n;
int path[E*N],cnt;
int stack[N],top;

void FindEluer(int v){
	memset(flag,0,sizeof(flag));
	top=cnt=0;
	stack[top++]=v;
	while(top>0){
		v=stack[top-1];
		bool isfind=false;
		for(int j=1;j<=n;j++) if(mat[v][j]&&flag[v][j]==0){
			flag[v][j]=1;
			flag[j][v]=1;
			stack[top++]=j;
			isfind=true;
			break;
		}
		if(!isfind){
			path[cnt++]=stack[--top];
		}
	}
	reverse(path,path+cnt);
}
