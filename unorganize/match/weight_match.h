#include <iostream>
using namespace std;
// -----------------���Ȩ����ƥ�� -----------------------
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define N 512
#define INF 0x7fffffff

bool map[N][N];
// ����ͼ�������ͼ, map[i][j] = true ����Xi��Yj�б�
bool xckd[N], yckd[N];
// �����һ��DFS�У�Xi��Yi�Ƿ��ڽ�������
int match[N];
//ƥ����Ϣ������iΪY�еĶ����ţ�match[i]ΪX�ж�����
int edge[N][N];//��Ȩ
bool DFS(int p,int n)
{//Ѱ���Ƿ�����XpΪ��������·����
 //����ֵΪ�Ƿ�������·
   int i;
   for(i = 0; i < n; i++) {
      if(!yckd[i] && map[p][i]) {
         yckd[i] = true;
         int t = match[i];
         match[i] = p;
         if(t == -1 || DFS(t, n)) {
            return true;
         }
         match[i] = t;
         if(t != -1) xckd[t] = true;
      }
   }
   return false;
}

void KM_Perfect_Match(int n){
   int i, j;
   int lx[N], ly[N];   //  KM�㷨��Xi��Yi�ı��
   for(i = 0; i < n; i++) {
      lx[i] = -INF;
      ly[i] = 0;
      for(j = 0; j < n; j++) {
         lx[i] = max(lx[i], edge[i][j]);
		 // lx[i] = min(...) for ��Сƥ��
      }
   }
    bool perfect = false;
    while(!perfect) {
      //  ��ʼ���ڽӾ���
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
            if(lx[i]+ly[j] == edge[i][j]) map[i][j] = true;
            else map[i][j] = false;
         }
      }
      // ƥ�����
      int live = 0;
      memset(match, -1, sizeof(match));
      for(i = 0; i < n; i++) {
         memset(xckd, false, sizeof(xckd));
         memset(yckd, false, sizeof(yckd));
         if(DFS(i, n)) live++;
         else {
            xckd[i] = true;
            break;
         }
      }
      if(live == n) perfect = true;
      else {
         // �޸ı�Ź���
         int ex = INF; //-INF for ��Сƥ��
         for(i = 0; i < n; i++) {
            for(j = 0; xckd[i] && j < n; j++) {
               if(!yckd[j]) ex = min(ex, lx[i]+ly[j]-edge[i][j]);
			   // ex = max(...) for ��Сƥ��
            }
         }
         for(i = 0; i < n; i++) {
            if(xckd[i]) lx[i] -= ex;
            if(yckd[i]) ly[i] += ex;
         }
      }
   }
}

int main(){
   /***************************************************
    *  ��ȡ����ͼÿ�����ߵ�Ȩ��������edge[][]��,
    *  ��X��Y��Ŀ���ȣ�Ӧ�����ϵĶ���
    *  �������ͼ��X��Y�Ķ�����n,����һ������Ӧ��
    *  ����Ӷ�����Ϻ��n
    ***************************************************/
   KM_Perfect_Match(n);
   int cost = 0;
   for(int i = 0; i < n; i++) {
      cost += edge[match[i]][i];
   }
   // cost Ϊ���ƥ����ܺ�, match[]�б���ƥ����Ϣ
   return 0;
}


//----------------------���Ȩ����ƥ��-------------------
#define N 128
#define INF 0x6fffffff
#define _clr(ar) memset(ar,0,sizeof(ar))
int cx[N],cy[N],sx[N],sy[N],lx[N],ly[N];
int nx,ny,mat[N][N];
int path(int u)
{
	sx[u]=1;
	for(int v=1;v<=ny;v++)
		if(mat[u][v]==lx[u]+ly[v] && !sy[v]){
			sy[v]=1;
			if (!cy[v] || path(cy[v]) ){
				cx[u]=v; cy[v]=u;
				return 1;
			}
		}
	return 0;
}
int KuhnMunkres()
{
	int i , j;
	_clr(lx),_clr(ly),_clr(cx),_clr(cy);
	for( i=1;i<=nx; i++)
		for( j=1;j<=ny; j++)
			if(lx[i]<mat[i][j])
				lx[i]=mat[ i ][ j ];
	for(int u=1; u<=nx; u++) if(!cx[u]) {
		_clr(sx),_clr(sy);
		while(!path(u)){
			int _min=INF;
			for( i=1;i<=nx; i++) if(sx[i])
				for(j=1;j<=ny; j++) if (!sy[j])
					if (lx[i]+ly[j]-mat[i][j]<_min )
						_min=lx[i]+ly[j]-mat[ i ][ j ];
			for( i=1;i<=nx; i++) if(sx[i]){
				lx[i]-=_min; sx[i]=0;
			}
			for( j=1;j<=ny; j++) if(sy[j]){
				ly[j]+=_min; sy[j]=0;
			}
		};
	}
	int cost = 0;
	for(i = 1; i <= nx; i++) {
		cost += mat[i][cx[i]];
	} return cost;
}