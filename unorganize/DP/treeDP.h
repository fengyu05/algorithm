#include<iostream>
#include<algorithm>
using namespace std;
#define INF 100000000
template<typename T>  
void make2Darray(T **&x,int rows,int cols){
	x=new T*[rows];  
	T *p =new T[rows*cols];  
	for(int i=0;i<rows;i++)  
		x[i]=p+i*cols;
}
template<typename T>
void destroy2Darray(T **x){  
	delete [] x[0];
	delete [] x;  
}
#define N 128
int n,k;
struct binode{
	int w,d,dep;
	int cost[N][N],dis[N];
	binode *p,*l,*r;
	binode(){w=d=dep=0;p=l=r=0;}
};
typedef binode* link;
link subt[N];
link findc(link q){
	while(q&&q->r) q=q->r;
	return q;
}
void adddep(link t){
	if(t->p) t->dep=t->p->dep+1;
	//make2Darray(t->cost,k+1,t->dep+1);
	t->dis[0]=0;
	if(t->p){
		for(int i=1;i<=t->dep;i++)
			t->dis[i]=t->p->dis[i-1]+t->d;
	}
}
void comp(link t){
	if(!t->l){
		for(int j=0;j<=t->dep;j++)
			t->cost[0][j]=t->w*t->dis[j];
		for(int i=1;i<=k;i++)
			for(int j=0;j<=t->dep;j++)
				t->cost[i][j]=0;
	}else{
		for(int i=0;i<=k;i++){
			for(int j=0;j<=t->dep;j++){
				if(i>0) t->cost[i][j]=t->cost[i-1][0];
				else t->cost[i][j]=INF;
				for(int a=0;a<=i;a++){
					int tmp=t->l->cost[a][j+1]+t->r->cost[i-a][j+1]+
						t->w*t->dis[j];
					if(t->cost[i][j]>tmp) t->cost[i][j]=tmp;
				}
			}
		}
	}
}
void PreOrder(void(*Visit)(link u),link t){
	if(t){
		Visit(t);
		PreOrder(Visit,t->l);
		PreOrder(Visit,t->r);
	}
}
void PostOrder(void(*Visit)(link u),link t){
	if(t){
		PreOrder(Visit,t->l);
		PreOrder(Visit,t->r);
		Visit(t);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int a,b,c;
	cin>>n>>k;
	for(int i=0;i<=n;i++) subt[i]=new binode;
	// input
	for(i=1;i<=n;i++){
		cin>>a>>b>>c;
		subt[i]->w=a;subt[i]->d=c;
		link p=findc(subt[b]);
		link q=new binode;
		p->l=subt[i];p->r=q;
		subt[i]->p=p;q->p=p;
	}
	PreOrder(adddep,subt[0]);
	PostOrder(comp,subt[0]);
	cout<<subt[0]->cost[k][0];
	return 0;
}