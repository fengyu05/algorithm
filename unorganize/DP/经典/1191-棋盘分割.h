/* 1191 ∆Â≈Ã∑÷∏Ó
 */
#include <iostream>
#include <cmath>
using namespace std;
#define N 9
#define INF 0x7fffffff
#define min(a,b) ((a)<(b)?(a):(b))
int k[N][N];
int s[N][N];
int d[50][N][N][N][N];
int query_sum(int x1,int y1,int x2,int y2){
	return s[x2][y2]+s[x1-1][y1-1]-s[x2][y1-1]-s[x1-1][y2];
}
int sq(int x){ return x*x;}
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int m=8,n;
	scanf("%d",&n);
	double x=0;
	int i,j;
	for(i=1;i<=m;i++)
		for(j=1;j<=m;j++){
			scanf("%d",&k[i][j]);
			x+=k[i][j];
		}
	x/=n;
	memset(s,0,sizeof(s));
	memset(d,0,sizeof(d));
	for(i=1;i<=m;i++)
		s[1][i]=s[1][i-1]+k[1][i];
	for(i=1;i<=m;i++){
		int sum=0;
		for(j=1;j<=m;j++){
			sum+=k[i][j];
			s[i][j]=s[i-1][j]+sum;
		}
	}
	int x1,y1,x2,y2;
	for(x1=1;x1<=m;x1++)
		for(y1=1;y1<=m;y1++)
			for(x2=x1;x2<=m;x2++)
				for(y2=y1;y2<=m;y2++)
					d[0][x1][y1][x2][y2]=sq(query_sum(x1,y1,x2,y2));
	for(int cut=1;cut<n;cut++){
		for(x1=1;x1<=m;x1++)
			for(y1=1;y1<=m;y1++)
				for(x2=x1;x2<=m;x2++)
					for(y2=y1;y2<=m;y2++){
						int _min=d[0][x1][y1][x2][y2];
						for(int a=x1;a<x2;a++){
							int tmp=
								min(d[cut-1][x1][y1][a][y2]+d[0][a+1][y1][x2][y2],
								d[0][x1][y1][a][y2]+d[cut-1][a+1][y1][x2][y2]);
							if(tmp<_min) _min=tmp;
						}
						for(int b=y1;b<y2;b++){
							int tmp=
								min(d[cut-1][x1][y1][x2][b]+d[0][x1][b+1][x2][y2],
								d[0][x1][y1][x2][b]+d[cut-1][x1][b+1][x2][y2]);
							if(tmp<_min) _min=tmp;
						}
						d[cut][x1][y1][x2][y2]=_min;
					}
	}
	double re=d[n-1][1][1][m][m];
	re=(re/n)-x*x;
	printf("%.3lf\n",sqrt(re));
	return 0;
}