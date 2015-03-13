/* Christmas(07.zsu Preliminary)
   求最大边最小的完全匹配
   解:二分枚举每条边,删除比它大的边,求是否有完成匹配
*/
#include <iostream>
#include <algorithm>
using namespace std;
#define N 16
#define INF 0x7fffffff
#define _clr(ar) memset(ar,0,sizeof(ar))

int nx,ny,cx[N],cy[N];
bool mat[N][N],sy[N];
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
int age[2*N],hi[2*N],edge[N][N],E[N*N];
int out[N*N];
bool cmp(int i,int j){ return E[i]<E[j];}
int mark(int i,int j){
	int h=hi[i]-hi[j];
	int a=age[i]-age[j];
	return h*h+a*a;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
   int n,i;
   scanf("%d",&n);
   for(i=1;i<=2*n;i++){
	   scanf("%d%d",&hi[i],&age[i]);
   }
   for(i=1;i<=n;i++){
	   for(int j=1;j<=n;j++){
			edge[i][j]=mark(i,n+j);
			E[(i-1)*n+j]=mark(i,n+j);
	   }
   }
	for(i=1;i<=n*n;i++) out[i]=i;
	sort(out+1,out+n*n+1,cmp);
	nx=ny=n;
	int l=1,r=n*n;
	int re=INF;
	while(l<r){
		int mid=(l+r)/2;
		int tmp=E[out[mid]];
		_clr(mat);
		for(i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				if(edge[i][j]<=tmp)
					mat[i][j]=1;
			}
		if(MaxMatch()==n){
			if(re>tmp) re=tmp;
			r=mid-1;
		}else{
			l=mid+1;
		}
	}
	printf("%d\n",re);
   return 0;
}