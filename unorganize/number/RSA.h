/* 2447-RSA
 * fengyu05
 RSA:
  选定两素数 P=37 Q=23
             N=P*Q=851
			 T=(P-1)*(Q-1)=792
  <E,N>公钥	 E=5
  <D,N>密钥	 D=E^-1(mod T)=317 D为E的逆模
     密文    M=7
    加密式   C=(M^E) mod N
	解密式   M=(C^D) mod N

  问题:已知C,E,N 求 M(解密)
*/
#include<iostream>
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
// ax+by=d
long extended_euclid(long a, long b, long &x, long &y)
{
	long d,temp;
	if(b==0){
		x=1,y=0;
		return a;
	}else{
		d=extended_euclid(b,a%b,x,y) ;
		temp=x;
		x=y;
		y=temp-a/b*y;
		return d;
	}
}
long mod_equation(long a, long b, long p)
{
	long d,x,y;
	d=extended_euclid(a,p,x,y) ;
	if (b%d!=0) return -1;
	x*=b/d;
	x=mod(x,(p/d));
	return x;
}
 
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

#define func(x,n) ((mod_mul(x,x,n)-1)%n)
i64 Pollard(i64 n){
	i64 i,x,y,p;
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

int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	i64 C,E,N,T,D,M;
	while(scanf("%I64d %I64d %I64d",&C,&E,&N)==3){
		if(Rabin_Miller(N)) throw 'e';
		i64 p=Pollard(N);
		T=(p-1)*(N/p-1);
		D=mod_equation(E,1,T);
		if(D<=0) throw 'e';
		M=mod_exp(C,D,N);
		if(C!=mod_exp(M,E,N)) throw 'e';
		printf("%I64d\n",M);
	}
	return 0;
}