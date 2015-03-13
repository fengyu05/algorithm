// 有向图 & DAG 算法  
//一 可达性,传递闭包 - transitive closure

// 1: warshall for matrix
bool mat[N][N];
int n;
void warshall(){ //[1..n]		
	for(int i=1;i<=n;i++){	// i
		mat[i][i]=1;	//add self loop
		for(int s=1;s<=n;s++) // s
			if(mat[s][i])
				for(int t=1;t<=n;t++)  //t
					if(mat[i][t]) mat[s][t]=1;
	}
}
// 2: for DAG
int tc[N][N],d[N],time;
void dfs_rc(int v){
	d[v]=++time;
	for(int w=1;w<=n;w++) if(mat[v][w]){
		tc[v][w]=1;
		if(d[w]>d[v]) continue;
		if(d[w]==0) dfs_rc(w);
		for(int t=1;t<=n;t++)
			if(tc[w][t]==1) tc[v][t]=1;
	}
}
void DAGtc(){
	memset(tc,0,sizeof(tc));
	memset(d,0,sizeof(d));
	time=0;
	for(int v=1;v<=n;v++)
		if(d[v]==0)	dfs_rc(v);
}
// 3: dfs for adj-list
int tc[N][N];
void dfs_rc(int v,int w){
	tc[v][w]=1;
	for(link lk=adj[w];lk;lk=lk->next){
		int t=lk->u;
		if(tc[v][t]==0)	dfs_rc(v,t);
	}
}
void closure(){
	memset(tc,0,sizeof(tc));
	for(int v=1;v<=n;v++) dfs_rc(v,v);
}

//二 拓扑排序 - Topological Sort

//1: use dfs for matrix 
// DFS之后按照结束访问时间反向排序,
// 如果在DFS过程中出现后向边(成环),则无法TOPO
int n,mk[N],pos,ord[N]; //ord[0,n)
bool mat[N][N],topo; //mat[1..n]
void dfs(int v)
{
	if(mk[v]<0){ topo=false; return ;}
	if(mk[v]>0) return ;
	else mk[v]=-1;
	for(int w=1; topo && w<=n; w++)
		if(mat[v][w]) dfs(w);
	ord[--pos]=v; mk[v]=1;
}
void toposort(){
	topo=true; pos=n;
	memset(mk,0, sizeof(mk));
	for(int i=1;topo && i<=n; i++)
		if(!mk[i]) dfs(i);
}

//2: use queue for adj-list
int ord[N];
void tpsort(){
	int i,s=-1,t=-1;
	int in[N]={0};
	for(i=1;i<=n;i++)
		for(link t=adj[i];t;t=t->next)
			in[t->u]++;
	for(i=1;i<=n;i++) if(in[i]==0) ord[++t]=i;
	while(s<t){
		int v=ord[++s];
		for(link pt=adj[v];pt;pt=pt->next){
			int w=pt->u;
			if(--in[w]==0)
				ord[++t]=w;
		}
	}
}

//三 强连通分量 - Strongly Connected Component
// 1: Kosaraju 
// reverse graph+two DFS
int mk[N],ord[N],sc[N],pos,cnt;
void back(int v)
{
	mk[v]=1;sc[v]=cnt;
	printf("%d ",v);
	for(int w=1;w<=n; w++) 
		if(!mk[w] && mat[v][w]) back(w);
}
void dfs(int v){
	mk[v]=1;
	for(int w=1;w<=n;w++)// w-v for reverse graph
		if(!mk[w]&&mat[w][v]) dfs(w);
	ord[pos--]=v;
}
void SCC(){
	pos=n; cnt=0;
	memset(mk,0,sizeof(mk));	
	for(int i=1;i<=n;i++){ 
		if(!mk[i]) dfs(i);
	}
	memset(mk,0,sizeof(mk));
	for(int j=1;j<=n;j++) if(!mk[ord[j]]){
		++cnt;
		printf("Strong Component %d: ",cnt);
		back(ord[j]);
		printf("\n");
	}
}

// 2: Tarjan for adj-list
int d[N],low[N],sc[N],time,stack[N],top,cnt;
void dfs_rc(int v){
	d[v]=low[v]=++time;
	int min=low[v];
	stack[top++]=v;
	for(link t=adj[v];t;t=t->next){
		int w=t->u;
		if(d[w]==0) dfs_rc(w);
		if(low[w]<min) min=low[w];
	}
	if(min<low[v]){ low[v]=min; return; }
	cnt++;
	do{	int w;
		sc[ w=stack[--top] ]=cnt;
		low[w]=n;
	}while(stack[top]!=v);
}
void SCC(){
	memset(d,0,sizeof(d));
	time=top=cnt=0;
	for(int i=1;i<=n;i++){
		if(d[i]==0) dfs_rc(i);
	}
}

// 四 核心DAG - Ker DAG
int dag[N][N];
void KerDAG(){
	memset(dag,0,sizeof(dag));
	SCC();
	for(int i=1;i<=n;i++)
		for(link t=adj[i];t;t=t->next){
				dag[sc[i]][sc[t->u]]=1;
		}
	//DAGtc();
}
bool reach(int s,int t){ return tc[sc[s]][sc[t]];}