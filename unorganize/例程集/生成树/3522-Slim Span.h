/* 3522 Slim Span
 *332K	93MS	C++	1791B
 * fengyu05 
 * ����:���Ƿ����slimness������,ʹ����������С�ߵĲ���С
 * �ⷨ:���ж���ͨ��,���ܲ���������������-1
 * �ѱ߰���С����,ö����С��,���δ�С˳������,����Ƿ�Ϊ������(ά�����鼯������)
 * һ����������,��Ϊ����С��Լ���µ�slimness������.�����ö�ٵ�����С��ֵ
 */
#include <iostream>
#include <algorithm>
using namespace std;

#define N 128
#define INF 0x7fffffff
int mat[N][N];//[0..n)

void init(int n){ for(int i=0;i<n;i++)
	for(int j=0;j<n;j++) mat[i][j]=INF;
}
struct EDGE{ 
	int u,v;
	int w;
	EDGE(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
} E[N*N/2];
bool operator<(const EDGE& a,const EDGE& b){	return a.w < b.w;}

int e_cnt,n;
bool flag[N];
void dfs(int v){
	flag[v]=1;
	e_cnt++;
	for(int i=0;i<n;i++){
		if(mat[v][i]!=INF&&flag[i]==0)
			dfs(i);
	}
}
bool mst(int n){//����Ƿ���������(�����ͨ��)
	e_cnt=0;
	memset(flag,0,sizeof(flag));
	dfs(0);
	return n==e_cnt;
}
//���鼯,�����������С,rΪ���Ľ����Ŀ
	int p[N],r[N];
	void UFset(int n){
		for(int i=0;i<n;i++){
			p[i]=i;
			r[i]=1;
		}
	}
	int find(int x){
		int t=x;
		while(t!=p[t]) t=p[t];
		while(x!=p[x]){int tmp=p[x];p[x]=t;x=tmp;}
		return t;
	}
	void Union(int x,int y){
		x=find(x),y=find(y);
		if(x==y) return;
		if(r[x]>r[y]){ p[y]=x; r[x]+=r[y],r[y]=0;}
		else{ p[x]=y; r[y]+=r[x],r[x]=0;}
	}
int main()
{	
	int m;
	while(scanf("%d%d",&n,&m),n){
		init(n);
		for(int i=0;i<m;i++){
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			x--,y--;
			mat[x][y]=mat[y][x]=z;
			E[i].u=x,E[i].v=y,E[i].w=z;
		}
		sort(E,E+m);
		if(!mst(n))	printf("-1\n");
		else{
			int re=INF;
			for(int j=0;j<=m-n+1;j++){
				int _min=E[j].w,_max=INF;
				UFset(n);
				int x,y;
				int k;
				for(k=j;k<j+n-2;k++){
					x=E[k].u,y=E[k].v;
					Union(x,y);
				}
				int cnt=r[find(x)];
				for(;k<m;k++){
					x=E[k].u,y=E[k].v;
					Union(x,y);
					cnt=r[find(x)];
					if(cnt==n){
						_max=E[k].w;
						break;
					}
				}
				if(_max!=INF)
					if(re>_max-_min) re=_max-_min;
			}
			printf("%d\n",re);
		}
	}
	return 0;
}