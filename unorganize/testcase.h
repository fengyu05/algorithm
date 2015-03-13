//
#include"MACRO/UTT.h"
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;

#define INF 1000000000
#define N 128

// data
int p[N];
int n;
void init(){
	CLEAR(p,0);
}
void solve(){
	int i,j,k;
	scanf("%d",&n);
	printf("n=%d\n",n);
}
int main()
{	
	REIN("t.in");
	int cas;
	scanf("%d",&cas);
	for(int ii=1;ii<=cas;ii++){
		printf("Case #%d: ",ii);
		init();
		solve();
	}
	return 0;
}