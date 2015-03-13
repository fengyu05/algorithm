/*
 1179 Polyon
 fengyu05
 DP
*/
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
#define INF 0x3fffffff
	char cc[64];
	int p[64];
	int n;
int go(){
	int max[64][64],min[64][64];
	int i,j;
	for(i=0;i<n;i++) max[i][i]=min[i][i]=p[i];
	for(int k=1;k<n;k++){
		for(i=0;i<n-k;i++){
			j=i+k;
			int mx,mn;
			max[i][j]=-INF;
			min[i][j]=INF;
			for(int q=i;q<j;q++){
				int a=max[i][q],b=min[i][q];
				int c=max[q+1][j],d=min[q+1][j];
				if(cc[q+1]=='t'){
					mx=a+c;
					mn=b+d;
					if(mx>max[i][j]) max[i][j]=mx;
					if(mn<min[i][j]) min[i][j]=mn;
				}else{
					int e[4];
					e[0]=a*c;e[1]=a*d;e[2]=b*c;e[3]=b*d;
					mx=*max_element(e,e+4);
					mn=*min_element(e,e+4);
					if(mx>max[i][j]) max[i][j]=mx;
					if(mn<min[i][j]) min[i][j]=mn;
				}
			}
		}
	}
	return max[0][n-1];
}
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif

	cin>>n;
	int i;
	for(i=0;i<n;i++){
		cin>>cc[i]>>p[i];
	}
	int mm=-INF;
	int re[64],r_cnt=0;
	for(int cas=1;cas<=n;cas++){		
		int tmp=go();
		if(tmp>mm){
			mm=tmp;
			r_cnt=0;
			re[r_cnt++]=cas;
		}else if(tmp==mm){
			re[r_cnt++]=cas;
		}
		rotate(p,p+1,p+n);
		rotate(cc,cc+1,cc+n);
	}
	printf("%d\n",mm);
	for( i=0;i<r_cnt;i++)
		printf("%d ",re[i]);
	printf("\n");
	return 0;
}