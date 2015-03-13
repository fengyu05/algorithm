//----------------稳定婚姻问题----------------------
//----------------Stable Marriage Problem-----------
#include <iostream>
using namespace std;
#include "ds/ds_array.h" //include Queue
#define N 32
#define _clr(ar) memset(ar,0,sizeof(ar))
int n;
int BrG[N][N];// boy对girl的评分
int GrB[N][N];// girl对boy的评分
int Bget[N],Gget[N];// boy,girl最后的搭配对象
int list[N][N],cur[N];// boy对girl选择的排名
void propose_and_reject(){
	int i,j;
	_clr(Bget),_clr(Gget);
	Queue<int,N> que;
	que.init();
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			list[i][BrG[i][j]]=j;
		}
		cur[i]=1;
		que.push(i);
	}
	while(que.size()){
		int boy=que.pop();
		int girl=list[boy][cur[boy]++];
		int prev_boy=Gget[girl];
		if(prev_boy==0){
			Bget[boy]=girl,Gget[girl]=boy;//engaged			
		}else if(GrB[girl][boy]<GrB[girl][prev_boy]){
			// girl perfer boy to prev_boy
			Bget[boy]=girl,Gget[girl]=boy;//engaged
			que.push(prev_boy);
		}else que.push(boy);
	}
}
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	scanf("%d",&n);
	int i,j;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			scanf("%d",&BrG[i][j]);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			scanf("%d",&GrB[i][j]);
	propose_and_reject();
	for(i=1;i<=n;i++){
		printf("Boy[ %d - %d ]Girl\n",i,Bget[i]);
	}
	return 0;
}