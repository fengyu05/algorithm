/* 1716 Integer Intervals
 * ²î·ÖÔ¼Êø
 */
#include <iostream>
#include<algorithm>
using namespace std;

pair<int,int> s[10010]; 

int main(){
	 int i,j,n,m; 
	 scanf("%d",&n);
		 int result[10010]={0};
		 int t;
		 memset(s,0,sizeof(s));
		 for(i=0;i<n;i++)
			 scanf("%d%d",&s[i].first,&s[i].second);
		 sort(s,s+n);
		 for(i=0;i<=n-1;i++) {
			 for(j=i+1;j<=n-1;j++) 
				 if(s[j].second<s[i].second) {
					 s[i].first=-1;s[i].second=-1;
					 break;
				 }
		 }
		 i=-1;j=-1;t=0;
		 for(m=0;m<=n-1;m++) {
			 //printf("i=%d j=%d\n",i,j); 
			 //printf("x=%d y=%d\n",s[m].first,s[m].second);
			 if(s[m].first==-1) continue;
			 if(i<s[m].first&&j<s[m].first) {
				 i=s[m].second-1;
				 j=s[m].second;
				 result[t++]=i;
				 result[t++]=j;
			 } 
			 if(i<s[m].first&&j<=s[m].second) {
				 i=j;
				 j=s[m].second;
				 result[t++]=j;
			} 
		 }
		 // for(i=0;i<=t-1;i++) 
		 // printf("%d ",result[i]); 
		 // printf("\n"); 
		 printf("%d\n",t);

	 return 0;
}