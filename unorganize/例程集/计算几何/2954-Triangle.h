/* 2954 Triangle
 * fengyu05
 * ����:��һ����Ϊ����������,�ڲ��ж��ٸ����
 * �ⷨ:Pick ��ʽ + gcd����ϵĸ��

Pick ��ʽ
�O �� ��ƽ�����Ը����c����c֮�μ���߅�Σ��t����e�� 
A= b/2+i-1
���� b ��߅���ϵĸ����c����i ��Ȳ��ĸ����c��.

����: i=A+1-b/2=(2*A-b)/2+1
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