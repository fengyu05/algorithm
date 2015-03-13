// Number-Theoretic Algorithms
//1.---------- bsae ----------------------
#define mod(a,b) ((a%b+b)%b)
long gcd(long x,long y){
	while(y){
		long tmp=x;
		x=y,y=tmp%y;
	}
	return x;
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
// a*b mod n
long mod_mul(long a, long b, long n)
{
	if(a<=0) return 0;
	return ( ((a&1)*b)%n + (mod_mul(a>>1,b,n)<<1)%n )%n;
}
//a^b mod n
long mod_exp(long a, long b, long n)
{
	long t=1,y=a;
	while(b!=0){
		if (b&1) t=mod_mul(t,y,n);
		y=mod_mul(y,y,n);
		b>>=1;
	}
	return t;
}
// ax=b(mod p)
long mod_equation(long a, long b, long p)//,long& ofs)
{
	long d,x,y;
	d=extended_euclid(a,p,x,y) ;
	if (b%d!=0) return -1;
	x*=b/d;
	x=mod(x,(p/d));
	//ofs=(p/d);
	return x;
}
// a=b[i](mod p[i]) p[] pairwise relatively prime
long mod_equations(long b[] , long p[] , long n)
{
	long a=0,m=1,x,y;
	int i;
	for( i=0;i<n; i++) m*=p[i];
	for( i=0;i<n; i++){
		long t=m/p[i];
		extended_euclid (p[i],t,x,y);
		a=(a+t*y*b[i])%m;
	}
	return mod(a,m);	// ofs=m
}
//eg: long b[3]={1,4 ,6},q[3]={3 ,5 ,7};
// modular_equations(b,q,3));

//2.---------- prime seive ----------------------
// 线性筛素数方法
bool notp[N];
long prime[M];
long pn;
void getprime()
{
	pn=0;//notp[0]=notp[1]=1;
	memset(notp,0,sizeof(notp));
	for(int i=2;i<N;i++)
	{
		if(!notp[i])prime[pn++]=i;
		for(long j=0;j<pn && prime[j]*i<N;j++)
		{
			notp[prime[j]*i]=1;
			if(i%prime[j]==0)break;
		}
	}
}
//-----------------------------------------
const int M = 172;
const int N = 1024;
int prime[M],pn;
void getprime()
{
	bool sieve[N]={0};
	prime[(pn=0)++] = 2;
	for (int i=3 ; i<N ; i+=2) if(sieve[i]==0)
    {
      prime[pn++] = i;
      for (int j=i*i ; j<N ; j+=i+i)
        sieve[j] = 1;
    }
}
//-------------------------------------------
//3.------- Euler's phi function --------------------
// phi(k)=k*II(1-1/p) where p|n && p is prime
/*
for prime p & p|n
if( (n/p) % p == 0 ) phi(n)=phi(n/p)*p;
else phi(n)=phi(n/p)*(p-1);
*/
bool notp[N];
long prime[M];
long pn;
int phi[N];
void getphi()
{
	pn=0;
	memset(notp,0,sizeof(notp));
	for(int i=2;i<N;i++)
	{
  		if(!notp[i])
		{
			prime[pn++]=i;
			phi[i]=i-1;
		}
		for(int j=0;j<pn && i*prime[j]<N;j++)
		{
			int k=i*prime[j];
			notp[k]=1;
			if(i%prime[j]==0)
			{// phi(p^n)=p^n*(p-1)
				phi[k]=phi[i]*prime[j];
				break;
			}
			else
			{//积性函数 phi[k]=phi[i]*phi[prime[j]]
				phi[k]=phi[i]*(prime[j]-1);
			}
		}
	}
}
int phi2(int n){
	if(n==1) return 0;
	int re=n;
	if(n%2==0) re/=2;
	while(n%2==0) n/=2;
	for(int i=3;n!=1;i=i+2){
		if(n%i==0) re-=re/i;
		while(n%i==0) n/=i;
	}
	return re;
}
//4------- 素数判定 ------------------------
bool PrimeTest(long x){
	long i=0;
	while(prime[i]*prime[x]<=x){
		if(x%prime[i++]==0) return false;
	}
	return true;
}
//--------- Rabin Miller Test ---------------------
// use mod_exp,mod_mul
// Euler's theorem. a^@(n)=1 (mod n) for any n>1
// when n is prime @(n)=n-1 , so we get
// Fermat's theorem p is prime => a^(p-1) = 1 (mod p) (**1)
// we also have
// p>2 is prime => x^2 = 1 (mod p) only when x=+/-1 (**2) 
long myrand(){	return rand(); }
bool Rabin_Miller(long x){	
	if(x<2) return false;
	if(x==2) return true;
	if(!(x&1)) return false;
	long t=0,u=x-1;// x-1 = 2^t*u
	while(!(u&1)) u>>=1,t++;
	int test_time=6;// TEST
	while(test_time--){
		long a=myrand()%(x-2)+2;//a=[2..x-1]
		a=mod_exp(a,u,x);
		if(a==1) continue;
		for(long j=0;j<t;j++){//(**1)
			if(a==x-1) break;// (x-1)^2 = 1 (mod x)
			a=mod_mul(a,a,x);
			//if(a==1) return false;//(**2) can remove
		}
		if(j<t) continue;
		return false;
	}
	return true;
}
//---------------------------------------------------
//5. 分解质因数
// use prime-list
int factor[SIZE];
int cnt;
void decompose(int n){// n>1
	cnt=0;
	for(int i=0;i<p_cnt&&n!=1;i++){
		while(n%prime[i]==0){
			factor[cnt++]=prime[i];
			n/=prime[i];
		}
	}
	if(n>1) factor[cnt++]=n;
}
// simple vision
int factor[MaxN], fcnt[MaxN],top;
void de(int a){
    int i;
    for (i=2, top=0; i<=a/i; i++){
        if (a%i) continue;
        factor[top] = i;
        fcnt[top] = 0;
        while (a%i==0){
            a /= i;
            fcnt[top]++;
        }
        top++;
    }
    if (a!=1){
        factor[top] = a;
        fcnt[top] = 1;
        top++;
    }
}
// --------  Pollard-RHO ------------------
// use Rabin_Miller,gcd
#define func(x,n) ((mod_mul(x,x,n)+1)%n)
long Pollard(long n){
	long i,x,y,p;
	if(Rabin_Miller(n)) return n;
	if(!(n&1)) return 2;
	int test_time=20;// TEST
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
