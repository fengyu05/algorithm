typedef unsigned long long i64;
typedef unsigned __int64 i64;
i64 gcd(i64 x,i64 y){
	while(y){
		i64 tmp=x;
		x=y,y=tmp%y;
	}
	return x;
}
// prime_seive [0..n]
#define N 1000000
bool flag[N];
void sieve(){
	memset(flag,true,sizeof(flag));
	flag[1]=0;
	for(int i=2;i<N;i++) 
		if (flag[i])
			for(int j=i+i;j<N;j+=i )
				flag[j]=0;		
}

// get prime list
int prime[M],p_cnt;
void prime_list()
{
	bool flag[N]={0};
	int p_cnt=1, i, j;
	prime[0]=2;
	for( i=3;i<N; i+=2) 
		if (!flag[i]){
			prime[p_cnt++]=i ;
			for( j=i ; j<N; j+=i ) flag[j]=1;
		}
}

// ax+by=d
i64 extended_euclid (i64 a, i64 b, i64 &x, i64 &y)
{
	i64 d,temp;
	if (b==0){
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
i64 mod_mul(i64 a, i64 b,i64 n)
{
	if(a<=0) return 0;
	return ( ((a&1)*b)%n + (mod_mul(a>>1,b,n)<<1)%n )%n;
	// return ( (a&1)*b + mod_mul(a>>1,b,n)<<1 )%n; if not upflow
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
	return t ;
}
// ax=b(mod p) 
i64 solve_equation(i64 a, i64 b, i64 p)
{
	i64 d,x,y;
	d=extended_euclid (a,p,x,y) ;
	if (b%d!=0) return -1;
	x*=b/d;
	x=(x%(p/d)+p/d)%(p/d) ;
	return x;
}

// a=b[i](mod p[i])
i64 modular_equations(i64 b[] , i64 p[] , i64 n)
{
	i64 a=0,i ,m=1,x,y, t ;
	for( i=0;i<n; i++) m*=p[ i ];
	for( i=0;i<n; i++){
		t=m/p[ i ];
		extended_euclid (p[ i ] ,t ,x,y) ;
		a=(a+t*y*b[ i ])%m;
	}
	return (a+m)%m;
}
//eg: i64 b[3]={1,4 ,6},q[3]={3 ,5 ,7};
// modular_equations(b,q,3)) ;

// prime test
bool isPrime(int n){
	int i=0;
	int max=(int)sqrt(n)
	while(prime[i]<=max){
		if(n%prime[i]==0) return false;
	}
	return true;
}
// random
i64 myrand(){
	i64 a=rand();
	return a*=rand();
}
#define TestTime 20
bool Rabin_Miller(i64 n){	
	if(n<2) return false;
	if(n==2) return true;
	if(!(n&1)) return false;
	i64 k=0,i,j,m,a;
	m=n-1;
	while(!(m&1)) m>>=1,k++;
	for(i=0;i<TestTime;i++){
		a=myrand()%(n-2)+2;
		a=mod_exp(a,m,n);
		if(a==1) continue;
		for(j=0;j<k;j++){
			if(a==n-1) break;
			a=mod_mul(a,a,n);
		}
		if(j<k) continue;
		return false;
	}
	return true;
}
#define func(x,n) ((mod_mul(x,x,n)+1)%n)
i64 Pollard(i64 n){
	i64 i,x,y,p;
	if(Rabin_Miller(n)) return n;
	if(!(n&1)) return 2;
	for(i=1;i<TestTime;i++){
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
i64 ans[100];
int ansn;
void factor(i64 n){// init ansn=0
	i64 x;
	x=Pollard(n);
	if(x==n){
		//if(ans[ansn-1]!=x)
		//去处相同的因子
			ans[ansn++]=x;
		return;
	}
	factor(x);
	factor(n/x);
}

