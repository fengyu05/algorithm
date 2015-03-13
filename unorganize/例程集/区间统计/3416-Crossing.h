/*  3416-Crossing	
 * 3604K	280MS	C++	1904B
 * fengyu05
 * 题目:给出平面n个点,和m个分割点,问分割点mi的(I,III象限内的点数之和)
   与(II,IV象限点数之和)的差值.
 * 方法:树状数组
 * Hint:Sort the queries in non-descending order of x. 
 For each query, evaluate the amounts of  points in area III, 
 under the horizontal  line and to the left of the vertical line.
 You may use Segment-Tree or tree-Array to implement it. 
*/
#include <iostream>
#include <algorithm>
using namespace std;
#define N 50000
#define M 524288
struct Point{
	int x,y,id;
	Point(int x=0,int y=0,int id=-1):x(x),y(y),id(id){}
} p[2*N];
bool operator<(Point& a,Point& b){ return a.x<b.x;}

int gt2(int x){
	// return the int which is the power of 2
	// and closest to x
	int re=1;
	while(x>=1){
		x/=2;
		re*=2;
	}
	return re;
}
class treeA{
public:
	int c[M],size; // size must be the power of 2
	int lowBit(int x) {
		return x & (x ^ (x - 1));
	}
	void add(int x, int k) { // k can be negative 
		// a[x] += k
		while (x <= size) {
			c[x-1] += k;
			x += lowBit(x);
		}
	}
	int query(int x) {// sum:a[1..x];
		int ret = 0;
		while (x > 0) {
			ret += c[x-1];
			x -= lowBit(x);
		}
		return ret;
	}
	int query(int x,int y){ // sum:a(x..y]
		return query(y)-query(x);
	}
	int other(int x){ //sum:a(x..size]
		return c[size-1]-query(x);
	}
	void init(int maxsize){
		size=maxsize;
		memset(c,0,sizeof(c));
	}
} c1;
int a[N];

int main()
{	
	int cas,n,m;
	scanf("%d",&cas);
	while(cas--){

		scanf("%d%d",&n,&m);
		int i;
		int _max=1;
		for(i=0;i<n+m;i++){
			scanf("%d%d",&p[i].x,&p[i].y);
			p[i].y+=1;
			if(p[i].y>_max) _max=p[i].y;
			if(i<n)
				p[i].id=-1;
			else
				p[i].id=i-n;
		}
		memset(a,0,sizeof(a));
		sort(p,p+n+m);
		_max=gt2(_max);
		c1.init(_max);
		for(i=0;i<m+n;i++){
			if(p[i].id>-1){
				int id=p[i].id;
				a[id]+=c1.query(p[i].y);
				a[id]-=c1.other(p[i].y);				
			}else{
				c1.add(p[i].y,1);
			}
		}
		for(i=0;i<m+n;i++){
			if(p[i].id>-1){
				int id=p[i].id;
				a[id]-=c1.query(p[i].y);
				a[id]+=c1.other(p[i].y);				
			}else{
				c1.add(p[i].y,-1);
			}
		}
		for(i=0;i<m;i++){
			printf("%d\n",abs(a[i]));
		}
		if(cas>0) printf("\n");
	}
	return 0;
}