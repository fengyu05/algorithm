/*******************************
DFS adj-matrix version
mat[][] 0 no edge , 1 visitable, -1: unvisitable
for graph after i-j is visit put mat[i][j]=-1

ed[][] 0 no edge, 1 tree ,2 back ,3 down ,4 cross
d[]: start time
f[]: finish time
c[]: color 0:white, -1:gray, 1:black
p[]: p-link
low[]:
low[u] = min(low[u], d[w])    visit {u,w}
         min(low[u], low[s])  after all u's childern s had been visited

/*******************************/
#define N 128
#define E 8
#define _clr(ar) memset(ar,0,sizeof(ar));

int n, mat[N][N],deg[N], ed[N][N];
int d[N], f[N], low[N], p[N], c[N] ;
int time;

void dfs_rc(int u){
	c[u] = -1; //remove for digraph
	time++; d[u] = low[u] = time;
	for(int v = 1; v<=n; v++) if(mat[u][v] > 0)
	{
		if(c[v] == 0)//white
		{         
			mat[v][u] = -1;//mark as unvisitable ,remove for digraph
			ed[u][v] = 1;//tree
			deg[u]++;        
			p[v] = u;
			dfs_rc(v);
			if(low[v] < low[u])	low[u] = low[v];
			mat[v][u] = 1; //recover as visitable
		}else if(c[v] < 0) { //gray
			if(low[v] < low[u])	low[u] = low[v];
			ed[u][v] = 2;    //back
		}else {       //black
			if(d[v] > d[u])	ed[u][v] = 3; //down
			else ed[u][v] = 4; //cross
		}
	}
	c[u] = 1;
	time++; f[u] = time;
}

void DFS(){
	_clr(deg),_clr(c),_clr(ed);
	time = 0;
	for(int u = 1; u <= n; u++)
		if(c[u] == 0){
			p[u] = 0;
			dfs_rc(u);
		}
}

//  adj-list version
int adj[N][E],deg[N],n;
int d[N],f[N],c[N],time;
int pre[N],post[N],p[N],low[N];

int pre_ord,post_ord;
int ed[N][E];

void dfs_rc(int u){
	//c[u]=-1,d[u]=(++time);
	pre[u]=pre_ord++;
	low[u]=pre[u];
	for(int i=0;i<deg[u];i++){
		int vec=adj[u][i];
		if(pre[vec]==0){ //c[u]==0
			ed[u][i]=1;//tree edge
			p[vec]=u;
			dfs_rc(vec);
			if(low[u]>low[vec]) low[u]=low[vec];
			if(low[vec]==pre[vec]); //bridge				
		}else if(post[vec]==0){
			ed[u][i]=2;//back edge
			if(low[u]>low[vec]) low[u]=low[vec];
		}else if(pre[vec]>pre[u]){
			ed[u][i]=3;//down edge
		}else{
			ed[u][i]=4;//cross edge
		}
	}
	post[u]=post_ord++;
	//c[u]=1,f[u]=(++time);
}
void DFS(){
	for(int i=0;i<n;i++){
		c[i]=pre[i]=post[i]=0;
	}
	pre_ord=post_ord=time=0;
	for(int u=1;u<=n;u++){		
		if(pre[u]==0){
			p[u]=0;
			dfs_rc(u);
		}
	}
}




//2: 求割点和桥

// bridge
//在任何DFS树中,不存在后向边连通w的后代与w的祖先时,树边{u,v}为桥
// 树边{u,v}中有 low[v]==d[v]
bool mat[N][N],mk[N];//mat[1..n]
int n,d[N],low[N];
int time, b_cnt , b_u[N] , b_v[N];
void dfs_rc(int u, int p)
{
	mk[u]=1;
	low[u]=d[u]=time++;
	for(int v=1;v<=n;v++) if(mat[u][v] &&v!=p)
		if(mk[v]==0)
		{
			dfs_rc(v,u);
			if (low[v]<low[u]) low[u]=low[v];
			if (low[v]==d[v]){
				b_u[b_cnt]=u;
				b_v[b_cnt++]=v;
			}
		}else if(d[v]<low[u]) low[u]=d[v];
}
void bridge()
{
	memset(c,0, sizeof(c));
	time=b_cnt=0;
	for(int i=1;i<=n;i++) if(!mk[i]){
		dfs_rc(i,0);
	}
}

// cut vertex
//规则1: 如果root节点又多于一个1子节点 则root是割点
//规则2: 如果一个节点u有某一个子节点v不含到u的祖先节点的后向边 则u为割点
//v是u子节点,有(p[u] == 0 && deg[v] > 1) || (p[u] > 0 && low[v] >= d[u])

bool mat[N][N],mk[N];
int n,d[N],low[N];
int time,cnt,cutv[N];
void def_rc(int u, int p)
{
	int s=0,bVertex=0;
	low[u]=d[u]=time++;
	mk[u]=1;
	for(int v=1;v<=n;v++) if(mat[u][v] &&v!=p)
		if (mk[v]==0){
			def_rc(v,u); s++;
			if (low[v]<low[u]) low[u]=low[v];
			if (low[v]>=d[u]) bVertex=1;
		}else if(d[v]<low[u])
			low[u]=d[v];
	if((p && bVertex ) || (!p && s>1))
		cutv[cnt++]=u;
}
void cut_vertex()
{
	memset(mk,0,sizeof(mk));
	time=cnt=0;
	for(int i=1;i<=n;i++) if(!mk[i]){
		def_rc(i,0);
	}
}

//3: biparttiteness 二分性,二着色,奇环
int adj[N][E],deg[N],n;
int color[N];
bool dfs_rc(int u,int c){
	color[u]=c;
	for(int i=0;i<deg[u];i++){
		int v=adj[u][i];
		if(color[v]==0){
			if(!dfs_rc(v,-c))
				return false;
		}else if(color[v]==c)
			return false;		
	}
	return true;
}
bool bipart(){
	memset(color,0,sizeof(color));
	for(int u=1;u<=n;u++)
		if(color[u]==0&&!dfs_rc(u,1))
			return false;
	return true;
}
// 无向图割点分块
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
/*  DFS 框架
Procedure DFS(节点编号k, k的父亲节点编号father, deep:integer)
var i, tot : integer;
begin
	C[k] = -1; {灰色}
	D[k] = deep; {记录深度}
	low[k] = deep, tot = 0;
	for i = 1->n
	begin
		if(节点i和k相连) and (i != father) and (Ci = -1)
		then low[k] = Min(low[k], Di);
		if(节点i与k相连) and (Ci = 0) then
		begin
			DFS(i, k, deep + 1);
			tot++, low[k] = Min(low[k], low[i]);
			if(k == Root) and (tot > 1) or
			( (k != Root) and (low[i] >= D[k]) )
			then Cut[k] = true;
			if(low[i] > D[k]) then Brige[k][i] = true
		end
	end
	C[k] = 1; //黑色
	time++, A[i] = time;
end;
*/
