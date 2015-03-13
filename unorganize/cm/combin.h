// Combinatorics

// p(n,k)
double P(int n,int k){
	double r=1;
	while(k--)
		r*=n--;
	return r;
}
// C(n,k)
double C(double n,int k)
{
	if(k<0) return 0;
	if(k==0) return 1;
	double r=1;
	if(k>n-k){ k=n-k;}
	for(double i=n;i>=n-k+1;i-=1)
		r*=i/(i-(n-k));
	return r;
}
// dp
for(i=1;i<=N;i++){
	c[i][0]=c[i][i]=1;
	for(j=1;j<i;j++)
		c[i][j]=c[i-1][j]+c[i-1][j-1];
}
//循环r排列  P(n,r)/r
//无限重数r排列 k^r
//k种元素,多重r排列  n!/(n1!*n2!*...nk!)
//k种元素,多重r组合 C(r+k-1,r)
// k*C(n,k)=n*C(n-1,k-1)
// E(k=0..n)C(n,k)^2=C(2n,n)
// Stirling
const double PI=acos(-1.0);
const double E=2.7182818284590452354;
double Stirling(double n){
	return sqrt(2*PI*n)*pow(n/E,n);
}

// gen permutation
#define N 100

class genper //生存排列
{public: // S.Even方法:交换相邻
	int a[N],n;
	bool flag[N];
	genper(int n):n(n){
		for(int i=1;i<=n;i++) a[i]=i,flag[i]=0;
	}
	bool getnext(){
		int i,dex=0,max=0;
		for(i=1;i<=n;i++){
			if(a[i]==1) continue;
			if(i==1&&flag[i]==0) continue;
			if(i==n&&flag[n]==1) continue;
			if(!flag[i]&&a[i-1]<a[i]||flag[i]&&a[i]>a[i+1])
				if(max<a[i]) max=a[i],dex=i;
		}
		if(dex==0) return false;
		int tmp=dex+(flag[dex]?1:-1);
		swap(a[dex],a[tmp]);
		swap(flag[dex],flag[tmp]);
		for(i=1;i<=n;i++) if(a[i]>a[tmp])
			flag[i]=!flag[i];
		return true;
	}
};

//逆序列
int a[N],inv[N];
int invper(int n)
{//生成逆序列,返回逆序数
	int i,j,re=0;
	bool flag[N]={0};
	for(i=1;i<=n;i++) inv[i]=0;
	for(i=1;i<=n;i++){
		for(j=1;j<a[i];j++){
			if(!flag[j]){
				inv[j]++;
				re++;
			}
		}
		flag[a[i]]=1;
	}
	return re;
}
void per(int n) //O(n^2)
{//由逆序列生成原列
	bool flag[N]={0};
	a[inv[1]+1]=1;
	flag[inv[1]+1]=1;
	for(int i=2;i<=n;i++){
		int j=0,k=0;
		while(k<=inv[i]){
			j++;
			if(!flag[j]) k++;
		}
		a[j]=i;
		flag[j]=1;
	}
}
void perm(int n) //O(n)
{//由逆序列生成原列
	PointTree<N> pt;int i;
	for(i=1;i<=n;i++) pt.add(i);
	for(i=1;i<=n;i++){
		int tmp=pt[inv[i]];
		a[tmp]=i;
		pt.del(tmp);
	}
}

// 求逆序数
int a[N],bak[N],n,ans;
void msort(int b, int e)
{
	if (e-b<=0) return;
	int mid=(b+e)/2,p1=b,p2=mid+1,i=b;
	msort(b,mid); msort(mid+1,e);
	while( p1<=mid || p2<=e )
	if ( p2>e || ( p1<=mid && a[p1]<=a[p2 ]) )
		bak[i++]=a[p1++];
	else{
		bak[i++]=a[p2++];
		ans+=mid-p1+1;
	}
	for(i=b;i<=e;i++) a[i]=bak[i];
}

// gen combination

void tobit(int n){
	if(n/2>0) tobit(n/2);
	printf("%d",n%2);
}
void printbit(int n,int l){
	int m=1<<l;
	while(m>>=1){		
		printf("%d",n/m);
		n%=m;		
	}
}
// Gray Code
int genGray(int n){ // beginat 00...0 endat 10...0  
	int m=n,t=0;
	while(m) t+=m%2,m/=2;
	if(t%2==0) n=n^1;
	else{
		m=n;
		while(m>0){
			if(m%2==1) break;
			m/=2;
		}
		n=n^(n/m*2);
	}
	return n;
}

//gen r-combin
// 生存下个r组合 begin:123..r end: (n-r+1)(n-2+2)..n
bool nextcom(int n,int r,int a[]){
	int i;
	for(i=r;i>=1;i--){
		if(a[i]+1<=n&&(i==r||a[i+1]!=a[i]+1))
			break;
	}
	if(i==0) return false;
	a[i]++;
	for(i++;i<=n;i++){
		a[i]=a[i-1]+1;
	} return true;
}
// index of r-com {a1 a2 a3... ar}
// = C(n,r)-C(n-a1,r-1)-..C(n-ar,1)

// C(n,r)生产排列 return [0..C(n,r)-1]
/*Combinations are ordered in such a manner that taking the k-th stone from a 
list always leads to a combination with smaller index than a combination where
 the k-th stone is not taken (the first k-1 stones having the same status)
*/
int gen_r_com(int n,int r,bool selected[]){
	int id=0;
	int left=r;
	for (int i=0 ; i<n ; i++)
        if (selected[i])
          --left;
        else
          if (left > 0)
            id += (int)C(n-i-1, left-1);
	return id;
}
