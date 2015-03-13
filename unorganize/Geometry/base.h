#include <cmath>
// const value
#define INF 1e300 
#define EP  1e-10
const double Pi = acos(-1.);
// basic function
inline double max(double a,double b){return a>b?a:b;}
inline double min(double a,double b){return a<b?a:b;}
inline double sqr(double x){ return x*x; }
int dcmp(double x){if(x<-EP) return -1; else return(x>EP);}
// Point and it's operator
struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y){}
};
Point operator+(Point &a,Point &b){ return Point(a.x+b.x,a.y+b.y);}
Point operator-(Point &a,Point &b){ return Point(a.x-b.x,a.y-b.y);}
bool operator==(Point &a,Point &b){
	return dcmp(a.x-a.x)==0 && dcmp(a.y-a.y)==0;
}
double operator*(Point &a,Point &b){
	return (a.x)*(b.y)-(b.x)*(a.y);
}
double operator^(Point &a,Point &b){
	return (a.x)*(b.x)+(a.y)*(b.y);
}
double dist(Point p1,Point p2){				// |p2-p1|
	return sqrt(sqr(p1.x-p2.x)+sqr(p1.y-p2.y));
}
double distsqr(Point p1,Point p2){			// |p2-p1|^2
	return sqr(p1.x-p2.x)+sqr(p1.y-p2.y);
}
double det(double x1,double y1,double x2,double y2){
	return x1*y2-x2*y1;
}
//r>0 counterclockwise, r=0 collinear, r<0 clockwise;  
double cross(Point a,Point b,Point c){	//(b-a)*(c-a)
	//return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
	return det(b.x-a.x,b.y-a.y,c.x-a.x,c.y-a.y);
}
bool intersectSimple(LineSeg u,LineSeg v){  
	//跨立实验  
    return cross(u.s,v.s,v.e)*cross(u.e,v.s,v.e)<0&&
		cross(v.s,u.s,u.e)*cross(v.e,u.s,u.e)<0;
}
// angle a=p1-p0-p2, [0,pi]: r>0 a<pi/2, r=0 a=0, r<0 a>pi/2 .
double dot(Point p0,Point p1,Point p2){		//(p1-p0)(p2-p0)
	return (p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y);
}
// Line Segment
struct LineSeg{  
	Point s,e;
	LineSeg(Point a, Point b) { s=a; e=b;}
};
/* 判断点p是否在线段l上 
条件：(p在线段l所在的直线上)&& (点p在以线段l为对角线的矩形内) */  
bool online(LineSeg l,Point p)  
{  
	return ( cross(l.e,p,l.s)==0  
	&& (p.x-l.s.x)*(p.x-l.e.x) <=0  
	&& (p.y-l.s.y)*(p.y-l.e.y) <=0  );
}

//判断线段u和v相交(包括相交在端点处)  
bool intersect(LineSeg u,LineSeg v){  
	return ( (max(u.s.x,u.e.x)>=min(v.s.x,v.e.x))&&		  //排斥实验  
             (max(v.s.x,v.e.x)>=min(u.s.x,u.e.x))&&  
             (max(u.s.y,u.e.y)>=min(v.s.y,v.e.y))&&  
             (max(v.s.y,v.e.y)>=min(u.s.y,u.e.y))&&  
             (cross(v.s,u.e,u.s)*cross(u.e,v.e,u.s)>=0)&& //跨立实验  
             (cross(u.s,v.e,v.s)*cross(v.e,u.e,v.s)>=0));
}
 
// 判断线段 u和v相交（不包括双方的端点）     
bool intersect_A(LineSeg u,LineSeg v){  
	return intersect(u,v) &&  
           !online(u,v.s) && !online(u,v.e) &&  
           !online(v,u.e) && !online(v,u.s) ;
}
 
// 判断线段 v所在直线与线段u相交 
//方法：判断线段u是否跨立线段v   
bool intersect_l(LineSeg u,LineSeg v){  
	return  cross(u.s,v.e,v.s)*cross(v.e,u.e,v.s)>=0;
}




// analytic geometry

