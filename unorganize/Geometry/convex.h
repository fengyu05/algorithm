// 卷包裹法求点集凸壳    
#include <iostream>
#include <cmath>
using namespace std;

#define N 256  
struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y){}
};
Point operator-(Point &a,Point &b){ return Point(a.x-b.x,a.y-b.y);}
inline double sqr(double x){ return x*x; }
double dist(Point p1,Point p2=0){				// |p2-p1|
	return sqrt(sqr(p1.x-p2.x)+sqr(p1.y-p2.y));
}
double distsqr(Point& p1,Point& p2){
	return sqr(p1.x-p2.x)+sqr(p1.y-p2.y);
}
double cosine(Point& a,Point& b){
	return (a.x*b.x+a.y*b.y)/(dist(a)*dist(b));
} 
void ConvexClosure(Point ps[],Point ch[],int n,int &len)  
{  
	int top=0,first;
	Point p0,p1,p2;

	bool use[N]={0};
	int dex=0;
	// 选取y最小点,如果多于一个,则选取最左点  
	for(int i=1;i<n;i++)  
		if(ps[i].y<ps[dex].y || ps[i].y == ps[dex].y&&ps[i].x<ps[dex].x)  
		{  dex=i;}

	first=dex;
	use[dex]=true;
	ch[top++]=ps[dex];
	p0=p1=ch[0];
	p0.x-=100;
	dex=-1;

	double curmax,curcos,curdis;
	while(dex!=first){  
		curmax=-2;
		curdis=0;
		// 选取与最后一条确定边夹角最小的点,即余弦值最大者  
		for(int i=0;i<n;i++)  
		{  
			if(use[i]) continue;
			p2=ps[i];
			curcos=cosine(p1-p0,p2-p1); // 根据cos值求夹角余弦,范围在 (-1 ~ 1)  
			if(curcos>curmax || fabs(curcos-curmax)<1e-6 && distsqr(p2,p1)>curdis)  
			{  
				curmax=curcos;
				dex=i;
				curdis=distsqr(p2,p1);
			} 
		}
		use[first]=false;   //清空第first 个顶点标志,使最后能形成封闭的hull  
		use[dex]=true;
		ch[top++]=ps[dex];
		p0=ch[top-2];
		p1=ch[top-1];
	}
	len=top-1;
}
int main()
{
	Point p[N],p2[N];
	int x,y;
	int n=0,len;
	while(scanf("%d%d",&x,&y)==2){
		p[n].x=x,p[n].y=y;
		n++;
	}
	ConvexClosure(p,p2,n,len);
}