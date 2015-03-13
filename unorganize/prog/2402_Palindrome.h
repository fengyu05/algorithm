/* 生成第n个回文 */
#include <iostream>
#include <cmath>
using namespace std;
int inv_num(int a){
	int re=0;
	while(a){
		re=re*10+a%10;
		a/=10;
	}
	return re;
}
int main()
{
#define N 19
	int cnt[N];
	cnt[0]=0;
	for(int i=1,t=9;i<N;i+=2,t*=10){
		cnt[i]=cnt[i-1]+t;
		cnt[i+1]=cnt[i]+t;
	}
	int n;
	while(scanf("%d",&n),n){
		for(i=1;i<N;i++) if(cnt[i]>=n) break;
		if(i==1)
			printf("%d\n",n);
		else if(i==2) printf("%d%d\n",n-cnt[i-1],n-cnt[i-1]);
		else if(i&1){
			int dif=n-cnt[i-1]-1,len=(i-1)/2;
			int offset=pow(10,len);
			dif+=offset;
			printf("%d%0*d\n",dif,len,inv_num(dif/10));			
		}else{
			int dif=n-cnt[i-1]-1,len=i/2;
			int offset=pow(10,len-1);
			dif+=offset;
			printf("%d%0*d\n",dif,len,inv_num(dif));
		}
	}
}