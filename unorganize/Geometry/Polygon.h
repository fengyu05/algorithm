#include <iostream>

typedef int type; 
struct Point{
	type x,y;
	Point(type x,type y):x(x),y(y){}
};

struct Vertex{
	int id;
	Point v;
	bool ear;
	Vertex *next,*prev;
	Vertex(Point v):v(v){}
};
typedef Vertex *ptrVertex;
void add(ptrVertex head,Point v){
	ptrVertex p=new Vertex(v);
	if(head){
		p->next=head;
		p->prev=head->prev;
		head->prev=p;
		p->prev->next=p;
	}else{
		head=p;
		head->next=head->prev=p;
	}
}
type Area2(Point a,Point b,Point c){
	return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
type Area2(ptrVertex head){
	type sum=0;
	ptrVertex p,a;
	p=head;
	a=p->next;
	do{
		sum+=Area2(p->v,a->v,a->next->v);
		a=a->next;
	}while(a->next!=head);
	return sum;
}

bool IntersectProp(Point a,Point b,Point c,Point d){
	return Area2(a,b,c)*Area2(a,b,d)<0 &&
		   Area2(c,d,a)*Area2(c,d,b)<0 ;
}
bool Between(Point a,Point b,Point c){ // c between a-b
	return Area2(a,b,c)==0 &&
	(c.x-a.x)*(c.x-b.x)<=0 && (c.y-a.y)*(c.y-b.y)<=0 ;
}
bool Intersect(Point a,Point b,Point c,Point d){
	return IntersectProp(a,b,c,d)||
		Between(a,b,c)||Between(a,b,d) ||
		Between(c,d,a)||Between(c,d,b);
}
bool Diagonalie(ptrVertex a,ptrVertex b,ptrVertex head){
	ptrVertex c=head,c1;
	do{
		c1=c->next;
		if( c!=a && c1!=a && c!=b && c1!=b &&
			Intersect(a->v,b->v,c->v,c1->v) )
			return false;
		c=c->next;
	}while(c!=head) ;
	return true;
}
bool InCone(ptrVertex a,ptrVertex b,ptrVertex head){
	ptrVertex a0=a->prev,a1=a->next;
	if(Area2(a->v,a1->v,a0->v)>=0)
		return Area2(a->v,b->v,a0->v)>0 &&
			   Area2(b->v,a->v,a1->v)>0;
	else
		return Area2(a->v,b->v,a1->v)<0 ||
			   Area2(b->v,a->v,a0->v)<0 ;
}
bool Diagonal(ptrVertex a,ptrVertex b,ptrVertex head){
	return InCone(a,b,head)&&InCone(b,a,head)
		&&Diagonalie(a,b,head);
}
void EarInit(ptrVertex head){
	ptrVertex v0,v1=head,v2;
	do{
		v2=v1->next;
		v0=v1->prev;
		v1->ear=Diagonal(v0,v2);
		v1=v1->next;
	}while(v1!=head);
}
void Triangulate(ptrVertex head,int n){
	ptrVertex v0,v1,v2,v3,v4;
	EarInit();
	while(n>3){
		do{
			if(v2->ear){
				v3=v2->next; v4=v3->next;
				v1=v2->next; v0=v1->next;

				PrintDiagonal(v1,v3);
				v1->ear=Diagonal(v0,v3);
				v3->ear=Diagonal(v1,v4);

				v1->next=v3;
				v3->prev=v1;
				head=v3;
				n--;
				break;
			}
		}whle(v2!=head);
	}
}
int main()
{
#ifndef ONLINE_JUDGE
  	freopen("t.in", "r", stdin);
#endif
	
	return 0;
}
