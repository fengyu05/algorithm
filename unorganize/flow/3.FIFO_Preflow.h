#include <iostream>
using namespace std;
template<class Item,int __SIZE>class Queue{
public:
	Item array[__SIZE];
	int front,rear;
	void init(){front=-1,rear=-1;}
	int next(int pos){return (pos+1)%__SIZE;}
	void push(Item x){ array[rear=next(rear)]=x;}
	Item pop(){ return array[front=next(front)];}
	int size(){ return rear-front;}
};
#define min(a,b) (a<b?a:b)
#define INF INT_MAX
#define N  400

class FIFO_Preflow
{
public:
    int V,ss,tt,c[N][N],f[N][N],maxflow;
    int e[N],d[N]; 
	void init(){
		memset(c,0,sizeof(c));
		memset(f,0,sizeof(f));
		maxflow=0;
	}
	Queue<int,N> que;
	int MaxFlow(int s, int t,int n)
	{
		V=n,ss=s,tt=t;
		preprocess();
		while(que.size()){
			int i=que.pop();
			if(i==ss||i==tt) continue;//ignore ss tt 
			int orgin=e[i];// mark for check whether e[i] decrease
			for(int j = 0; j < V && e[i]>0; ++j){// i->j
				if(c[i][j]>0 && d[i]==d[j]+1)
				{
					// push flow
					int val=min(e[i],c[i][j]);
					e[i]-=val; e[j]+=val;
					update(i,j,val);
					if(j!=tt) que.push(j);
				}
			}
			//relable
			if(e[i]==orgin) relable(i);
			if(e[i]>0) que.push(i);
		}
		return e[tt];
	}
	void relable(int i){
		int minval=INF;
		for(int j = 0; j < V; ++j){// i->j 
			if(c[i][j]>0&&d[j]+1<minval)
				minval=d[j]+1;
		}
		if(minval==INF) minval=V; // i is isolation
		// [key point] 最大的标号小于V
		d[i]=minval;
	}
	void preprocess(){
		memset(d, 0xff, sizeof(int)*V); // set d[..]=-1
		memset(e, 0, sizeof(int)*V); // set e[..]=0
		// compute the exact distance labels
		que.init();
		d[tt] = 0;
		que.push(tt);
		while(que.size())
		{
			int v = que.pop();
			for(int j = 0; j < V; ++j)// j->v
				if(c[j][v]>0 && d[j]<0)
				{
					d[j] = d[v]+1;
					que.push(j);
				}   
		}
		// set each node adjacent to node s a positive excess
		que.init();
		for(int j = 0; j < V; ++j)// ss-j
			if(c[ss][j]>0)
			{
				e[j] = c[ss][j];
				update(ss,j,e[j]);			
				que.push(j);
			}  
		d[ss]=V;
	}
	void update(int v,int w,int tiny){// push tiny at v->w
		f[v][w] += tiny;
		f[w][v] -= tiny;
		c[v][w] -= tiny;
		c[w][v] += tiny;
	}
};
FIFO_Preflow flow;
// test1
void test1(){
	flow.init();
	flow.c[1][2]=2;
	flow.c[1][3]=4;
	flow.c[2][3]=3;
	flow.c[3][0]=5;
	flow.c[2][0]=1;
	flow.MaxFlow(1,0,4);
}
// test2
// test in Power Network POJ(1459)
int main()
{
#ifndef ONLINE_JUDGE
  	freopen("t.in", "r", stdin);
#endif
	//test1();
//
	int n,e,i,cap;
	int p,c,a,b,ans;
	char ch;
	while(scanf("%d %d %d %d",&n,&p,&c,&e)==4)
	{
		flow.init();
		for(i = 0; i < e; ++i)
		{
			while((ch=getchar()) !='(');
			scanf("%d,%d)%d",&a,&b,&cap);
			flow.c[a][b] = cap;
		}
		for(i = 0; i < p; ++i)
		{
			while((ch=getchar()) !='(');
			scanf("%d)%d",&a, &cap);
			flow.c[n][a] = cap;
		}
		for(i = 0; i < c; ++i)
		{
			while((ch=getchar()) !='(');
			scanf("%d)%d",&a, &cap);
			flow.c[a][n+1] = cap;
		}      
		ans=flow.MaxFlow(n,n+1,n+2);
		printf("%d\n",ans);
	}//*/
	return 0;
}
