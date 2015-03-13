/*  1129-Channel Allocation	
 * 212K	0MS	C++	994B
 * fengyu05
 * ��Ŀ:������ͼȾɫ,���ڵ���ɫ��ͬ,����С��ɫ��
 * ����:��С����ö��Ⱦɫ����������
*/
#include <iostream>
#include <sstream>
using namespace std;
#define N 32
int n,m;//��������ɫ��
bool mat[N][N];
int xx[N];//���н�
bool OK(int k){
	for(int j=0;j<n;j++)
		if(mat[k][j]==1&&xx[j]==xx[k])
			return false;
	return true;
}
//init ans=0,x[]={0} 
bool search(int t)
{
	if(t>n){
		return true;			
	}else
		for(int i=1;i<=m;i++){
			xx[t]=i;
			if(OK(t)) if(search(t+1))
				return true;
		}
	return false;
}


int main()
{
	int i,x,y;
	char str[128],ch;
	while(scanf("%d\n",&n),n){
		memset(mat,0,sizeof(mat));
		for(i=0;i<n;i++){
			scanf("%s",str);
			stringstream ss;
			ss.str(str);
			ss>>ch;
			x=ch-'A';
			ss>>ch;
			while(ss>>ch){
				y=ch-'A';
				mat[x][y]=mat[y][x]=1;
			}
		}
		memset(xx,0,sizeof(xx));
		for(m=1;m<10;m++){
			if(search(0))
				break;
		}
		if(m==1)
			printf("1 channel needed.\n");
		else
			printf("%d channels needed.\n",m);
	}
}