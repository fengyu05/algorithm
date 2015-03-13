/*
1691 Painting A Board
fengyu05
状态DP:二进制编码+预处理:状态分阶列表
*/
#include<iostream>

using namespace std;
#define N 32768
int countbit(int x){
	int re=0;
	while(x>0){
		re+=x%2;
		x/=2;
	}return re;
}
int list[16][6500],cnt[16];//状态分阶列表
int f[22][N],n;
struct board{
	int x1,x2,y1,y2,c;
} p[16];
bool color[22];
bool on(int x,int y){// x on y
	if(x==y) return 0;
	if(p[x].y2>p[y].y1) return false;
	if(p[x].x2<=p[y].x1||p[x].x1>=p[y].x2) return false;
	return true;
}
bool onto[16][16];
bool has_paint(int k,int id){
	char x[16]={0};
	int j;
	for(j=0;j<n&&id>0;j++){
		x[j]=id%2;
		id/=2;
	}
	x[k]=1;
	for(j=0;j<n;j++) if(x[j]==0){
		if(onto[j][k]) return false; //j on k
	}
	return true;
}
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int cas;
	scanf("%d",&cas);
	while(cas--){
		scanf("%d",&n);
		int end=(1<<n),i;
		memset(cnt,0,sizeof(cnt));
		for(i=1;i<end;i++){
			int bb=countbit(i);
			list[bb][cnt[bb]++]=i;
		}
		memset(color,0,sizeof(color));
		int max_color=0;
		for(i=0;i<n;i++){
			scanf("%d%d%d%d%d",&p[i].y1,&p[i].x1,
				&p[i].y2,&p[i].x2,&p[i].c);
			color[p[i].c]=1;
			if(p[i].c>max_color) max_color=p[i].c;
		}
		for(i=0;i<n;i++){
			for(int j=0;j<n;j++){
				onto[i][j]=on(i,j);
			}
		}
		memset(f,-1,sizeof(f));
		for(i=0;i<n;i++){
			int c=p[i].c;
			int id=(1<<i);
			if(has_paint(i,0)){
				f[c][id]=1;
			}
		}
		for(int ii=1;ii<n;ii++){
			for(int c=1;c<=max_color;c++) if(color[c]){
				for(i=0;i<cnt[ii];i++){
					int j=list[ii][i];
					if(f[c][j]!=-1){
						for(int k=0;k<n;k++){
							int id=1<<k;
							int tar=id&j;
							if(tar==0&&has_paint(k,j)){
								int nw=id|j;
								int nc=p[k].c;
								int val=f[c][j]+(nc==c?0:1);
								if(f[nc][nw]==-1||f[nc][nw]>val)
									f[nc][nw]=val;
							}
						}
					}
				}
			}							
		}
		int _min=-1;
		for(i=1;i<=max_color;i++) if(color[i]){
			int tmp=f[i][end-1];
			if(tmp==-1) continue;
			if(_min==-1||tmp<_min) _min=tmp;
		}
		printf("%d\n",_min);
	}
	return 0;
}