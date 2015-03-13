#include <iostream>
using namespace std;
//Stern-Brocot Tree
//分数有序列生成树
struct node{
	int x,y; // x/y
	char sign; // -1 left ,1 right
	node *l,*r,*p;
	node(int x=0,int y=0,node* p=0,int sign=0)
		:x(x),y(y),p(p),sign(sign){ l=0;r=0;}
};
typedef node* link;
link O,root;
void __free(link t){
	if(t!=0){
		__free(t->l);
		__free(t->r);
		delete t;
	}
}
#define MAX_LV 5 // [ 1/lv , 1/1]  
void gen(link t,int lv){
	if(lv>=MAX_LV) return;
	link c1,c2;
	c1=c2=t;
	while(c1->sign<0) c1=c1->p; // find a r:p-link
	while(c2->sign>0) c2=c2->p; // find a l:p-link
	c1=c1->p;
	c2=c2->p;
	t->l=new node(t->x+c1->x,t->y+c1->y,t,-1);
	t->r=new node(t->x+c2->x,t->y+c2->y,t,1);
	gen(t->l,lv+1);
	gen(t->r,lv+1);
}
void gen(){
	O=new node(0,1);
	root=new node(1,1,O,1);
	link second=new node(1,2,root,-1);
	root->l=second;
	gen(second,2);
}
void walk(link x){
		if(x!=0){
			walk(x->l);
			printf("%d\\%d\n",x->x,x->y);
			walk(x->r);			
		}
	}
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	gen();
	walk(root);
	return 0;
}