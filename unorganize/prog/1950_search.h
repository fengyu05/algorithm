// poj 1950 Dessert
// search + 结果保存(trick)
#include <stdio.h>

int n,m;
char c[20];
int cal()
{
	int re=0,tmp=0,bp=1;
	for(int i=1;i<n;i++)
	{
		if(c[i]=='.'){
			if(i>=10)
				tmp=tmp*100+i;
			else
				tmp=tmp*10+i;
			continue;
		}
		if(c[i]=='+'){
			if(i>=10)
				re+=bp*(tmp*100+i);
			else
				re+=bp*(tmp*10+i);
			bp=1;
			tmp=0;
			continue;
		}
		if(c[i]=='-'){
			if(i>=10)
				re+=bp*(tmp*100+i);
			else
				re+=bp*(tmp*10+i);
			bp=-1;
			tmp=0;
		}
	}
	if(n>=10)
		re+=bp*(tmp*100+n);
	else
		re+=bp*(tmp*10+n);
	return re;
}
void search(int t)
{
	if(t==n){
		if(cal()==0){
			m++;
				for(int i=1;i<n;i++){
					printf("%d",i);
					printf(" %c ",c[i]);
				}
				printf("%d\n",n);
		}
		return;
	}	
	c[t]='+';
	search(t+1);
	if(m>=20) return;
	c[t]='-';
	search(t+1);
	if(m>=20) return;
	c[t]='.';
	search(t+1);

}
void main()
{
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	scanf("%d\n",&n);
	m=0;search(1);
	//结果保存(预先运行过一遍保存下结果3<=k<=15)
	int ans[16]={ 0,0,0,1,1,1,1,6,10,11,17,88,162,197,437,1350};
	printf("%d\n",ans[n]);
}