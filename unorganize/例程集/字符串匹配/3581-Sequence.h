#include <iostream>
#include <algorithm>
using namespace std;
#define N 200000*2
#define nb next // "new bucket" overlaid on "next"
#define head height // head is never used when computing height
int str[N];//字符串
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
int main()
{	
	int n,i,pos;
	scanf("%d",&n);
	for(i=n-1;i>=0;i--){
		scanf("%d",&str[i]);
	}
	SuffixSort(n);
	i=0;
	do{
		pos=sa[i];
		i++;
	}while(pos<2);
	for(i=pos;i<n;i++){
		printf("%d\n",str[i]);
	}
	//--
	for(i=0;i<pos;i++)
		str[pos+i]=str[i];
	n=pos;	
	SuffixSort(n+pos);
	i=0;
	do{
		pos=sa[i];
		i++;
	}while(pos<1||pos>=n);
	for(i=pos;i<n;i++){
		printf("%d\n",str[i]);
	}
	//--
	n=pos;
	for(i=0;i<n;i++){
		printf("%d\n",str[i]);
	}
	return 0;
}