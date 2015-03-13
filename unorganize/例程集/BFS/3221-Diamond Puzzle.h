/* 3221-Diamond Puzzle
 * 39364K	15MS	C++	1325B
 * fengyu05
 题目:求Diamond Puzzle每个状态到目标状态的最少步数
 方法:预处理反向BFS,记录答案
  */
#include <iostream>
#include <deque>
using namespace std;

int tab[10000000];
int ar_to_int(int p[]){
	int re=p[0];
	for(int i=1;i<=6;i++){
		re=(re*10)+p[i];
	}
	return re;
}
void int_to_ar(int code,int p[]){
	int pos=6;
	p[0]=0;
	while(pos>=0){
		p[pos--]=code%10;
		code/=10;
	}
}
int Opos(int p[]){
	for(int i=0;i<=6;i++) if(p[i]==0) return i;
	return -1;
}
int ex[8][8];
void BFS(int t){
	deque<int> que;
	que.push_back(t);
	while(que.size()){
		int tmp=que.front();
		que.pop_front();
		int p[8];
		int_to_ar(tmp,p);
		int pos=Opos(p);
		for(int k=0;ex[pos][k]!=-1;k++){
			int pos2=ex[pos][k];
			swap(p[pos],p[pos2]);
			int nw=ar_to_int(p);
			if(tab[nw]==-1){
				tab[nw]=tab[tmp]+1;
				que.push_back(nw);
			}
			swap(p[pos],p[pos2]);
		}
	}
}
int main()
{	
	memset(tab,0xff,sizeof(tab));
	memset(ex,0xff,sizeof(ex));
	ex[0][0]=2;	ex[0][1]=4;	ex[0][2]=6;
	ex[1][0]=6; ex[1][1]=2; 
	ex[2][0]=0; ex[2][1]=1; ex[2][2]=3;
	ex[3][0]=2; ex[3][1]=4; 
	ex[4][0]=0; ex[4][1]=3; ex[4][2]=5;
	ex[5][0]=4; ex[5][1]=6; 
	ex[6][0]=0; ex[6][1]=5; ex[6][2]=1;
	tab[123456]=0;
	BFS(123456);
	int n;
	scanf("%d",&n);
	while(n--){
		int x;
		scanf("%d",&x);
		printf("%d\n",tab[x]);
	}//*/
	return 0;
}