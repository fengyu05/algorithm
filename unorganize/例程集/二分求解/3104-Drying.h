/* 3104 Drying
	648K	422MS	C++	1184B
	fengyu05
  ����:����n��ʪ�·�,��ˮ��Ϊp[i],��Ȼ��ÿ����ˮ�ּ�1.
       ��һ̨���»�,ֻ�ܸ�һ��,ÿ���Ӽ�k
	   �ʸ�������ʱ��.
  �ⷨ:����ö��,�жϿ���
       ö��ʱ��mid,ÿ���·���ȥ��Ȼ�ɵ�ˮ��mid��
	   ͳ��������ٷ�����. (����һ��Ϊk,��Ϊ���е�1������mid����)
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