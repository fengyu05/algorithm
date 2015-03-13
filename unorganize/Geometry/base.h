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
	//����ʵ��  
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
/* �жϵ�p�Ƿ����߶�l�� 
������(p���߶�l���ڵ�ֱ����)&& (��p�����߶�lΪ�Խ��ߵľ�����) */  
bool online(LineSeg l,Point p)  
{  
	return ( cross(l.e,p,l.s)==0  
	&& (p.x-l.s.x)*(p.x-l.e.x) <=0  
	&& (p.y-l.s.y)*(p.y-l.e.y) <=0  );
}

//�ж��߶�u��v�ཻ(�����ཻ�ڶ˵㴦)  
bool intersect(LineSeg u,LineSeg v){  
	return ( (max(u.s.x,u.e.x)>=min(v.s.x,v.e.x))&&		  //�ų�ʵ��  
             (max(v.s.x,v.e.x)>=min(u.s.x,u.e.x))&&  
             (max(u.s.y,u.e.y)>=min(v.s.y,v.e.y))&&  
             (max(v.s.y,v.e.y)>=min(u.s.y,u.e.y))&&  
             (cross(v.s,u.e,u.s)*cross(u.e,v.e,u.s)>=0)&& //����ʵ��  
             (cross(u.s,v.e,v.s)*cross(v.e,u.e,v.s)>=0));
}
 
// �ж��߶� u��v�ཻ��������˫���Ķ˵㣩     
bool intersect_A(LineSeg u,LineSeg v){  
	return intersect(u,v) &&  
           !online(u,v.s) && !online(u,v.e) &&  
           !online(v,u.e) && !online(v,u.s) ;
}
 
// �ж��߶� v����ֱ�����߶�u�ཻ 
//�������ж��߶�u�Ƿ�����߶�v   
bool intersect_l(LineSeg u,LineSeg v){  
	return  cross(u.s,v.e,v.s)*cross(v.e,u.e,v.s)>=0;
}




// analytic geometry

// ֱ�ߵĽ������� a*x+b*y+c=0  Ϊͳһ��ʾ,Լ�� a>= 0 
struct Line{  
	double a,b,c;
	Line(double d1=1, double d2=-1, double d3=0) {a=d1; b=d2; c=d3;}
};
// ���ص�p�Ե�oΪԲ����ʱ����ת alpha(��λ������)�����ڵ�λ��  
Point rotate(Point o,double alpha,Point p)  
{  
	Point tp;
	p.x -=o.x;
	p.y -=o.y;
	tp.x=p.x*cos(alpha) - p.y*sin(alpha)+o.x;
	tp.y=p.y*cos(alpha) + p.x*sin(alpha)+o.y;
	return tp;
}
 
/* ���ض�����o��,��ʼ��Ϊos,��ֹ��Ϊoe�ļн�(��λ������)  
�Ƕ�С��pi,������ֵ  
�Ƕȴ���pi,���ظ�ֵ  
�����������߶�֮��ļн� */  
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
	if (dsx*dey-dsy*dex>0) return fi;// ˵��ʸ�� os ��ʸ�� oe��˳ʱ�뷽��  
		return -fi;
}

// ������֪��������,����������ֱ�߽������̣� a*x+b*y+c = 0  (a >= 0)   
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
// ����ֱ�߽������̷���ֱ�ߵ�б��k,ˮƽ�߷��� 0,��ֱ�߷��� INF  
double slope(Line l)  
{  
	if(abs(l.a) < 1e-20)return 0;
	if(abs(l.b) < 1e-20)return INF;
	return -(l.a/l.b);
}
 
// ����ֱ�ߵ���б��alpha ( 0 - pi) 
// ע�⣺atan()���ص��� -PI/2 ~ PI/2  
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
 
// ���p����ֱ��l�ĶԳƵ�   
Point symmetry(Line l,Point p)  
{  
   Point tp;
   tp.x=((l.b*l.b-l.a*l.a)*p.x-2*l.a*l.b*p.y-2*l.a*l.c)/(l.a*l.a+l.b*l.b);
   tp.y=((l.a*l.a-l.b*l.b)*p.y-2*l.a*l.b*p.x-2*l.b*l.c)/(l.a*l.a+l.b*l.b);
   return tp;
}
 
// �������ֱ�� l1(a1*x+b1*y+c1 = 0), l2(a2*x+b2*y+c2 = 0)�ཻ,����true,�ҷ��ؽ���p   
bool lineintersect(Line l1,Line l2,Point &p) // �� L1,L2  
{  
	double d=l1.a*l2.b-l2.a*l1.b;
	if(abs(d)<EP) // ���ཻ  
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

