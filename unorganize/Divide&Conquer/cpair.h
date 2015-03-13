/* 最近点对 */
#include <iostream>
#include <cmath>
#include <algorithm>

#define N 512

inline double sqr(double x){ return x*x; }

struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y){}
} pt[N];
double dist(Point& p1,Point& p2){
	return sqrt(sqr(p1.x-p2.x)+sqr(p1.y-p2.y));
}
bool cmp(Point& a,Point& b){ return a.x<b.x; }
bool cmpY(int a,int b){ return pt[a].y<pt[b].y; }

double Cpair2(int l,int r,int& pa,int& pb){
	if(r-l==1){
		pa=l;
		pb=r;
		return dist(pt[l],pt[r]);
	}else if(r-l==2){
		double d1=dist(pt[l],pt[l+1]);
		double d2=dist(pt[l+1],pt[r]);
		double d3=dist(pt[l],pt[r]);
		
		if(d1<d2 && d1<d3){
			pa=l , pb=l+1;
			return d1;
		}else if(d2<d3){
			pa=l+1 , pb=r;
			return d2;
		}else{
			pa=l , pb=r;
			return d3;
		}
	}else{
		int m=(l+r)/2;
		int pa2,pb2;
		double d,d2;
		d=Cpair2(l,m,pa,pb);
		d2=Cpair2(m+1,r,pa2,pb2);
		if(d2<d) pa=pa2,pb=pb2,d=d2;
		int s1[N],s2[N],cnt_s1=0,cnt_s2=0;
		double mid=(pt[m].x+pt[m+1].x)/2;
		while(mid-pt[m-cnt_s1].x<d && cnt_s1<m-l+1){
			s1[cnt_s1]=m-cnt_s1;
			cnt_s1++;
		}
		while(pt[m+1+cnt_s2].x-mid<d && cnt_s2<r-m){
			s2[cnt_s2]=m+1+cnt_s2;
			cnt_s2++;
		}
		std::sort(s1,s1+cnt_s1,cmpY);
		std::sort(s2,s2+cnt_s2,cmpY);
		double dp=d;
		for(int i=0;i<cnt_s1;i++){
			for(int j=0;j<cnt_s2;j++){
				if(pt[s1[i]].y - pt[s2[j]].y>d)
					continue;
				if(pt[s2[j]].y - pt[s1[i]].y>d)
					break;
				double tmp=dist(pt[s1[i]],pt[s2[j]]);
				if(tmp<dp){
					dp=tmp;
					pa=s1[i],pb=s2[j];
				}
			}
		}
		if(dp<d) d=dp;
		return dp;
	}
}
double Cpair2(int n,Point& pa,Point& pb){
	std::sort(pt,pt+n,cmp);
	int a,b;
	double re=Cpair2(0,n-1,a,b);
	pa=pt[a],pb=pt[b];
	return re;
}

// for test
const int M=65535;
int getrand(){
	return (rand()*rand())%M;
}
int main()
{
#ifndef ONLINE_JUDGE
  	freopen("t.in", "r", stdin);
#endif
	int n=0;
	while(n<500){
		pt[n++]=Point(getrand(),getrand());
	}
	Point a,b;
	double re=Cpair2(n,a,b);
	double re2=re;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			double tmp=dist(pt[i],pt[j]);
			if(tmp<re2) re2=re;
		}
	}
	// check is the result is right
	printf("%.2lf  %.2lf\n",re,re2); 
	return 0;
}
