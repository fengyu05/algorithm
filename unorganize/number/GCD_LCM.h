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
#define func(x,n) ((mod_mul(x,x,n)+1)%n)
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

i64 ans[20],cnt[20];
int ansn;
void factor(i64 n){// init ansn=0
	i64 x;
	x=Pollard(n);
	if(x==n){
		if(x==ans[ansn-1]){
			cnt[ansn-1]++;
		}else{
			ans[ansn++]=x;
			cnt[ansn-1]=1;
		}
		return;
	}
	factor(x);
	factor(n/x);
}
char X[20];
i64 a,b,re;
void go(int i){
	if(i==ansn){
		i64 t[2];t[1]=t[0]=1;
		for(int j=0;j<ansn;j++){
			int ii=cnt[j];
			while(ii--) t[X[j]]*=ans[j];			
		}
		i64 tmp=t[0]+t[1];
		if(re==-1||tmp<re){
			re=tmp;
			a=t[0];
			b=t[1];
		}
	}else{
		X[i]=1;
		go(i+1);
		X[i]=0;
		go(i+1);
	}
}
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	i64 x,y;
	while(scanf("%I64d%I64d",&x,&y)==2){
		if(x==1&&Rabin_Miller(y)){
			printf("%I64d %I64d\n",x,y);
		}else{
			i64 D=y/x;
			ansn=0;
			factor(D);
			re=-1;
			memset(X,0,sizeof(X));
			go(0);
			if(a>b) swap(a,b);
			printf("%I64d %I64d\n",a*x,b*x);
		}
	}
	return 0;
}