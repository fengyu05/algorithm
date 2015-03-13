#include <iostream>
#include <algorithm>
using namespace std;

#define min(a,b) (a<b?a:b)
#define INF INT_MAX
#define N  300

//最短增广路标号算法
// d(x):距离标号,与t的距离
//1. d(t)=0
//2. 对残余网络N(x)中的弧 i-j
//   d(i)<=d(j)+1
//  如果d(i)=d(j)+1,i-j为允许弧(admissible arc)
//  由允许弧组成的路径为允许路径(admissible path)
//  允许路径是N(x)中的最短增广路   
class LabelShortestAugment{ // best in practise for maxflow
public:
    int c[N][N],f[N][N], maxflow;   
	int V,ss,tt,pred[N],d[N],numb[N];
	int queue[N];
	void init(){
		memset(c,0,sizeof(c));
		memset(f,0,sizeof(f));
		maxflow=0;
	}
    int MaxFlow(int s, int t,int n)
	{
		ss = s, tt = t, V=n;
		// assert(ss != tt);
		maxflow = 0; 
		label();
		int i=ss;
		while(d[ss]<n){
			bool flag=true;// mark whether retreat
			for(int j = 0; j < V; ++j){// i->j is admissible arc
				if(c[i][j]>0&&d[i]==d[j]+1)
				{
					// advance i->j
					pred[j]=i;
					i=j;
					if(i==t){
						augment();
						i=ss;
					}
					flag=false;
					break;
				}
			}
			if(flag){// 没有找到admissible arc, 则retreat 
				if(numb[d[i]]==1) return maxflow;// termination
				int minval=n;// [key point] 最大的标号小于n
				for(int j = 0; j < V; ++j){// i->j 
					if(c[i][j]>0&&d[j]+1<minval)
						minval=d[j]+1;
				}
				numb[d[i]]--;
				numb[minval]++;
				d[i]=minval;
				if(i!=ss) i=pred[i];
			}
		}
		return maxflow;
	}
	void augment(){
		int tiny=INF;
		int v=tt, w=pred[v];// trace back
		do{
			if(tiny > c[w][v]) tiny = c[w][v];
			v = w, w = pred[v];
		}while(v != ss);   
		v = tt, w = pred[v];
		do{
			f[w][v] += tiny;
			f[v][w] -= tiny;
			c[w][v] -= tiny;
			c[v][w] += tiny;
			v = w, w = pred[v];
		}while(v != ss);
		maxflow += tiny; 
	}
	void label(){// use bfs from tt to label each node
		memset(d, 0xff, sizeof(int)*V); // set d[..]=-1
		memset(numb, 0, sizeof(int)*V); // set numb[..]=0
		int front=-1,end=-1;
		d[tt] = 0;
		numb[d[tt]]++;
		queue[++end]=tt;
		while(front<end)
		{
			int v = queue[++front];
			for(int j = 0; j < V; ++j)// j->v
				if(c[j][v]>0 && d[j]<0)
				{
					d[j] = d[v]+1;
					numb[d[j]]++;
					queue[++end]=j;
				}   
		}
	}

};
LabelShortestAugment flow;
// test1
void test1(){
	flow.c[1][2]=flow.c[1][3]=flow.c[1][4]=flow.c[1][5]=flow.c[1][6]=2;
	flow.c[2][7]=flow.c[3][8]=flow.c[4][9]=flow.c[5][10]=flow.c[6][11]=1;
	flow.c[7][0]=flow.c[8][0]=flow.c[9][0]=flow.c[10][0]=flow.c[11][0]=2;
	flow.MaxFlow(1,0,12);
}
// test2
// test in Power Network POJ(1459) // 892K	46MS
             // without record flow.f 620K	32MS

int main()
{
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	//test1();
	
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
	}	//*/
	return 0;
}