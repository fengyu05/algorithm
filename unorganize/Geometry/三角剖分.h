/*
Polygon Triangulation
任意多边形 三角剖分
fengyu
*/
#include <iostream>
using namespace std;
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
int v_cnt;
struct vertex{
	int x,y,id;
	vertex *prev,*next;
	bool ear;
	vertex(int x,int y,int id):x(x),y(y),id(id){}
};
typedef vertex* vlk;
vlk vtx;
void add(int x,int y){
	if(vtx==0){
		vtx=new vertex(x,y,v_cnt);
		vtx->next=vtx;
		vtx->prev=vtx;
	}else{
		vlk cur=new vertex(x,y,v_cnt);
		cur->next=vtx;
		cur->prev=vtx->prev;
		vtx->prev=cur;
		cur->prev->next=cur;
	}

	v_cnt++;
}
int Area2(vertex& a,vertex& b,vertex& c){
	return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
bool IntersectProp(vlk a,vlk b,vlk c,vlk d){
	return Area2(*a,*b,*c)*Area2(*a,*b,*d)<0 &&
			Area2(*c,*d,*a)*Area2(*c,*d,*b)<0;
}
bool Between(vlk a,vlk b,vlk c){
	if(Area2(*a,*b,*c)!=0) return false;//not collinear false
	if(a->x!=b->x){
		return (c->x<=max(a->x,b->x))
			&&(c->x>=min(a->x,b->x));
	}else
		return (c->y<=max(a->y,b->y))
			&&(c->y>=min(a->y,b->y));
}
bool Intersect(vlk a,vlk b,vlk c,vlk d){
	if(IntersectProp(a,b,c,d)) return true;
	else if(Between(a,b,c)||Between(a,b,d)
		||Between(c,d,a)||Between(c,d,b)
		)
		return true;
	else return false;
}
bool InCone(vlk a,vlk b){
	vlk a0,a1;
	a1=a->next,a0=a->prev;
	if(Area2(*a,*a1,*a0)>=0){
		return Area2(*a,*b,*a0)>0&&Area2(*b,*a,*a1)>0;
	}else
		return !(Area2(*a,*b,*a1)>=0&&Area2(*b,*a,*a0)>=0);
}
bool Diagonalie(vlk a,vlk b){
	vlk c=vtx,c1;
	do{
		c1=c->next;
		if( (c!=a)&&(c1!=a)&&(c!=b)&&(c1!=b)&&
			Intersect(a,b,c,c1) )
			return false;
		c=c->next;
	}while(c!=vtx);
	return true;
}
bool Diagonal(vlk a,vlk b){
	return InCone(a,b)&&InCone(b,a)&&Diagonalie(a,b);
}
void EarInit(){
	vlk v0,v1,v2;
	v1=vtx;
	do{
		v2=v1->next;
		v0=v1->prev;
		v1->ear=Diagonal(v0,v2);
		v1=v1->next;
	}while(v1!=vtx);
}
void Triangulate(){
	vlk v0,v1,v2,v3,v4;
	int n=v_cnt;
	EarInit();
	while(n>3){
		v2=vtx;
		do{
			if(v2->ear){
				v3=v2->next;v4=v3->next;
				v1=v2->prev;v0=v1->prev;
				// output
				printf("%d--%d\n",v1->id,v3->id);
				v1->ear=Diagonal(v0,v3);
				v3->ear=Diagonal(v1,v4);
				v1->next=v3;
				v3->prev=v1;
				vtx=v3;
				n--;
				break;
			}		
			v2=v2->next;
		}while(v2!=vtx);
	}
}
int main()
{
	freopen("t.in", "r", stdin);
	int n;
	scanf("%d",&n);
	v_cnt=0;
	vtx=0;
	while(n--){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	Triangulate();
	return 0;
	/*
input:n和点集[0..18)
18
0 0
10 7
12 3
20 8
13 17
10 12
12 14
14 9
8 10
6 14
10 15
7 18
0 16
1 13
3 15
5 8
-2 9
5 5
output:切线两点的id
17--1
1--3
4--6
4--7
9--11
12--14
15--17
15--1
15--3
3--7
11--14
15--7
15--8
15--9
9--14
	*/
}