#include <iostream>
#include <algorithm>
using namespace std;
//Doubling Algorithm O(nlogn)
//SuffxSort : input str[0..n) , output sa[0..n)
#define nb next // "new bucket" overlaid on "next"
#define head height // head is never used when computing height

#define N 128
char str[N];//字符串
int sa[N]; //后续数组
int height[N] ;//||head
int rank[N] ;//名次数组 || bucket
int next[N];// ||new bucket
bool cmp(int i ,int j ){ return str[i]<str[j]; }
void SuffixSort(int n)
{
	int i,j,k,h;
	for(i=0; i<n; i++) sa[i]=i;
	sort(sa,sa+n,cmp);
	for(i=0; i<n; i++)
		if ( i==0 || str[ sa[ i ]]!= str[ sa[ i-1 ]] )
			rank[ sa[ i ]] = i ;
		else
			rank[ sa[ i ]]=rank[ sa[ i-1 ]];
	for(h=1; h<n; h<<=1)
	{
		for( i=0;i<n; i++) head[i]=next[i]=-1;
		for( i=n-1; i>=0; i--) if(sa[i])
		{
			j = sa[i]-h;
			if ( j<0 ) j+=n;
			next[j] = head[rank[j]];
			head[rank[j]] = j ;
		}
		j=n-h; next[ j ] = head[rank[ j ]]; head[rank[ j ]] = j ;
		for( i=k=0; i<n; i++) if ( head[ i]>=0 )
			for( j=head[ i ]; j >=0; j=next[ j ])
				sa[k++]=j ;
		for( i =0; i<n; i++)
			if ( i>0 && sa[ i]+h<n && sa[ i-1]+h<n
				&& rank[ sa[ i ]] == rank[ sa[ i -1]] 
				&& rank[ sa[i]+h] == rank[ sa[ i-1]+h] )
				nb[ sa[ i ]] = nb[ sa[ i -1]];
			else nb[ sa[ i ]] = i ;
		for( i =0; i<n; i++) rank[i]=nb[i];
	}
}
//GetHeight: hegiht[i]=LCP(str[sa[i]],str[sa[i]-1])
void GetHeight(int n){
	int i,j,h;
	height[0]=0;
	for(i=0;i<n;i++) rank[sa[i]]=i;
	for(h=0,i=0;i<n;i++) if(rank[i]>0){
		j=sa[rank[i]-1];
		while(str[i+h]==str[j+h]) ++h;
		height[rank[i]]=h;
		if(h>0) --h;
	}
}
// App
// 1. match
// affter Suffixsort
// P[0..m) match str[0..) O(mlogn)
int match(char P[],int m,int n){
	int cnt=0;//match count
	int l=0,r=n;
	while(l<r){
		int mid=(l+r)/2;
		char ch;
		while((ch=str[sa[mid]+cnt])==P[cnt]) cnt++;
		if(cnt>=m) return sa[mid];
		else if(P[cnt]<ch){
			r=mid;
		}else l=mid+1;
	}
	return -1;
}
// 2. RMQ on height

int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	scanf("%s",str);
	int n=strlen(str);
	SuffixSort(n);
	GetHeight(n);

	return 0;
}