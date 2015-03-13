// C(n,x) in 64bit using factoring
#define N 10000000
#define M 700000
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
typedef unsigned __int64 i64;
typedef	map<int,int> mii;
typedef map<int,int>::iterator mit;
bool cmp(pair<int,int>& x,pair<int,int>& y){
	return x.first<y.first;
}
void factor(i64 x,mii& r,int mode){
	if(x==1) return;
	int i;
	for(i=0;;i++){
		if(x==1) break;
		if((i64)prime[i]*prime[i]>x) break;
		int cnt=0;
		while(x%prime[i]==0){
			cnt++;
			x/=prime[i];
		}
		if(cnt>0){
			mit it=r.find(prime[i]);
			if(it==r.end())
				r.insert(make_pair(prime[i],cnt*mode));
			else
				it->second+=(cnt*mode);
		}
	}
	if(x!=1){
		mit it=r.find(x);
		if(it==r.end())
			r.insert(make_pair(x,1*mode));
		else
			it->second+=(1*mode);
	}
}
i64 C(i64 n,i64 x){
	if(n-x<x) x=n-x;
	mii re;
	for(i64 i=1;i<=x;i++){
		factor(n-i+1,re,1);
		factor(i,re,-1);
	}
	i64 r=1;
	for(mit it=re.begin();it!=re.end();++it){
		while(it->second>0){
			it->second--;
			r*=it->first;
		}
	}
	return r;
}