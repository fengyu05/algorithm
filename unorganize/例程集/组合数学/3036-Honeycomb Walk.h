/* 3036 Honeycomb Walk
蜂巢为六边形
求蜜蜂窝走N步回到出发地的方法数
*/
#include <iostream>
using namespace std;
int d[16][16][16];
void main()
{
	d[0][0][0]=1;
	for(int i=1;i<=14;i++){
		d[i][0][0]=6*d[i-1][1][0];
		for(int j=1;j<=14;j++){
			d[i][j][0]=d[i-1][j-1][0]+
				d[i-1][j][1%j]+d[i-1][j][(j-1)%j]+
				d[i-1][j+1][1%(j+1)]+d[i-1][j+1][0]+d[i-1][j+1][j%(j+1)];
			for(int k=1;k<j;k++){
				d[i][j][k]=d[i-1][j-1][(-1+k+j-1)%(j-1)]+d[i-1][j-1][k%(j-1)]+
					d[i-1][j][(-1+k+j)%j]+d[i-1][j][(1+k)%j]+
					d[i-1][j+1][k%(j+1)]+d[i-1][j+1][(1+k)%(j+1)];
			}
		}
	}
	int n,m;
	for(i=1;i<=14;i++){
		printf("%d: %d\n",i,d[i][0][0]);
	}
}
