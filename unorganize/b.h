#include<iostream>
#include<algorithm>
#include<cmath>
#include<cassert>

using namespace std;
#define EP 10000
double rpow(double x,int n){
	if(n==1) return x;
	else{
		double t;
		t=rpow(x,n/2);
		t*=t;
		if(t>(EP*1.0)){
			int ii=(int)t;
			t=t-((ii/EP)*EP*1.0);				
		}
		if(n%2==1){
			t*=x;
			if(t>(EP*1.0)){
				int ii=(int)t;
				t=t-((ii/EP)*EP*1.0);				
			}
		}
		return t;
	}
}
int main()
{	

	freopen("t.in", "r", stdin);
	//freopen("t.out","w",stdout);

	int cas;
	scanf("%d",&cas);
	for(int ii=1;ii<=cas;ii++){
		printf("Case #%d: ",ii);
		int n;
		scanf("%d",&n);
		double base=sqrt(5)+3;
		double re=rpow(base,n);
		int res=(int)floor(re);
		printf("%03d\n",res%1000);
	}
	return 0;
}