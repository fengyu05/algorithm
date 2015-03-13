#include <iostream>
#include <vector>
using namespace std;
/*
--------------- autoBint -------------------
------------- 自动空间扩充大整数类 ---------
test:
(1)3472 Holey Square Tiling : +,*,print2
(2)2389 Bull Math           : *,Num(char s[])
*/
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
	Num(char s[],int len):l((len+8)/9-1),d(l+1,0){
		for(int i=0;i<=l;i++){
			int tmp=0;
			for(int j=1;j<MARK&&len>0;j*=10,len--){
				tmp+=(s[len-1]-'0')*j;
			}
			d[i]=tmp;
		}
		while(l>0&&d[l]==0) l--;
	}
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
