/*
��Ȩͼ���Ȩƥ��--KM�㷨[ת]

KM�㷨��ͨ����ÿ������һ����ţ��������꣩���������Ȩƥ�������ת��Ϊ���걸ƥ
�������ġ��趥��Xi�Ķ���ΪA[i]������Yi�Ķ���ΪB[i]������Xi��Yj֮��ı�ȨΪw[
i,j]�����㷨ִ�й����е���һʱ�̣�������һ����(i,j)��A[i]+B[j]>=w[i,j]ʼ�ճ���
��KM�㷨����ȷ�Ի���
���¶���
�������ɶ���ͼ����������A[i]+B[j]=w[i,j]�ı�(i,j)���ɵ���ͼ�����������ͼ������
��ƥ�䣬��ô����걸ƥ����Ƕ���ͼ�����Ȩƥ�䡣
���������������Ȼ�ġ���Ϊ���ڶ���ͼ������һ��ƥ�䣬����������������ͼ����ô
���ı�Ȩ�͵������ж���Ķ���ͣ�������еı߲������������ͼ����ô���ı�Ȩ��С
�����ж���Ķ���͡����������ͼ���걸ƥ��һ���Ƕ���ͼ�����Ȩƥ�䡣
������ʼʱΪ��ʹA[i]+B[j]>=w[i,j]���������A[i]Ϊ�����붥��Xi�����ıߵ����Ȩ��
B[j]=0�������ǰ�������ͼû���걸ƥ�䣬�Ͱ�����ķ����޸Ķ�����ʹ���������ͼ
��ֱ�������ͼ�����걸ƥ��Ϊֹ��
����������ǰ�����ͼ���걸ƥ��ʧ���ˣ�����Ϊ����ĳ��X���㣬�����Ҳ���һ������
�����Ľ���·����ʱ���ǻ����һ�ý�����������Ҷ�ӽ��ȫ����X���㡣�������ǰѽ���
����X����Ķ���ȫ����Сĳ��ֵd��Y����Ķ���ȫ������ͬһ��ֵd����ô���ǻᷢ�֣�

���˶��ڽ������еı�(i,j)��A[i]+B[j]��ֵû�б仯��Ҳ����˵����ԭ�����������ͼ
�����������������ͼ��
���˶����ڽ������еı�(i,j)��A[i]��B[j]��û�б仯��Ҳ����˵����ԭ�����ڣ�����
�ڣ������ͼ�����������ڣ������ڣ������ͼ��
X�˲��ڽ������У�Y���ڽ������еı�(i,j)������A[i]+B[j]��ֵ����������ԭ������
�������ͼ�������Բ����������ͼ��
X���ڽ������У�Y�˲��ڽ������еı�(i,j)������A[i]+B[j]��ֵ������С��Ҳ��˵����
ԭ�������������ͼ�����ڿ��ܽ����������ͼ�����ʹ�����ͼ�õ�������
�������ڵ����������dֵ�ˡ�Ϊ��ʹA[i]+B[j]>=w[i,j]ʼ�ճ�������������һ���߽���
�����ͼ��dӦ�õ���min{A[i]+B[j]-w[i,j]|Xi�ڽ������У�Yi���ڽ�������}��
�������Ͼ���KM�㷨�Ļ���˼·���������ص�ʵ�ַ�����ʱ�临�Ӷ�ΪO(n4)������Ҫ��O
(n)������·��ÿ�����������Ҫ�޸�O(n)�ζ��꣬ÿ���޸Ķ���ʱ����Ҫö�ٱ�����dֵ
�����Ӷ�ΪO(n2)��ʵ����KM�㷨�ĸ��Ӷ��ǿ�������O(n3)�ġ����Ǹ�ÿ��Y����һ������
����������slack��ÿ�ο�ʼ������·ʱ��ʼ��Ϊ�������Ѱ������·�Ĺ����У�����
(i,j)ʱ����������������ͼ�У�����slack[j]���ԭֵ��A[i]+B[j]-w[i,j]�Ľ�Сֵ��
���������޸Ķ���ʱ��ȡ���в��ڽ������е�Y�����slackֵ�е���Сֵ��Ϊdֵ���ɡ�
����Ҫע��һ�㣺�޸Ķ����Ҫ�����е�slackֵ����ȥd��

*/

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
}


