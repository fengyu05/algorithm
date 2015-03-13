/*
 1118 Lining Up
 ��������
 ��֪ƽ����һЩ�㣬�󾭹������һ��ֱ��
 ����ÿ�㣬�Ըõ㵽�������б������
*/
#include<iostream>
#include<algorithm>
using namespace std;

#define N 1000
#define INF 0x7fffffff
struct Point{
	int x,y;
}	d[N];

typedef double item;
int countmost(item a[],int n)
{// a[] must be sort
	int re=1,tmp=1;
	for(int i=1;i<n;i++){
		if(a[i]==a[i-1]){
			tmp++;
			if(tmp>re) re=tmp;
		}else{			
			tmp=1;
		}
	}
	return re;
}
int main()
{
	int i,j,l_cnt,n,max,cnt;
	double  line[N];
	int cas=0;
	while(scanf("%d",&n),n){
		cas++;
		for(i=0;i<n;i++)
			scanf("%d%d",&d[i].x,&d[i].y);
		max=1;
		for(i=0;i<n;i++)
		{
			l_cnt=0;
			for(j=0;j<n;j++){
				if(i==j) continue;
				if(d[i].x!=d[j].x)
					line[l_cnt++]=(double)(d[j].y-d[i].y)/(d[j].x-d[i].x);
				else line[l_cnt++]=INF;
			}
			sort(line,line+l_cnt);
			cnt=countmost(line,l_cnt);
			if(cnt>max) max=cnt;
		}
		printf("%d\n",max+1);
	}
}
