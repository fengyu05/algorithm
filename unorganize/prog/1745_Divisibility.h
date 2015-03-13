// poj 1745 Divisibility
// ¶þÖµDP
// feng
#include <iostream>
using namespace std;

int n,k;
bool dp[10001][101];

void main()
{
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
    int i,j,tmp,val;	
	scanf("%d%d",&n,&k);
	memset(dp[0],0,sizeof(dp[0]));
	dp[0][0]=1;
	for(i=1;i<=n;i++){
		scanf("%d",&val);
		for(j=0;j<k;j++){
			if(dp[i-1][j]){
				// +
				tmp=((j+val%k)+k)%k;
				dp[i][tmp]=1;
				//-
				tmp=((j-val%k)+k)%k;
				dp[i][tmp]=1;
			}
		}
	}
	if(dp[n][0]) printf("Divisible\n");
	else printf("Not divisible\n");
}