// 直线的解析方程 a*x+b*y+c=0  为统一表示,约定 a>= 0 
struct Line{  
	double a,b,c;
	Line(double d1=1, double d2=-1, double d3=0) {a=d1; b=d2; c=d3;}
};
// 返回点p以点o为圆心逆时针旋转 alpha(单位：弧度)后所在的位置  
Point rotate(Point o,double alpha,Point p)  
{  
	Point tp;
	p.x -=o.x;
	p.y -=o.y;
	tp.x=p.x*cos(alpha) - p.y*sin(alpha)+o.x;
	tp.y=p.y*cos(alpha) + p.x*sin(alpha)+o.y;
	return tp;
}
 
/* 返回顶角在o点,起始边为os,终止边为oe的夹角(单位：弧度)  
角度小于pi,返回正值  
角度大于pi,返回负值  
可以用于求线段之间的夹角 */  
double angle(Point o,Point s,Point e)  
{  
	double cosfi,fi,norm;
	double dsx = s.x - o.x;
	double dsy = s.y - o.y;
	double dex = e.x - o.x; 
	double dey = e.y - o.y;
 
	cosfi=dsx*dex+dsy*dey;
	norm=(dsx*dsx+dey*dey)*(dex*dex+dey*dey);
	cosfi /= sqrt( norm );
	if (cosfi >=  1.0 ) return 0;
	if (cosfi <= -1.0 ) return -Pi;
	fi=acos(cosfi);
	if (dsx*dey-dsy*dex>0) return fi;// 说明矢量 os 在矢量 oe的顺时针方向  
		return -fi;
}

// 根据已知两点坐标,求过这两点的直线解析方程： a*x+b*y+c = 0  (a >= 0)   
Line makeline(Point p1,Point p2)  
{  
    Line tl;
    int sign = 1;
    tl.a=p2.y-p1.y;
    if(tl.a<0)  
	{  
		sign = -1;
		tl.a=sign*tl.a;
	}
	tl.b=sign*(p1.x-p2.x);
	tl.c=sign*(p1.y*p2.x-p1.x*p2.y);
	return tl;
}
// 根据直线解析方程返回直线的斜率k,水平线返回 0,竖直线返回 INF  
double slope(Line l)  
{  
	if(abs(l.a) < 1e-20)return 0;
	if(abs(l.b) < 1e-20)return INF;
	return -(l.a/l.b);
}
 
// 返回直线的倾斜角alpha ( 0 - pi) 
// 注意：atan()返回的是 -PI/2 ~ PI/2  
double alpha(Line l)  
{  
	if(abs(l.a)< EP)return 0;
	if(abs(l.b)< EP)return PI/2;
	double k=slope(l);
	if(k>0)  
       return atan(k);
   else  
      return PI+atan(k);
}
 
// 求点p关于直线l的对称点   
Point symmetry(Line l,Point p)  
{  
   Point tp;
   tp.x=((l.b*l.b-l.a*l.a)*p.x-2*l.a*l.b*p.y-2*l.a*l.c)/(l.a*l.a+l.b*l.b);
   tp.y=((l.a*l.a-l.b*l.b)*p.y-2*l.a*l.b*p.x-2*l.b*l.c)/(l.a*l.a+l.b*l.b);
   return tp;
}
 
// 如果两条直线 l1(a1*x+b1*y+c1 = 0), l2(a2*x+b2*y+c2 = 0)相交,返回true,且返回交点p   
bool lineintersect(Line l1,Line l2,Point &p) // 是 L1,L2  
{  
	double d=l1.a*l2.b-l2.a*l1.b;
	if(abs(d)<EP) // 不相交  
	return false;
	p.x = (l2.c*l1.b-l1.c*l2.b)/d;
	p.y = (l2.a*l1.c-l1.a*l2.c)/d;
	return true;
}

// Function for Polygon
double area(Point a,Point b,Point c){
	return (b-a)*(c-a)/2;
}
double area(int vcnt,Point polygon[])//  r>0 counterclockwise
{  
	int i;
	double s;
	if (vcnt<3)  
	   return 0;
	s=polygon[0].y*(polygon[vcnt-1].x-polygon[1].x);
	for (i=1;i<vcnt;i++)  
	s+=polygon[i].y*(polygon[(i-1)].x-polygon[(i+1)%vcnt].x);
	return s/2;
}

