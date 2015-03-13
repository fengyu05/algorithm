#include <iostream>
using namespace std;
#define N 128
const double eps=1e-5;
#define genx (rand()%1000)/100.0
int dcmp(double x){
	if(x>eps) return 1;
	else if(x<-eps) return -1;
	else return 0;
}
double f(double a[],int n,double x){
	double ret=0,xx=1;
	for(int i=0;i<=n;i++){ ret+=a[i]*xx;xx*=x;}
	return ret;
}
double newton(double a[],double b[],int n){
	double dy,y,x=genx,lastx=x-1;
	while(y=f(a,n,x),dcmp(lastx-x)){
		lastx=x;dy=f(b,n-1,x);
		if(!dcmp(dy)) x=genx;
		else x=x-y/dy;
	}
	return x;
}
void solve(double a[],double x[],int n){
	int i,j;double b[N];
	for(j=n;j>0;j--){
		for(i=0;i<j;i++) b[i]=a[i+1]*(i+1);
		x[j-1]=newton(a,b,j);
		for(b[j]=0,i=j-1;i>=0;i--)
			b[i]=a[i+1]+b[i+1]*x[j-1];
		for(i=0;i<j;i++) a[i]=b[i];
	}
}
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int n;
	double a[N];
	double x[N];
	while(scanf("%d",&n)==1){
		a[n]=1;
		for(int i=n-1;i>=0;i--) scanf("%lf",&a[i]);
		solve(a,x,n+1);
		int re=0;		
	}
	return 0;
}