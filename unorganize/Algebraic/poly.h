#include<iostream>
#include<algorithm>
#include<functional>
#include<cmath>
#include<cassert>
#include<vector>
using namespace std;

//--------------------------------------------------------
// poly is vector
typedef vector<int> poly;
//typedef vector<double> poly;
/* x^2+2x+3 :[3,2,1] size= 3 */

// use to define the hight poly and low poly
#define FLAG(a,b) (a.size()>b.size())
#define HI (flag?a:b)
#define LOW (flag?b:a)

// ------------ base function --------------
void read(poly& x){
	int h;
	cin>>h;
	x.clear();
	x.resize(h+1);
	assert(x.size()==h+1);
	for(int i=h;i>=0;i--)
		cin>>x[i];
}
void print(const poly& x){
	if(x.size()==0){
		printf("0\n");
		return;
	}
	for(int i=x.size()-1;i>=0;i--){
		if(i>1)
			cout<<x[i]<<"x^"<<i;
		else if(i==1)
			cout<<x[i]<<"x";
		else cout<<x[i];
		if(i==0) printf("\n");
		else printf(" + ");
	}
}
template<typename Num>
int cal(const poly& x,Num val){
	Num re=x.back();
	for(int i=x.size()-1;i>0;i--){
		re=re*val+x[i-1];
	}
	return re;
}
bool is0(const poly& x){
	return x.size()==0;
}
// ------------ operator --------------------
poly operator+(const poly& a,const poly& b){
	bool flag=FLAG(a,b);
	poly c=HI;
	for(int i=0;i<LOW.size();i++){
		c[i]+=LOW[i];
	}
	while(c.back()==0) c.pop_back();
	return c;
}
poly operator-(const poly& a,const poly& b){
	poly c;
	c.resize(b.size());
	transform(b.begin(),b.end(),c.begin(), negate<int>());
	return a+c;
}
poly operator*(const poly& a,const poly& b){
	if(is0(a)||is0(b)) return poly(0);
	poly c(a.size()+b.size()-1,0);
	for(int i=b.size()-1;i>=0;i--){
		for(int j=a.size()-1;j>=0;j--){
			c[i+j]+=b[i]*a[j];
		}
	}
	return c;
}
// use at poly is vector<double>
void divide(const poly& a,const poly& b,poly& q,poly& r){
	assert(!is0(b)&&!is0(a));
	q.resize(a.size()-b.size()+1);
	r=a;
	while(!is0(r)&&r.size()>=b.size()){
		double tmp=r.back()/b.back();
		q[r.size()-b.size()]=tmp;
		poly c(r.size()-b.size()+1,0);
		c.back()=tmp;
		r=r-b*c;
		print(r);		
	};
}
long gcd(long x,long y){
	while(y){
		long tmp=x;
		x=y,y=tmp%y;
	}
	return x;
}
poly gcd(const poly& a,const poly& b){
	poly n=a,m=b;
	while(!is0(m)){
		//print(n),print(m);
		poly q,r=n;
		q.resize(n.size()-m.size()+1);
		while(!is0(r)&&r.size()>=m.size()){
			int mul= m.back()/gcd(r.back(),m.back());
			transform (r.begin(), r.end(),r.begin(),     // the whole poly 
					  bind2nd(multiplies<int>(),mul));	 // * mul
			
			int tmp=r.back()/m.back();
			q[r.size()-m.size()]=tmp;
			poly c(r.size()-m.size()+1,0);
			c.back()=tmp;
			r=r-m*c;
			//print(r);
		}        
		n=m,m=r;
	}
	if(n.size()>1){
		int k=n.back();
		for(int i=n.size()-2;i>=0;i--) k=gcd(k,n[i]);
		transform (n.begin(), n.end(),n.begin(),     // the whole poly 
					 bind2nd(divides<int>(),k));
	}
	return n;
}
//-----------------------------------------
void rnd(poly& x){
	int h=rand();
	x.resize(h+1);
	for(int i=h;i>=0;i--)
		x[i]=rand();	
}
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	poly x,y,q,r;
	read(x),read(y);
	print(x);
	print(y);
	/*
	divide(x,y,q,r);
	print(q);
	print(r);
	*/
	print(gcd(x,y));

	/*
	poly x(0),y(1,1);
	assert(is0(x*y));
	int cas=10;
	while(cas--){
		rnd(x),rnd(y);
		print(x);
		print(y);
		print(x*y);
		int a=rand();
		assert( cal(x,a)*cal(y,a) == cal(x*y,a) );
		printf("\n");
	}*/
	return 0;
}