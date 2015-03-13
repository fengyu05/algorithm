/* 1270 
 Following Orders
 已知偏序集合，求所有相容的全序集，按字典序输出
 回溯，有序排列树
*/
#include <iostream>
#include <algorithm>
using namespace std;

#define N 32
char ord[N];
char dic[128];
char mat[N][N];
int n;
int x[N];
bool good(int i){
	for(int j=0;j<i;j++){
		if(mat[x[i]][x[j]]==1) return false;
	}return true;
}
void search(int i){
	if(i==n){
		for(int j=0;j<n;j++){
			printf("%c",ord[x[j]]);
		}
		printf("\n");
		return;
	}else{
		int x2[N];
		memcpy(x2,x,sizeof(x));
		sort(x+i,x+n);
		for(int j=i;j<n;j++){
			swap(x[i],x[j]);
			if(good(i)) search(i+1);
			swap(x[i],x[j]);
		}
		memcpy(x,x2,sizeof(x));
	}
}
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	char ch;int i;int cas=0;
	while(scanf("%c",&ch)!=EOF){
		if(cas++!=0) printf("\n");
		n=0;
		memset(dic,-1,sizeof(dic));
		memset(mat,0,sizeof(mat));
		if(ch>='a'&&ch<='z') ord[n++]=ch;
		while(scanf("%c",&ch),ch!='\n'){
			if(ch==' ') continue;
			ord[n++]=ch;
		}
		sort(ord,ord+n);
		for(i=0;i<n;i++){
			dic[ord[i]]=i;
		}
		char a=0;
		while(scanf("%c",&ch)!=EOF&&ch!='\n'){
			if(ch==' ') continue;
			if(a==0) a=ch;
			else{
				mat[dic[a]][dic[ch]]=1;
				a=0;
			}
		}
		for(i=0;i<n;i++) x[i]=i;
		search(0);
		//printf("\n");
	}
	return 0;
}