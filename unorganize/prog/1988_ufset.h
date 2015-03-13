/* 1988 Cube Stacking */

#include <iostream>
using namespace std;
const int N=30000;
int m,a[N],c[N],d[N];
int findways(int v)
{
	int i,ch,r;
	i=v; r=0;
	while (a[i]!=i) {r+=d[i]; i=a[i];}
	while (i!=v)
	{
		ch=r-d[v]; d[v]=r; r=ch;
		ch=a[v]; a[v]=i; v=ch;
	}
	return v;
}
int main()
{
	int l,i,j;
	char *s=new char[10];
	scanf("%d",&m);
	for (l=0;l<N;l++) {a[l]=l; c[l]=1;}
	for (l=0;l<m;l++)
	{
		scanf("%s",s);
		if (*s=='M')
		{
			scanf("%d%d",&i,&j);
			i--; j--;
			i=findways(i); j=findways(j);
			d[i]=c[j];
			a[i]=j; c[j]+=c[i];
		}
		else
		{
			scanf("%d",&i);
			i--;
			findways(i);
			printf("%d\n",d[i]);
		}
	}
	return 0;
}