/*
 1185 炮兵阵地
 fengyu05
 状态压缩DP + 滚动数组 + DFS预处理 + 最优性剪枝
**
  1.确定状态压缩的表示
  2.确定状态
  3.判断两种状态是否可以转移
  4.转移
*/
#include<iostream>
#include<algorithm>
using namespace std;
int countbit(int x){
	int re=0;
	while(x>0){
		re+=x%2;
		x/=2;
	}return re;
}
#define N 1024
int n,m;
int valid[128][N];//可行放置
// valid[x][id]=countbit(id) :可行
// valid[x][id]=-1 :不可行
char map[16];//当前行地图，用于DFS
char X[16];
void DFS(int x,int pos){
	if(pos==m){
		int id=0;
		for(int i=0;i<m;i++){
			id=id*2+X[i];
		}
		valid[x][id]=countbit(id);
	}else{
		bool canplace=(map[pos]=='P');
		if(canplace){
			for(int i=1;i<=2;i++){
				if(pos-i<0) break;
				if(X[pos-i]==1){
					canplace=false;
					break;
				}
			}
		}
		if(canplace){
			X[pos]=1;
			DFS(x,pos+1);
		}
		X[pos]=0;
		DFS(x,pos+1);
	}
}
int f[2][N][N];
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int i,j;
	scanf("%d %d\n",&n,&m);
	int end=(1<<m);
	memset(valid,-1,sizeof(valid));
	for(i=0;i<n;i++){
		int re=0;
		scanf("%s",map);
		memset(X,0,sizeof(X));
		DFS(i,0);//DFS确定可行放置
	}
	if(n==1){ 
		printf("%d\n",*max_element(valid[0],valid[0]+end));
		return 0;
	}
	int _max=0;
	memset(f[1],0,sizeof(f[1]));
	for(i=0;i<end;i++) if(valid[0][i]>=0){
		for(j=0;j<end;j++) if(valid[1][j]>=0){
			if( (i&j)==0 )
			{
				f[1][i][j]=valid[0][i]+valid[1][j];
				if(f[1][i][j]>_max) _max=f[1][i][j];
			}
		}
	}
	//数组滚动
	for(int cnt=2;cnt<n;cnt++){
		int cur=cnt%2,pre=(cnt-1)%2;
		memset(f[cur],0,sizeof(f[cur]));
		for(i=end-1;i>=0;i--) if(valid[cnt-2][i]>=0){//注意循环顺序
			for(j=end-1;j>=0;j--) if(valid[cnt-1][j]>=0){
				if((i&j)!=0) continue;
				if(f[pre][i][j]+m/2<_max) continue;//最优性剪枝
				for(int k=end-1;k>=0;k--) if(valid[cnt][k]>=0){//
					if( (k&i)==0 && (k&j)==0 ){
						int tmp=f[pre][i][j]+valid[cnt][k];
						if(f[cur][j][k]<tmp){
							if(tmp>_max) _max=tmp;
							f[cur][j][k]=tmp;							
						}
					}					
				}
			}
		}
	}
	printf("%d\n",_max);
	return 0;
}