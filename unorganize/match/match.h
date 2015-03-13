// Maximum Matching on Bipartite Graph
/*
(1) 二分图点覆盖数:选择若干个点的点集,使得每条边至少有一点属于该点集
    定理:  最小覆盖数 = 最大匹配数
APP:
1.任务安排
问题:有A,B两台机器,分别有Ma,Mb个模式,有N个任务,每个任务在A上ai模式或B上bi模式运行
     转换模式时需要重启,问最少重启次数.
建图:以A,B的模式为点,建立二分图,以任务为边.ai与bi有边 iff 任务i可以在模式ai或bi上运行
     求最小覆盖

(2) 二分图独立数:选择若干个点的点集,使得任意两点不存在相连的边
    定理: 最大独立数 = 顶点数 - 最大匹配数
APP:
1.棋盘上的骑士
问题:问一棋盘上最多摆放多少个骑士,并使他们不互相攻击
建图:以棋盘上的方格为点,建立二分图.两点有边 iff 两点可以互相攻击
     求最大独立点集

(3) 无环图(DAG)最小路径覆盖:用不相交的简单路径覆盖图上所以顶点,使得路径数最少
    建图:将所有顶点i拆成二分图X中i和Y中的i',i和j'有边 iff i->j为原图中的边
	定理:最小路径覆盖 = 顶点数 - 最大匹配数
求具体路径的时候顺着匹配边走就可以，匹配边i→j',j→k',k→l'....构成一条有向路径。
*注,该二分图不能含有边i->i'
APP:
1.街道巡逻
问题:一小镇有若干条有向街道(无环),分配最少的警卫,使他们经过所有的街道交点
     并且任两个警卫不能相遇
2.Treasure Exploration(POJ2594)
解:求传递闭包后,去掉所有边i->i,求最少路径覆盖

综合例子:皇家卫士
1.皇家城堡由N*M的矩形,由空地和墙组成.安排最多警卫,使他们视线互不相交
建图:在城堡外围建墙,把无法再上下(左右)扩展的线段称为列(行)线段.
     分别以行列作为二分图X,Y部,建立二分图,两点有边 iff 该交点为空地
	 求最大匹配

2.Shooting Contest(POJ1719)
*注意这种不对称的匹配
每列对应一行,但一行可以对应多列(至少为一)
解:以列为X部,行为Y部,建立有向二分图(X->Y),匹配后将剩下的c-r列随意做可行搭配

3.Christmas(07.zsu Preliminary)
求最大边最小的完全匹配
解:二分枚举每条边,删除比它大的边,求是否有完成匹配
*/
//-----------------------------Algorithm------------------------------------
#define N 128
#define _clr(ar) memset(ar,0,sizeof(ar))
//----------------- adj-matrix version -------------------------------------
// use DFS
int nx,ny,cx[N],cy[N];
bool mat[N][N],sy[N];
// must be [1..nx][1..ny]
int path(int u){
	for(int v=1;v<=ny;v++) if(mat[u][v] && !sy[v]){
		sy[v]=1;
		if (!cy[v]||path(cy[v])){
			cx[u]=v,cy[v]=u;
			return 1;
		}
	} return 0;
}
int MaxMatch(){
	int ret=0;
	_clr(cx),_clr(cy);
	for(int i=1;i<=nx; i++) if(!cx[i]){
		_clr(sy);
		ret+=path(i);
	}
	return ret ;
}
//---------------- adj-list version ---------------------------------------
struct node
{	int u;
	node* next;
	node(int u,node *next=0):u(u),next(next){}
}; typedef node* link;
link adj[N];
void insert(int x,int y){adj[x]=new node(y,adj[x]);}
int nx,ny,cx[N],cy[N];
bool sy[N];
int path(int u){
	for(link lk=adj[u];lk;lk=lk->next){
		int v=lk->u;
		if(!sy[v]){
			sy[v]=1;
			if (!cy[v]||path(cy[v])){
				cx[u]=v,cy[v]=u;
				return 1;
			}	
		}
	}return 0;
}
int MaxMatch(){
	int ret=0;
	_clr(cx),_clr(cy);
	for(int i=1;i<=nx; i++) if(!cx[i]){
		_clr(sy);
		ret+=path(i);
	}
	return ret ;
}