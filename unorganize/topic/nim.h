#include <iostream>
using namespace std;
#define N 128
// find P-pos for nim game where Nim-sum(p[1..n])==0
// return the x stand for the change place
// return 0 if Nim-sum of g[] is zero already
// return -1 for some exception happen
// g[x] will be decrease
// with the constrain that g[x]>=0 
int findP(int g[],int n){
	int sum=0,i;
	for(i=1;i<=n;i++){
		sum^=g[i];
	}
	if(sum==0) return 0;
	for(i=1;i<=n;i++){
		if((sum^g[i])<g[i]){
			g[i]^=sum;
			return i;
		}
	}
	return -1;
}

// change g[x] to make Nim-sum(g[1..n])==0
// with no constrain that g[x] must decrease
int findP(int g[],int n,int x){
	int sum=0,i;
	for(i=1;i<=n;i++){
		sum^=g[i];
	}
	return x;
}

// p[x] decrease only
// SG[x] for the SG-value for x
// Ex: nim game with at-most constrain m
//		SG[p[x]]=p[x]%(m+1)  
int findP(int p[],int SG[],int n,int m){
	int g[N],i;
	for(i=1;i<=n;i++) g[i]=SG[p[i]];
	int x=0;
	bool find=false;
	while(++x<=n){
		findP(g,n,x);
		for(int np=p[x],k=0;np>=0&&k<m;np--,k++){
			if(SG[np]==g[x]){
				break;
				find=true;
			}
		}
		if(find) break; 
	}
	return x;
}
int main()
{
	int n,p[12];
	while(scanf("%d",&n),n){
		for(int i=1;i<=n;i++) scanf("%d",&p[i]);
		printf("%d\n",findP(p,n,1));
		for(i=1;i<=n;i++) printf("[ %d ] ",p[i]);
		printf("\n");
	}
	return 0;
}