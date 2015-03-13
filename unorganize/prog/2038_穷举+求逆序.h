// poj 2038 Team Rankings
// Çî¾Ù+ÇóÄæĞòÊı

#include <stdio.h>
#include<algorithm>
int a[100][6];

bool cmp(int i,int j,int b[]){ return b[i]<b[j];}
bool cmpalpha(int *x,int *y)
{
	int i,j;
	for(i=1;i<=5;i++) if(x[i]==1) break;
	for(j=1;j<=5;j++) if(y[j]==1) break;
	return i<j;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int n,i,j,p,q,sum=0,b[6],max,rez[6];
	char s[5];
	while(scanf("%d",&n),n){
		max=100000000;
		for (i=0;i<n;i++) {
			scanf("%s",s);
			a[i][1]=s[0]-'A'+1;
			a[i][2]=s[1]-'A'+1;
			a[i][3]=s[2]-'A'+1;
			a[i][4]=s[3]-'A'+1;
			a[i][5]=s[4]-'A'+1;
		}
		for (i=1;i<=5;i++) b[i]=i;
		//b[1]=4;
		//b[2]=5;
		//b[3]=1;
		//b[4]=2;
		//b[5]=3;
		do{
			sum=0;
			for(i=0;i<n;i++)
			{
				int tmp=0;
				for (p=1;p<=4;p++){
					for (q=p+1;q<=5;q++) {
						if(cmp(a[i][q],a[i][p],b)) tmp++;
					}
				}
				sum+=tmp;
			}
			if (sum<max) { 
				max=sum;
				for (q=1;q<=5;q++) rez[q]=b[q];
			}
			if(sum==max&&cmpalpha(b,rez)){
				for (q=1;q<=5;q++) rez[q]=b[q];
			}
		}while(std::next_permutation(b+1,b+6));
		for (j=1;j<=5;j++) {	
			for (i=1;i<=5;i++)
				if (rez[i]==j) {
					printf("%c",i+'A'-1);
					break;
				}
		}
		printf(" is the median ranking with value %d.\n",max);
	}
	return 0;
}