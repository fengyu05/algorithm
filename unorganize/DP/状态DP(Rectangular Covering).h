/*Rectangular Covering*/
#include<iostream>

using namespace std;
#define N 32768
#define INF 0x3fffffff
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
int countbit(int x){
	int re=0;
	while(x>0){
		re+=x%2;
		x/=2;
	}return re;
}
int list[16][6500],cnt[16];//×´Ì¬·Ö½×ÁÐ±í
int f[N],n;
int x[16],y[16];
int area(int i,int j){
	int dx=abs(x[i]-x[j]);
	if(dx==0) dx=1;
	int dy=abs(y[i]-y[j]);
	if(dy==0) dy=1;
	return dx*dy;
}
bool inarea(int x1,int x2,int y1,int y2,int p){
	if(x[p]>=x1&&x[p]<=x2&&y[p]>=y1&&y[p]<=y2)
		return true;
	else return false;
}
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	while(scanf("%d",&n),n){
		int end=(1<<n),i;
		memset(cnt,0,sizeof(cnt));
		for(i=0;i<end;i++){
			int bb=countbit(i);
			list[bb][cnt[bb]++]=i;
		}
		for(i=0;i<n;i++){
			scanf("%d%d",&x[i],&y[i]);
		}
		memset(f,-1,sizeof(f));
		f[0]=0;
		for(int ii=0;ii<n;ii++){
			for(i=0;i<cnt[ii];i++){
				int j=list[ii][i];
				if(f[j]!=-1){
					for(int k=0;k<n;k++){
						int tar=(1<<k)&j;
						if(tar==0){							
							int a=INF,dex=-1,nw,p;
							for(p=0;p<n;p++){
								if(p==k) continue;
								int tmp=area(k,p);
								if(a>tmp){
									a=tmp;
									dex=p;
								}
							}
							int val=f[j]+a;
							int x1=min(x[k],x[dex]),x2=max(x[k],x[dex]);
							int y1=min(y[k],y[dex]),y2=max(y[k],y[dex]);
							if(x1==x2){
								nw=j;
								for(p=0;p<n;p++){
									if(inarea(x1,x2+1,y1,y2,p))
										nw=nw|(1<<p);
								}
								if(f[nw]==-1||f[nw]>val) f[nw]=val;
								nw=j;
								for(p=0;p<n;p++){
									if(inarea(x1-1,x2,y1,y2,p))
										nw=nw|(1<<p);
								}
								if(f[nw]==-1||f[nw]>val) f[nw]=val;
							}else if(y1==y2){
								nw=j;
								for(p=0;p<n;p++){
									if(inarea(x1,x2,y1,y2+1,p))
										nw=nw|(1<<p);
								}
								if(f[nw]==-1||f[nw]>val) f[nw]=val;
								nw=j;
								for(p=0;p<n;p++){
									if(inarea(x1,x2,y1-1,y2,p))
										nw=nw|(1<<p);
								}
								if(f[nw]==-1||f[nw]>val) f[nw]=val;				
							}else{
								nw=j;
								for(p=0;p<n;p++){
									if(inarea(x1,x2,y1,y2,p))
										nw=nw|(1<<p);
								}
								if(f[nw]==-1||f[nw]>val) f[nw]=val;
							}
						}
					}
				}
			}	
		}
		printf("%d\n",f[end-1]);
	}
	return 0;
}