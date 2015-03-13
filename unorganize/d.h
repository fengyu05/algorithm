//#pragma warning(disable: 4786)
#pragma warning(disable: 4101)
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cassert>
//#include<map>
//#include<string>
using namespace std;
#define mset(a,v) memset(a,v,sizeof(a))
#define _clr(a) memset(a,0,sizeof(a))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define INF 1000000000
#define N 128

// data
int mat[N][N],dp[N][N];
int H,W,R;
void init(){
	mset(mat,0);
	mset(dp,-1);
}
int search(int x,int y){
	if(x<=0||y<=0) return 0;
	else if(x==1&&y==1) return 1;
	else if(mat[x][y]!=0) return 0;
	else if(dp[x][y]==-1){
		dp[x][y]=search(x-2,y-1)+search(x-1,y-2);
		if(dp[x][y]>=10007)
			dp[x][y]%=10007;
	}
	return dp[x][y];
}
void solve(){
	int i,j,k;
	scanf("%d%d%d",&H,&W,&R);
	while(R--){
		int x,y;
		scanf("%d%d",&x,&y);
		mat[x][y]=-1;
	}
	printf("%d\n",search(H,W)%10007);
}
int main()
{	
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int cas;
	scanf("%d",&cas);
	for(int ii=1;ii<=cas;ii++){
		printf("Case #%d: ",ii);
		init();
		solve();
	}
	return 0;
}