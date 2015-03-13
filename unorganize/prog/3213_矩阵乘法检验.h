// poj 3213 PM^3
// 预处理:判断哪行有错误
// 如果直接将矩阵相成将TLE
#include <iostream>
using namespace std;

#define N 1024

int A[N][N],B[N][N];
int C[N][N];
int sB[N],sC[N];
int n,p,m;

void input()
{
  int i,j;

  for (i=0;i<n;++i)
    for (j=0;j<p;++j)
      scanf("%d",&A[i][j]);
  
  for (i=0;i<p;++i)
    for (j=0;j<m;++j)
      scanf("%d",&B[i][j]);
  
  for (i=0;i<n;++i)
    for (j=0;j<m;++j)
      scanf("%d",&C[i][j]);
}

void precalc()
{
  int i,j;
  for (i=0;i<p;++i)
    for (j=0;j<m;++j) sB[i]+=B[i][j];
  for (i=0;i<n;++i)
    for (j=0;j<m;++j) sC[i]+=C[i][j];
}

void solve()
{
  int i,j,k;
  int s;

  for (i=0;i<n;++i) {
    s=0;
    for (j=0;j<p;++j)
      s+=A[i][j]*sB[j];
    if (s!=sC[i]) break;
  }

  if (i==n) {
    printf("Yes\n");
    return;
  }
  else printf("No\n");

  k=i;
  for (j=0;j<m;++j) {
    for (i=0,s=0;i<p;++i)
      s+=A[k][i]*B[i][j];
    if (s!=C[k][j]) break;
  }

  printf("%d %d\n%d\n",k+1,j+1,s);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
  scanf("%d %d %d",&n,&p,&m);
  input();
  precalc();
  solve();
  return 0;
}