#include <cstdio>
int main(){
#ifndef ONLINE_JUDGE
	freopen("I:\\acm\\acm\\input.txt", "r", stdin);
#endif
#define SIZE 202
	int n,p[SIZE],q[SIZE],e[SIZE][SIZE],w[SIZE][SIZE];
	while(scanf("%d",&n)&&n!=0){
		int i;
		for(i=1;i<=n;i++)
			scanf("%d",&p[i]);
		for(i=0;i<=n;i++){
			scanf("%d",&q[i]);
			e[i+1][i]=0;
			w[i+1][i]=q[i];
		}
		for(int l=1;l<=n;l++){
			for(i=1;i<=n-l+1;i++){
				int j=i+l-1;
				e[i][j]=-1;  // mark unlimits as -1;
				w[i][j]=w[i][j-1]+p[j]+q[j];
				for(int r=i;r<=j;r++){
					int t=e[i][r-1]+e[r+1][j]+w[i][j];
					if(t<e[i][j]||e[i][j]==-1)
						e[i][j]=t;
				}
			}
		}
		printf("%d\n",e[1][n]);
	}
    return 0;
}
