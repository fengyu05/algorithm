// 给出一堆直线，计算三角行数量
#define N 128
#define EP  1e-10
const double Pi = acos(-1.);

struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y){}
};
// 直线的解析方程 a*x+b*y+c=0  约定 a>= 0 
struct Line{  
	double a,b,c;
	Line(double d1=1, double d2=-1, double d3=0){a=d1; b=d2; c=d3;}
} l[N];
// 判断 l1, l2 相交且返回交点p   
bool lineintersect(Line l1,Line l2,Point &p) // 是 L1,L2  
{  
	double d=l1.a*l2.b-l2.a*l1.b;
	if(fabs(d)<EP) // 不相交  
		return false;
	p.x = (l2.c*l1.b-l1.c*l2.b)/d;
	p.y = (l2.a*l1.c-l1.a*l2.c)/d;
		return true;
}
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int n,i;
	while(scanf("%d",&n)==1){
		for(i=0;i<n;i++){
			scanf("%lf%lf%lf",&l[i].a,&l[i].b,&l[i].c);
		}
		int cnt=0;
		for(i=0;i<n;i++){
			for(int j=i+1;j<n;j++){
				for(int k=j+1;k<n;k++){
					Point p1,p2,p3;
					if(lineintersect(l[i],l[j],p1)
						&&lineintersect(l[i],l[k],p2)
						&&lineintersect(l[j],l[k],p3) ){
						if(fabs(p1.x-p2.x)<EP && fabs(p1.y-p2.y)<EP )
							continue;
						else cnt++;
					}
				}
			}
		}
		printf("%d\n",cnt);
	}
	return 0;
}