/* 1190 …˙»’µ∞∏‚
 * DFS+ºÙ÷¶
*/
#include <iostream>
using namespace std;
int cmp(const void *a,const void *b){return *(int*)b - *(int*)a;}
int cas;
int st[70],used[70],maxlen,totlen;
int len;
int search(int t,int rest,int pos)
{
	int flag=0;
	if(rest==len) flag=1;
	if(t==totlen/len) return 1;
	for(int i=pos;i<cas;i++)
	{
		if(!used[i])
		{
			if(rest==st[i])
			{
				used[i]=1;
				if(search(t+1,len,0)) return 1;
				used[i]=0;
				return 0;
			}else if(rest>st[i])
			{
				used[i]=1;
				if(search(t,rest-st[i],i+1)) return 1;
				used[i]=0;
				if(flag) return 0;
				while(st[i]==st[i+1]) i++;
			}
			else if(flag) return 0;
		}
		
	}
	return 0;
}
int main()
{
#ifndef ONLINE_JUDGE
  	freopen("D:\\acm\\t.in", "r", stdin);
#endif

	while(scanf("%d",&cas),cas){
		maxlen=totlen=0;
		for(int i=0;i<cas;i++){
			scanf("%d",&st[i]);
			totlen+=st[i];
			if(maxlen<st[i]) maxlen=st[i];
		}
		qsort(st,cas,sizeof(st[0]),cmp);
		for(i=maxlen;i<=totlen;i++){
			if(i==totlen) break;
			if(totlen%i==0)
			{
				memset(used,0,sizeof(used));
				len=i;
				if(search(1,len,0)) break;
			}
		}
		printf("%d\n",i);
	}
}