//��O(N^3)���㷨����:

#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int N = 128;
const int INF = 1 << 28;

class Graph {
private:
   bool xckd[N], yckd[N];
   int n, edge[N][N], xmate[N], ymate[N];
   int lx[N], ly[N], slack[N], prev[N];
   queue<int> Q;
   bool bfs();
   void agument(int);
public:
   bool make();
   int KMMatch();
};
bool Graph::make() {
   int house[N], child[N], h, w, cn = 0;
   char line[N];
   scanf("%d %d", &h, &w);
   if(w == 0) return false;
   scanf("\n"); n = 0;
   for(int i = 0; i < h; i++) {
      gets(line);
      for(int j = 0; line[j] != 0; j++) {
         if(line[j] == 'H') house[n++] = i * N + j;
         if(line[j] == 'm') child[cn++] = i * N + j;
      }
   }
   for(int i = 0; i < n; i++) {
      int cr = child[i] / N, cc = child[i] % N;
      for(int j = 0; j < n; j++) {
         int hr = house[j] / N, hc = house[j] % N;
         edge[i][j] = -abs(cr-hr) - abs(cc-hc);
      }
   }
   return true;
}
bool Graph::bfs() {
   while(!Q.empty()) {
      int p = Q.front(), u = p>>1; Q.pop();
      if(p&1) {
         if(ymate[u] == -1) { agument(u); return true; }
         else { xckd[ymate[u]] = true; Q.push(ymate[u]<<1); }
      } else {
         for(int i = 0; i < n; i++)
            if(yckd[i]) continue;
            else if(lx[u]+ly[i] != edge[u][i]) {
               int ex = lx[u]+ly[i]-edge[u][i];
               if(slack[i] > ex) { slack[i] = ex; prev[i] = u; }
            } else {
               yckd[i] = true; prev[i] = u;
               Q.push((i<<1)|1);
            }
      }
   }
   return false;
}
void Graph::agument(int u) {
   while(u != -1) {
      int pv = xmate[prev[u]];
      ymate[u] = prev[u]; xmate[prev[u]] = u;
      u = pv;
   }
}
int Graph::KMMatch() {
   memset(ly, 0, sizeof(ly));
   for(int i = 0; i < n; i++) {
      lx[i] = -INF;
      for(int j = 0; j < n; j++) lx[i] >?= edge[i][j];
   }
   memset(xmate, -1, sizeof(xmate)); memset(ymate, -1, sizeof(ymate));
   bool agu = true;
   for(int mn = 0; mn < n; mn++) {
      if(agu) {
         memset(xckd, false, sizeof(xckd));
         memset(yckd, false, sizeof(yckd));
         for(int i = 0; i < n; i++) slack[i] = INF;
         while(!Q.empty()) Q.pop();
         xckd[mn] = true; Q.push(mn<<1);
      }
      if(bfs()) { agu = true; continue; }
      int ex = INF; mn--; agu = false;
      for(int i = 0; i < n; i++)
         if(!yckd[i]) ex <?= slack[i];
      for(int i = 0; i < n; i++) {
         if(xckd[i]) lx[i] -= ex;
         if(yckd[i]) ly[i] += ex;
         slack[i] -= ex;
      }
      for(int i = 0; i < n; i++)
         if(!yckd[i] && slack[i] == 0) { yckd[i] = true; Q.push((i<<1)|1); }

   }
   int cost = 0;
   for(int i = 0; i < n; i++) cost += edge[i][xmate[i]];
   return cost;
}

int main()
{
   Graph g;
   while(g.make()) printf("%d\n", -g.KMMatch());
   return 0;
}