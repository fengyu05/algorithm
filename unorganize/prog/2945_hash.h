/* 2945 Find the Clones
 * hash
 * feng */
#include <iostream>
#include <algorithm>
using namespace std;

char asc[85];

__int64 hash(char key[],int l)
{
	__int64 re=0;
	for(int i=0;i<l;i++){
		re=re*4+asc[key[i]];
	}
	return re;
}	
int main()
{
#ifndef ONLINE_JUDGE
  	freopen("D:\\acm\\acm\\input.txt", "r", stdin);
//freopen("D:\\acm\\acm\\output.txt", "w", stdout);
#endif
	int p,l;char str[25];

	 int a[20001];__int64 v[20000];
	 	 asc['A']=0;asc['C']=1;asc['G']=2;asc['T']=3; 
	while(scanf("%d %d\n",&p,&l)&&p){
		memset(a,0,sizeof(a));
		for(int i=0;i<p;i++){
			gets(str);
			v[i]=hash(str,l);			
		}
		sort(v,v+p);
		__int64 val=v[0];
		int count=1;
		for(i=1;i<=p;i++){
			if(i==p){ a[count]++;break;}
			if(val!=v[i]){
				a[count]++;
				val=v[i];
				count=1;
			}else
				count++;
		}
		//for(i=0;i<p;i++)	printf("%I64d ",v[i]);
		for(i=1;i<=p;i++){
			printf("%d\n",a[i]);
		}

	}
   	return 0;
}

