#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
struct Arr{
    int num,lo;
    bool friend operator <(Arr a,Arr b)
    {
         return a.num<b.num;
    }
}s[100001];
int main()
{
    //freopen("t.in","r",stdin);
    int i,j,k,l,n,m,first,last;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(i=0;i<n;i++){
            scanf("%d",&s[i].num);
            s[i].lo=i+1;
        }
        sort(s,s+n);
        for(i=0;i<m;i++){
            scanf("%d%d%d",&first,&last,&k);
            for(j=0,l=0;j<n;j++){
                if(s[j].lo>=first && s[j].lo<=last)l++;
                if(l==k) break;
            }
            printf("%d\n",s[j].num);
        }
    }
}
