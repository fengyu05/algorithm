/*
 2752-Seek the Name, Seek the Fame
 fengyu05
 题目:给定字符串,求是它prefix-suffix的字串长度.(由小到大)
 解法:KMP的第一阶段,计算prefix函数.
      反向输出n,next[n],next[next[n]]...
 */
#include <iostream>
using namespace std;

#define P_LEN 400004
char P[P_LEN];//[0..m)
int next[P_LEN];//[1..m]
void compute_prefix_fun(int m){
	next[1]=0;
	int k=0;
	for(int q=1;q<m;q++){
		while(k>0&&P[k]!=P[q]){
			k=next[k];
		}
		if(P[k]==P[q]) k++;
		next[q+1]=k;		
	}
}
void pt(int t){
	if(t!=0){ pt(next[t]);
		printf("%d ",t);
	}
}
int main()
{	
	while(scanf("%s",P)==1){
		int len=strlen(P);
		compute_prefix_fun(len);
		pt(next[len]);
		printf("%d\n",len);
	}
	return 0;
}