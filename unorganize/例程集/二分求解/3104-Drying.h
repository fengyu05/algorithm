/* 3104 Drying
	648K	422MS	C++	1184B
	fengyu05
  问题:给出n件湿衣服,含水量为p[i],自然干每分钟水分减1.
       有一台干衣机,只能干一件,每分钟减k
	   问干衣最少时间.
  解法:二分枚举,判断可行
       枚举时间mid,每件衣服减去自然干的水分mid后
	   统计仍需多少分钟衣. (干衣一次为k,因为其中的1计算在mid里面)
*/
#include <iostream>
using namespace std;

int p[100000];
int n,k;
int attempt(int l, int r)
{
    int i, b;
    if (l < r){
          int cnt = 0;
          int mid = (l + r) / 2;
          for (i = 0; i < n; i ++)
          {
              int tmp = p[i]-mid;
              if (tmp > 0)
              {
                  cnt += tmp / (k - 1);//(**) not k
                  if ((tmp % (k - 1)) != 0) cnt++;
                  if (cnt > mid) break;
              }
          }
          if (i >= n)
			  b = attempt (l, mid);
          else
              b = attempt (mid + 1, r);
          return b;
    }else
		return r;
}
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	scanf("%d",&n);
	int max=0;
	for(int i=0;i<n;i++){
		scanf("%d",&p[i]);
		if(p[i]>max) max=p[i];
	}
	scanf("%d",&k);
	int re;
	if(k==1){
		re=max;
	}else
		re=attempt(1,max);
	printf("%d\n",re);
	return 0;
}