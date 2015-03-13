/*
 1556 The Doors
 fengyu05
 相交判断+最短路
*/
#include <iostream>
#include<cmath>
using namespace std;
#define N 128
#define INF 1e50
#define EP  1e-10
int dcmp(double x){if(x<-EP) return -1; else return(x>EP);}
inline double sqr(double x){ return x*x; }
struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y){}
} P[N];
struct LineSeg{  
	Point s,e;
	LineSeg(Point a=0, Point b=0) { s=a; e=b;}
} L[N/2];
double dis(Point p1,Point p2){				// |p2-p1|
	return sqrt(sqr(p1.x-p2.x)+sqr(p1.y-p2.y));
}
double det(double x1,double y1,double x2,double y2){
	return x1*y2-x2*y1;
}
double cross(Point a,Point b,Point c){	//(b-a)*(c-a)
	//return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
	return det(b.x-a.x,b.y-a.y,c.x-a.x,c.y-a.y);
}
bool intersect(LineSeg u,LineSeg v){  
	//跨立实验  
    return cross(u.s,v.s,v.e)*cross(u.e,v.s,v.e)<0&&
		cross(v.s,u.s,u.e)*cross(v.e,u.s,u.e)<0;
}
double mat[N][N];//mat[0..n)[0..n)
double dist[N];
void primary_Dij(int s,int n)
{
	bool flag[N]={0};
	for(int i=0;i<n;i++){
		dist[i]=mat[s][i];
	}
	flag[s]=true,dist[s]=0;
	for(int k=0;k<n;k++){
		double val=INF;
		int dex=-1;
		for(int j=0;j<n;j++)
			if(!flag[j] && val>dist[j])
				dex=j,val=dist[j];			
		if(dex==-1) return;
		flag[dex]=true;
		for(int i=0;i<n;i++)
			if(!flag[i] && dist[i]>dist[dex]+mat[dex][i]){
				dist[i]=dist[dex]+mat[dex][i];
			}
	}
}
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int n,cnt,lcnt;
	P[0]=Point(0,5);
	while(scanf("%d",&n),n!=-1){
		cnt=1,lcnt=0;
		int i,j;
		for(i=0;i<n;i++){			
			double x,y1=0,y2;
			scanf("%lf",&x);
			int four=4;
			while(four--){
				scanf("%lf",&y2);
				P[cnt++]=Point(x,y2);
				if(four%2==1)
					L[lcnt++]=LineSeg(Point(x,y1),Point(x,y2));
				y1=y2;
			}
			L[lcnt++]=LineSeg(Point(x,y2),Point(x,10));
		}
		P[cnt++]=Point(10,5);
		for(i=0;i<cnt;i++){
			for(j=0;j<cnt;j++){
				if(i==j) mat[i][j]=0;
				else mat[i][j]=INF;
			}
		}
		for(i=0;i<cnt;i++){
			for(j=i+1;j<cnt;j++){
				if(dcmp(P[i].x-P[j].x)==0)
					continue;
				LineSeg ls(P[i],P[j]);
				bool cro=false;
				for(int k=0;k<lcnt;k++){
					if(L[k].s.x<=P[i].x||L[k].s.x>=P[j].x)
						continue;
					if(intersect(ls,L[k])){
						cro=true;
						break;
					}
				}
				if(!cro)
					mat[i][j]=mat[j][i]=dis(P[i],P[j]);
			}
		}
		primary_Dij(0,cnt);
		printf("%.2lf\n",dist[cnt-1]);
	}
	return 0;
}