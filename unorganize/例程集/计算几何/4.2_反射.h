/* 反射 */
#include <iostream>
#include <cmath>
using namespace std;
#define INF 1e300 
#define EP  1e-10
const double Pi = acos(-1.);
// basic function
inline double max(double a,double b){return a>b?a:b;}
inline double min(double a,double b){return a<b?a:b;}
inline double sqr(double x){ return x*x; }
int dcmp(double x){if(x<-EP) return -1; else return(x>EP);}

struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y){}
};
//直线的倾角
double alpha(Point& o,Point& t){
	if(dcmp(o.x-t.x)==0){
		if(o.y<t.y) return Pi/2;
		else return Pi/2*3;
	}else{
		double q=atan((o.y-t.y)/(o.x-t.x));
		if(o.x-t.x>0) q+=Pi;
		if(q<0) q+=2*Pi;
		return q;
	}
}
void test_alpha(){
	Point O;
	printf("%.2lf\n",alpha(O,Point(1,0)));
	printf("%.2lf\n",alpha(O,Point(1,1)));
	printf("%.2lf\n",alpha(O,Point(0,1)));
	printf("%.2lf\n",alpha(O,Point(-1,1)));
	printf("%.2lf\n",alpha(O,Point(-1,0)));
	printf("%.2lf\n",alpha(O,Point(-1,-1)));
	printf("%.2lf\n",alpha(O,Point(0,-1)));
	printf("%.2lf\n",alpha(O,Point(1,-1)));
}

#define N 64
int n;
Point o[N],p;//球心和光线射出点
double r[N];
double dx,dy;
int hit(double& tt,int lh){
	int re=0;
	tt=INF;
	for(int i=1;i<=n;i++){
		if(i==lh) continue;
		double d=abs(dy*o[i].x-dx*o[i].y+dx*p.y-dy*p.x)/sqrt(dy*dy+dx*dx);
		if(d<r[i]){
			double a=dx*dx+dy*dy;
			double b=2*((p.x-o[i].x)*dx+(p.y-o[i].y)*dy);
			double c=sqr(p.x-o[i].x)+sqr(p.y-o[i].y)-r[i]*r[i];
			double t=(-b-sqrt(b*b-4*a*c))/2/a;
			if(t>0&&t<tt) tt=t,re=i;
		}
	}
	return re;
}
int main()
{	
	freopen("t.in", "r", stdin);
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%lf%lf%lf",&o[i].x,&o[i].y,&r[i]);
	}
	double tt;
	scanf("%lf%lf%lf%lf",&p.x,&p.y,&dx,&dy);
	int h=0;//击中的球,上次击中的球
	i=1;
	while(i<=10){
		h=hit(tt,h);
		if(h==0){ printf("inf\n"); return 0;}
		printf("%d ",h);
		Point np(dx*tt+p.x,dy*tt+p.y);
		double q1=alpha(np,p);//(*)反射点沿光射入方向反向线的角
		double q2=alpha(np,o[h]);//(*)圆心到反射点的角
		double q=q2-(q1-q2);//(*)反射点沿光出射方向的角
		//(*) 入射角=反射角:q1-q2=q2-q
		dx=cos(q)*10,dy=sin(q)*10;
		p=np;
		i++;
	}
	h=hit(tt,h);
	if(h==0) printf("inf\n");
	else printf("...");
	return 0;
}