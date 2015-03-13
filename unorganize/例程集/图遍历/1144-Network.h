/*  1144-Network	
 * 112K	62MS	C++	1033B
 * fengyu05
 * 题目:求网络关键点个数
*/
#include <iostream>
#include <sstream>
using namespace std;
#define N 128

bool mat[N][N];
int n,d[N],low[N],mk[N];
int color,ti,cutv_cnt , cutv[N];
void dfsvisit(int u, int p)
{
	int v, s=0,bVertex=0;
	low[u]=d[u]=++ti ;
	mk[u]=-color ;
	for(v=1; v<=n; v++) if(mat[u][v] && v!=p)
		if (mk[v]==0){
			dfsvisit (v,u); s++;
			if (low[v]<low[u]) low[u]=low[v ];
			if (low[v]>=d[u]) bVertex=1;
		} else if(d[v]<low[u])
			low[u]=d[v ];
	if ((p && bVertex ) || (! p && s>1))
		cutv[cutv_cnt++]=u;
	mk[u]=color ;
}
void dfs(){
	memset(mk,0,sizeof(mk));
	color=ti=cutv_cnt=0;
	for(int i=1;i<=n;i++) if(!mk[i]){
		++color;
		dfsvisit(i,0);
	}
}
int main()
{
	char str[256];
	int x,y;
	while(scanf("%d\n",&n),n){
		memset(mat,0,sizeof(mat));
		while(gets(str),str[0]!='0'){
			stringstream ss;
			ss.str(str);
			ss>>x;
			while(ss>>y){
				mat[x][y]=mat[y][x]=1;
			}
		}
		dfs();
		printf("%d\n",cutv_cnt);
	}
	return 0;
} 