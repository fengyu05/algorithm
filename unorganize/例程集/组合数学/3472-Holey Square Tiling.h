/* 3472 Holey Square Tiling
 * fengyu05
 * 5168K	2671MS	C++	2045B
 * 加法原理&乘法原理,autoBint
 */
#include <iostream>
#include <vector>
using namespace std;

#define i64 __int64
#define MARK 1000000000
#define max(a,b) (a>b?a:b)
class Num{
public:
	int l;
	vector<int> d;
	Num(int size,int init):l(size-1),d(size,init){}
	Num(int x=0):d(1,0){		
		d[l=0]=x;
	}
	bool is0(){return l==0&&d[0]==0;}
	void print(){
		printf("%d",d[l]);
		for(int i=l-1;i>=0;i--)
			printf("%09d",d[i]);
		printf("\n");
	}
	void put(int x,bool high=false){
		int a=x%1000,b=(x/1000)%1000,c=x/1000000;
		if(high){
			if(c>0) printf("%d,%03d,%03d",c,b,a);
			else if(b>0) printf("%d,%03d",b,a);
			else if(a>0) printf("%d",a);
		}else printf("%03d,%03d,%03d",c,b,a);
	}
	void print2(){
		put(d[l],true);if(l>0) printf(",");
		for(int i=l-1;i>=0;i--){
			put(d[i]);
			if(i!=0) printf(",");
		}
		printf("\n");
	}
};
Num operator+(const Num &a,const Num &b){
	Num c(max(a.l,b.l)+2,0);
	for(int i=0;i<c.l;i++){
		if(i<=a.l) c.d[i]+=a.d[i];
		if(i<=b.l) c.d[i]+=b.d[i];
		c.d[i+1]=c.d[i]/MARK,c.d[i]%=MARK;
	}
	if(c.l>0&&c.d[c.l]==0) c.l--;
	return c;
}
Num operator*(Num &a,Num &b){
	if(a.is0()||b.is0()) return Num(0);
	Num c((a.l+b.l+2),0);
	for(int i=0;i<=b.l;i++){
		int l=i-1,w=0;
		for(int j=0;j<=a.l;j++){
			l++;
			i64 tmp=(i64)b.d[i]*a.d[j]+c.d[l];
			c.d[l]=tmp%MARK;
			c.d[l+1]+=tmp/MARK;
		}
	}
	while(c.l>0&&c.d[c.l]==0) c.l--;
	return c;
}
int cmp(Num &a,Num &b){
	if(a.l<b.l) return -1;
	if(a.l>b.l) return 1;
	for(int i=a.l;i>=0;i--){
		if(a.d[i]<b.d[i]) return -1;
		if(a.d[i]>b.d[i]) return 1;
	}
	return 0;
}
#define M 10010
Num f[M];
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int i;
	f[0]=f[1]=1;
	for(i=2;i<M;i++)
		f[i]=f[i-2]+f[i-1];
	while(scanf("%d",&i)==1){
		Num L_i1_i=(f[i]*f[i-2])+(f[i-1]*f[i-1]);//L[i+1][i]
		Num L_i1_i1=(f[i]*f[i-1])+(f[i]*f[i-1]);//L[i+1][i+1]
		Num L_i_i=(f[i-1]*f[i-2])+(f[i-1]*f[i-2]);//L[i][i];
		Num B=(L_i1_i*L_i1_i)+(L_i1_i1*L_i_i);
		Num re=(B+1)*Num(2);
		re.print2();
	}
	return 0;
}