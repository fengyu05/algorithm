#include<iostream>
#include<ctime>
using namespace std;
typedef unsigned __int64 i64;
#define mod(a,b) ((a%b+b)%b)
i64 gcd(i64 x,i64 y){
	while(y){
		i64 tmp=x;
		x=y,y=tmp%y;
	}
	return x;
}
// a*b mod n
i64 mod_mul(i64 a, i64 b, i64 n)
{
	if(a<=0) return 0;
	return ( ((a&1)*b)%n + (mod_mul(a>>1,b,n)<<1)%n )%n;
}
//a^b mod n
i64 mod_exp(i64 a, i64 b, i64 n)
{
	i64 t=1,y=a;
	while(b!=0){
		if (b&1) t=mod_mul(t,y,n);
		y=mod_mul(y,y,n);
		b>>=1;
	}
	return t;
}

//.--------- Rabin Miller Test ---------------------

i64 myrand(){	return rand(); }
bool Rabin_Miller(i64 x){	
	if(x<2) return false;
	if(x==2) return true;
	if(!(x&1)) return false;
	i64 t=0,u=x-1;// x-1 = 2^t*u
	while(!(u&1)) u>>=1,t++;
	int test_time=6;// TEST
	while(test_time--){
		i64 a=myrand()%(x-2)+2;//a=[2..x-1]
		a=mod_exp(a,u,x);
		if(a==1) continue;
		for(int j=0;j<=t;j++){//(**1)
			if(j==t) return false;
			if(a==x-1) break;// (x-1)^2 = 1 (mod x)
			a=mod_mul(a,a,x);
			//if(a==1) return false;//(**2) can remove
		}
	}
	return true;
}
//---------------------------------------------------
//. --------  Pollard-RHO ------------------
// use Rabin_Miller,gcd
#define func(x,n) ((mod_mul(x,x,n)-1)%n)
i64 Pollard(i64 n){
	i64 i,x,y,p;
	if(Rabin_Miller(n)) return n;
	if(!(n&1)) return 2;
	int test_time=10;// TEST
	for(i=1;i<test_time;i++){
		x=i;
		y=func(x,n);
		p=gcd(y-x,n);
		while(p==1){
			x=func(x,n);
			y=func(func(y,n),n);
			p=gcd((y-x+n)%n,n)%n;
		}
		if(p==0||p==n) continue;
		return p;
	}
	return p;
}

i64 ans[64];
int ansn;
void factor(i64 n){// init ansn=0
	i64 x;
	x=Pollard(n);
	if(x==n){
		ans[ansn++]=x;
		return;
	}
	factor(x);
	factor(n/x);
}

int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	i64 n;
	int cas=50;
   int ss = clock(); 
	//while(scanf("%I64d",&n)==1){
	while(cas--){
		n=(__int64)rand()*(__int64)rand()*(__int64)rand();
		ansn=0;
		factor(n);
		//printf("%I64d = ",n);
		i64 check=1;
		for(int i=0;i<ansn;i++){
			//printf("%I64d",ans[i]);
			if(!Rabin_Miller(ans[i])){
				printf("%I64d\n",ans[i]);
				system("pasue");
			}
			check*=ans[i];
			//if(i!=ansn-1) printf(" * ");
			//else printf("\n");
		}
		if(n!=check) system("pause");
	}
   printf("%f\n", (double)(clock()-ss)/1000); 

	return 0;
}