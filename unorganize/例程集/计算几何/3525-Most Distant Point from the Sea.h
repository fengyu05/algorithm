/* 3525	Most Distant Point from the Sea
 * 求凸包到边最长的距离
 * 解法:将边缩为点
 */
 
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
const int N=100;
int n;
struct Point{
	int x;
	int y;
};
Point data[N];
struct edge {
	int pre;
	int end;
};
edge e[N];
inline bool equal(double a,double b) {
	if(fabs(a-b)<1e-8)
		return true;
	else
		return false;
}
inline bool cal(double &x,double &y,edge a,edge b) {
	const double x1=data[a.pre].x,x2=data[a.end].x,
		y1=data[a.pre].y,y2=data[a.end].y,
		x3=data[b.pre].x,x4=data[b.end].x,
		y3=data[b.pre].y,y4=data[b.end].y;
		if(equal((y4-y3)*(x2-x1),(y2-y1)*(x4-x3)))
			return true;
		else{ 
			x=-(x2*x3*y1 - x2*x4*y1 - x1*x3*y2 + x1*x4*y2 - x1*x4*y3 + x2*x4*y3 +  x1*x3*y4 - x2*x3*y4)/(-x3*y1 + x4*y1 + x3*y2 - x4*y2 + x1*y3 - x2*y3 - x1*y4 + x2*y4);
			y=-(-x2*y1*y3 + x4*y1*y3 + x1*y2*y3 - x4*y2*y3 + x2*y1*y4 - x3*y1*y4 - x1*y2*y4 + x3*y2*y4)/(x3*y1 - x4*y1 - x3*y2 + x4*y2 - x1*y3 + x2*y3 +x1*y4 - x2*y4);
			return false;
		}
}
inline double calacross(double x1,double y1,double x2,double y2) {
	return x1*y2-x2*y1;
}
inline double dis(double x1,double y1,double x2,double y2) {
	return sqrt((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1));
}
inline double dis(edge a,edge b) {
	double temp;
	temp=calacross(data[b.pre].x-data[a.pre].x,data[b.pre].y-data[a.pre].y,data[a.end].x-data[a.pre].x,data[a.end].y-data[a.pre].y);
	temp/=dis(data[a.pre].x,data[a.pre].y,data[a.end].x,data[a.end].y);
     
	return temp;
}
double re; 
inline double ok(edge a,edge b,edge c) {
	double abx=0,aby=0,bcx=0,bcy=0,acx=0,acy=0;
	if(cal(abx,aby,a,b)==true) {
		re=dis(a,b)/2;
		return true;
	}
	if(cal(bcx,bcy,b,c)==true){
		re=dis(b,c)/2;
		return true;
	}
	if(cal(acx,acy,a,c)==true){
		re=dis(a,c)/2;
		return true;
	}
	if((data[a.pre].x-abx)*(data[a.pre].x-acx)>0||(data[a.end].x-abx)*(data[a.end].x-acx)>0)
		return false;    
	if((data[b.pre].x-bcx)*(data[b.pre].x-abx)>0||(data[b.end].x-bcx)*(data[b.end].x-abx)>0)
		return false;
	if((data[c.pre].x-acx)*(data[c.pre].x-bcx)>0||(data[c.end].x-acx)*(data[c.end].x-bcx)>0)
		return false;
	double s=calacross(bcx-abx,bcy-aby,acx-abx,acy-aby); 
	double lendth=dis(abx,aby,acx,acy)+dis(abx,aby,bcx,bcy)+dis(bcx,bcy,acx,acy); 
	re=s/lendth; 
	return true;
}
void Re(){
	int i,j,k;
	double min=100000000;
	for(i=0;i<n-2;i++)
		for(j=i+1;j<n-1;j++)
			for(k=j+1;k<n;k++){
				if(ok(e[i],e[j],e[k]))
					if(fabs(re)<min)
						min=fabs(re);
			}
			printf("%lf\n",min);
}
void Cin(){
	int i;
	while(scanf("%d",&n)&&n){
		for(i=0;i<n;i++)
			scanf("%d%d",&data[i].x,&data[i].y);
		for(i=0;i<n-1;i++)  {
			e[i].pre=i;
			e[i].end=i+1;
		}
		e[n-1].pre=n-1;
		e[n-1].end=0;
		Re();
	}
}
int main(){
	Cin();
	return 0;
} 