/*  1164-The Castle	
 * 	112K	0MS	C++	1014B
 * fengyu05
 * 题目:已知迷宫(有向墙壁),求连通最大房间数
 * 解法:BFS
*/
#include <iostream>
#include <deque>
using namespace std;
int mat[51][51];
int flag[51][51]={0};
struct node{int x,y;node(int x,int y):x(x),y(y){} };
int num,max;
int change[4][2]={
	0,-1,
	-1,0,
	0,1,
	1,0
};
void BFS(int i,int j)
{
	flag[i][j]=1;
	int s=0,t=0;
	deque<node> qu;
	qu.push_back(node(i,j));
	int _max=0;
	while(qu.size()){
		node tmp=qu.front();
		qu.pop_front();
		_max++;
		int dir=mat[tmp.x][tmp.y];
		for(int i=3;i>=0;i--){
			if(dir<(1<<i)){
				int _x=tmp.x+change[i][0],_y=tmp.y+change[i][1];
				if(flag[_x][_y]==0){
					qu.push_back(node(_x,_y));
					flag[_x][_y]=1;
				}				
			}else dir-=(1<<i);
		}
	}
	if(_max>max) max=_max;
}

int main()
{
	int n,m,i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			scanf("%d",&mat[i][j]);
	num=0,max=0;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++){
			if(flag[i][j]==0){
				num++;
				BFS(i,j);
			}
		}
	printf("%d\n%d\n",num,max);
}

