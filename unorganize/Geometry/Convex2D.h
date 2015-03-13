#include <iostream>
#include <algorithm>
using namespace std;
#define N 128
struct Point{
	int x,y,id;
	bool del;
	Point(int x=0,int y=0):x(x),y(y){del=0;}
} p[N];
int Area2(Point& a,Point& b,Point& c){
	return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
bool operator<(Point& a,Point& b){// compare with left
	int area=Area2(p[0],a,b);
	if(area>0) return true;
	else if(area<0) return false;
	else{
		int x=abs(a.x-p[0].x)-abs(b.x-p[0].x);
		int y=abs(a.y-p[0].y)-abs(b.y-p[0].y);
		if(x<0||y<0){ a.del=true; return false;}
		else{ b.del=true; return true;}
	}
}
int Graham(int n,Point out[]){
	// find lowest
	int i,m=0;// index of lowest so far
	for(i=1;i<n;i++)
		if(p[i].y<p[m].y||p[i].y==p[m].y&&p[i].x>p[m].x)
			m=i;
	swap(p[0],p[m]);
	// qsort
	sort(p+1,p+n);
	out[0]=p[0],out[1]=p[1];
	int cnt=2;
	i=2;
	while(i<n){
		if(p[i].del==true){i++;continue;}
		if(Area2(out[cnt-2],out[cnt-1],p[i])>0){
			out[cnt]=p[i];
			cnt++;
			i++;
		}else cnt--;
	}return cnt;
}
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	Point out[N];
	int x,y;
	int n=0,cnt;
	while(scanf("%d%d",&x,&y)==2){
		p[n].x=x,p[n].y=y;
		p[n].id=n;
		n++;
	}
	cnt=Graham(n,out);
	return 0;
}
/*
input:
3 3
3 5
0 1
2 5
-2 2
-3 2
6 5
-3 4
-5 2
-5 -1
1 -2
-3 -2
4 2
5 1
-5 1
3 -2
0 5
0 0
7 4
output:
cnt=8 id:15 18 6 16 7 8 9 11
*/