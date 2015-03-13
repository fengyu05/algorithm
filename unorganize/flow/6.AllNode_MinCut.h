/* ȫ����С�и�
 * fengyu05
 * test :POJ 2914 Minimum Cut
 * 2296K	5532MS	C++	2463B
��С�� Stoer-Wagner �㷨 
Stoer-Wagner �㷨����������ͼ G=(V, E)��ȫ����С� 
	�㷨��������һ��������������s, t �� V��ȫ����С����ߵ���
	ԭͼ��s-t ��С����ߵ��ڽ�ԭͼ���� Contract(s,t)�������õ�
	ͼ��ȫ����С� 
 
�㷨��ܣ� 
1. �赱ǰ�ҵ�����С��MinCut Ϊ+��  
2. �� G��������� s-t ��С�� c��MinCut = min(MinCut, c)  
3. �� G�� Contract(s, t)�������õ� G'=(V', E')��
��|V'|>1����G=G'��ת 2������MinCut Ϊԭͼ��ȫ����С��  
 
Contract �������壺 
�������ڱ�(p, q)�������(p, q)Ȩֵw(p, q) = 0 
Contract(a, b): ɾ���� a, b ����(a, b)�������½ڵ� c��
�������� v��V ��w(v, c) = w(c, v) = w(a, v) + w(b,v) 

*/
#include <iostream>
#include <algorithm>
using namespace std;

#define min(a,b) (a<b?a:b)
#define INF INT_MAX
#define N  512

class BasAugment
{
public:
    int c[N][N], maxflow;   
	int V,ss,tt,pred[N];	
	void init(){
		memset(c,0,sizeof(c));
		maxflow=0;
	}
    int MaxFlow(int s, int t,int n)
	{
		ss = s, tt = t, V=n;
		// assert(ss != tt);
		maxflow = 0; 
		while(bfs())
			augment();
		return maxflow;
	}
	void augment()
	{
		int tiny=INF;
		int v=tt, w=pred[v];// trace back
		do{
			if(tiny > c[w][v]) tiny = c[w][v];
			v = w, w = pred[v];
		}while(v != ss);   
		v = tt, w = pred[v];
		do{
			c[w][v] -= tiny;
			c[v][w] += tiny;
			v = w, w = pred[v];
		}while(v != ss);
		maxflow += tiny;   
	}
	//���·����·��
	int queue[N];
    bool bfs() 
	{
		memset(pred, 0xff, sizeof(int)*V); // set pred[..]=-1
		int front=-1,end=-1;
		pred[ss] = ss;
		queue[++end]=ss;
		while(front<end)
		{
			int v = queue[++front];// v->j
			for(int j = 0; j < V; ++j)
				if(c[v][j]>0 && pred[j]<0)
				{
					pred[j] = v;
					if(j == tt)	return 1;
					queue[++end]=j;
				}   
		}   
		return 0;
	}
} flow;

int mat[N][N];
int Stoer_Wagner(int n){
	int re=INF;
	do{
		int s=n-2,t=n-1;
		for(int j=0;j<n;j++) for(int k=0;k<n;k++)
			flow.c[j][k]=mat[j][k];
		flow.maxflow=0;
		int tmp=flow.MaxFlow(s,t,n);
		re=min(re,tmp);
		n--;
		for(int i=0;i<n-1;i++){
			mat[i][n-1]+=mat[i][n];
			mat[n-1][i]=mat[i][n-1];
		}
	}while(n>1);
	return re;
}
int main()
{	
	int n,m;
	while(scanf("%d%d",&n,&m)==2){
		memset(mat,0,sizeof(mat));
		int x,y,z;
		while(m--){
			scanf("%d%d%d",&x,&y,&z);
			mat[x][y]+=z;
			mat[y][x]+=z;
		}
		printf("%d\n",Stoer_Wagner(n));
	}
	return 0;
}