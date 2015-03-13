/* ·ä×åµÄÂÃÐÐ*/
#include <iostream>
#include <cmath>
using namespace std;
#define INF 1e300 
#define EP  1e-20
const double sqr3=sqrt(3.0);
double dis(double x1,double y1,double x2,double y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
void locate(double ll,double x,double y,double &x0,double &y0){
	double xx,yy,mm,m0=INF;
	int k1,k2;
	k1=floor(x/1.5/ll);
	for(int i=0;i<=1;i++){
		k1=k1+i;
		k2=floor(y/ll/sqr3-k1/2);
		for(int j=0;j<=1;j++){
			k2=k2+j;
			xx=1.5*k1*ll;
			yy=ll*(sqr3*k1/2+sqr3*k2);
			mm=dis(x,y,xx,yy);
			if(mm<m0)
				m0=mm,x0=xx,y0=yy;
		}
	}
}
double distance(double x1,double y1,double x2,double y2,double ll){
	double dx,r1,r2;
	dx=fabs(x1-x2)/1.5/ll;
	r1=y1+dx*sqr3*ll/2;
	r2=y1-dx*sqr3*ll/2;
	if(r1>=y2&&y2>=r2)
		return sqr3*ll*dx;
	if(r1<y2)
		return sqr3*ll*dx+y2-r1;
	else return sqr3*ll*dx+r2-y2;
}


int main()
{	
	double ll,x1,y1,x2,y2,ax,ay,bx,by;
	while(scanf("%lf%lf%lf%lf%lf",&ll,&x1,&y1,&x2,&y2),ll>0){
		locate(ll,x1,y1,ax,ay);
		locate(ll,x2,y2,bx,by);
		double re;
		if(fabs(ax-bx)>EP||fabs(ay-by)>EP){
			re=dis(x1,y1,ax,ay);
			re+=dis(x2,y2,bx,by);
			re+=distance(ax,ay,bx,by,ll);
		}else{
			re=dis(x1,y1,x2,y2);
		}
		printf("%.3lf\n",re);
	}
	return 0;
}