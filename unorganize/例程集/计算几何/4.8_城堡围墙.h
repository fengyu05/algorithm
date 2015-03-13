/* 城堡围墙 
 * 求凸包
*/
#include <iostream>
#include <cmath>
using namespace std;

const double Pi = acos(-1.);
#define N 1024
struct Point{
	int x,y;
} p[2*N],convex[N];
double sqr(int x){ return x*x; }
double dist(Point& p1,Point& p2){				// |p2-p1|
	return sqrt(sqr(p1.x-p2.x)+sqr(p1.y-p2.y));
}
int cross(Point& a,Point& b,Point& c){	//(b-a)*(c-a)
	return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int n,l;
	scanf("%d%d",&n,&l);
	int i;
	for(i=1;i<=n;i++){//输入已经排序,可在O(n)内求凸包
		scanf("%d%d",&p[i].x,&p[i].y);
		p[n+i]=p[i];
	}
	//最左点
	int leftest=1;
	for(i=2;i<=n;i++){
		if(p[i].x<p[leftest].x) leftest=i;
	}
	convex[1]=p[leftest];
	int k=1,cur=leftest;
	//求凸包
	do{
		int next=cur+1;
		for(int i=cur+2;i<=leftest+n;i++){
			if(cross(p[cur],p[i],p[next])<0) next=i;
		}
		convex[++k]=p[next];
		cur=next;
	}while(cur!=leftest+n);
	double len=0;
	for(i=1;i<=k-1;i++)
		len+=dist(convex[i],convex[i+1]);
	len+=2*Pi*l;
	printf("%.0lf\n",len);
	return 0;
}