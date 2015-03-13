/* 2954 Triangle
 * fengyu05
 * 问题:求一顶点为格点的三角形,内部有多少个格点
 * 解法:Pick 公式 + gcd求边上的格点

Pick 公式
設 Γ 為平面上以格子點為頂點之單純多邊形，則其面積為 
A= b/2+i-1
其中 b 為邊界上的格子點數，i 為內部的格子點數.

所以: i=A+1-b/2=(2*A-b)/2+1
*/
#include <iostream>
using namespace std;
int gcd(int x,int y){
	while(y){
		int tmp=x;
		x=y,y=tmp%y;
	}
	return x;
}
int main()
{	
	int x[3],y[3];
	while(scanf("%d%d%d%d%d%d",&x[0],&y[0],&x[1],&y[1],&x[2],&y[2])==6){
		if(x[0]==0&&x[1]==0&&x[2]==0&&y[0]==0&&y[1]==0&&y[2]==0)
			break;
		int b=0;
		for(int j=0;j<3;j++){
			for(int k=j+1;k<3;k++){
				int xx=abs(x[j]-x[k]);
				int yy=abs(y[j]-y[k]);
				if(xx>yy) swap(xx,yy);
				if(xx==0){
					b+=yy;
					continue;
				}
				else{
					b+=gcd(xx,yy);
				}
			}
		}
		int x1=x[1]-x[0],x2=x[2]-x[0];
		int y1=y[1]-y[0],y2=y[2]-y[0];
		int A2=abs(x1*y2-x2*y1);
		int i=(A2-b)/2+1;
		printf("%d\n",i);
	}
	return 0;
}