/* 
 * 2046 Gap
 * fengyu Accepted	10648K	907MS	C++
 * BFS + hash(×´Ì¬)close±í
 */
#include<iostream>
#include<algorithm>
#include<deque>
using namespace std;
#define N 10472911
int Hash(char const str[]) 
{
    int b = 378551,a = 63689,hash = 0;
    for(int i=0;str[i];i++){
		hash = hash * a + str[i];
		a *= b;
	}
	return (hash & 0x7FFFFFFF)%N;
}
struct State{
	char p[33];
	operator int() const{ return Hash(p);}
};
bool operator==(State& a,State &b){
	for(int i=0;i<32;i++){
		if(a.p[i]!=b.p[i]) return false;
	}
	return true;
}
char close[N];
State T;
int BFS(char p[]){
	deque<State> open;
	State S;
	memcpy(S.p,p,33);
	if(S==T) return 0;
	open.push_back(S);
	memset(close,-1,sizeof(close));
	close[S]=0;
	while(open.size()){
		State cur=open.front(),next;
		open.pop_front();
		if(cur==T) return close[cur];		
		for(int i=0;i<32;i++){
			if(cur.p[i]==-1){
				int t=cur.p[i-1];
				for(int j=0;j<32;j++){
					if(cur.p[j]==t+1){
						memcpy(next.p,cur.p,33);
						swap(next.p[i],next.p[j]);
						if(close[next]==-1){
							close[next]=close[cur]+1;	
							open.push_back(next);
						}
						break;
					}
				}
			}
		}		
	}
	return -1;
}

int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int cas;
	scanf("%d",&cas);
	char p[33];
	for(int i=0;i<4;i++){
		T.p[i*8+7]=-1;
		for(int j=0;j<7;j++){
			int pos=i*8+j;
			T.p[pos]=(i+1)*10+j+1;
		}
	}
	T.p[32]=0;		p[32]=0;
	while(cas--){
		int i,j;
		for(i=0;i<4;i++){
			p[i*8]=-1;
			for(j=1;j<=7;j++){
				int pos=i*8+j;
				int tmp;
				scanf("%d",&tmp);
				p[pos]=tmp;
			}
		}
		for(i=0;i<32;i++){
			if(p[i]==11) swap(p[0],p[i]);
			else if(p[i]==21) swap(p[8],p[i]);
			else if(p[i]==31) swap(p[16],p[i]);
			else if(p[i]==41) swap(p[24],p[i]);
		}
		/*// random test %37
		int ii=N,cnt=0;
		memset(close,0,sizeof(close));
		do{
			random_shuffle(p,p+32);
			int tmp=Hash(p);
			if(close[tmp]==0){
				close[tmp]=1;
			}else cnt++;
		}while(ii-->0);
		printf("%.2lf\n",(double)cnt/N);
		//*/
		int re=BFS(p);
		printf("%d\n",re);
	}
	return 0;
}
