/*  1177-Picture
 * 	2548K	60MS	C++	2601B
 * fengyu05
 * 题目:已知一些矩形的坐标,求重叠后总周长
 * 解法:线段树
*/
#include <iostream>
#include <algorithm>
using namespace std;
#define  N  5010 
struct  rec { int x, y, x1, y1; } r[N];
struct  Line{
    int  x, y1, y2; int  sign;
    Line(int  x=0,int y1=0,int y2=0, int d=0)
		:x(x), y1(y1), y2(y2),sign(d){}
	bool operator<(Line& l){ return x<l.x;}
} line[ 2*N+10 ];

int  n, ans;

// segmentTree 线段树
class segmentTree
{
public:
	struct node
	{
		int beg,end,cnt, // [beg,end]
			m,//测度
			line,//连续段数
			lbd,rbd;//左右端是否覆盖 1为覆盖，0不覆盖
		node *l,*r; // children
		node(int a,int b):beg(a),end(b),cnt(0),l(0),r(0),
			m(0),line(0),lbd(0),rbd(0){}
	};typedef node* link;
	link root;
	segmentTree(int a,int b){root=build(a,b);}

	link build(int a,int b){
		link p=new node(a,b);
		if(b-a>1){			
			p->l=build(a,(a+b)/2);
			p->r=build((a+b)/2,b);
		}
		return p;
	}
	void update(int a,int b,int val=1,link x=0){
		// val=1: insert val=-1: remove
		if(x==0) x=root;
		if(a<= x->beg && b>= x->end ) x->cnt+=val;
		else if(x->end - x->beg >1 ){
			int mid=(x->beg+x->end)/2;
			if(a< mid ) update(a,b,val,x->l);
			if(b> mid ) update(a,b,val,x->r);
		}
		update_m(x);
		update_lines(x);
	}
	void update_m(link x){
		if(x->cnt>0) x->m=x->end - x->beg;
		else if (x->end == x->beg+1)  x->m=0; //leaf
		else x->m=x->l->m + x->r->m;		
	}
	void update_lines(link x){
		if(x->cnt>0)
			x->lbd=x->rbd=x->line=1; // ldb, rbd , line =1		
		else if (x->end == x->beg+1) //leaf
			x->lbd=x->rbd=x->line=0; //
		else {
			x->lbd=x->l->lbd; x->rbd=x->r->rbd;
			x->line=x->l->line  +  x->r->line - (x->l->rbd * x->r->lbd);
		}
	}
};

int main()
{
    segmentTree st(-10000, 10000 );
    scanf("%d" ,  &n);
	int i;
    for(i = 0 ; i < n; i ++ )
    {
        scanf( "%d%d%d%d" ,  &r[i].x,  &r[i].y,  &r[i].x1,  &r[i].y1);
        line[ 2 * i]  =  Line(r[i].x , r[i].y, r[i].y1,0 );
        line[ 2*i+1]  =  Line(r[i].x1, r[i].y, r[i].y1,1 );
    }         
    sort(line, line+n * 2 );
	int nowM =0 , nowLine = 0,lastM = 0 ,lastLine = 0;
    for (i = 0 ; i < n * 2 ; i ++ )
    {
         if (line[i].sign == 0 )
            st.update(line[i].y1, line[i].y2,1);
         else  st.update(line[i].y1, line[i].y2,-1);
         nowM  =  st.root -> m;
         nowLine  =  st.root -> line;
         ans  +=  lastLine  *   2   *  (line[i].x - line[i-1].x);
         ans  +=  abs(nowM - lastM);
         lastM  =  nowM;
         lastLine  =  nowLine;
    }
    printf( "%d\n" , ans);
} 