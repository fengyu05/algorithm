/* 1011 sticks
 * DFS+��֦
*/
#include <iostream>
#include <algorithm>
using namespace std;

#define N 70

int maxlen,totlen,len;
int p[N],n;
bool used[N];
bool cmp(int x,int y){ return x>y;}
bool search(int t,int res,int pos){
	if(t==totlen/len) return 1;//ȫ������������
	bool first=(res==len);//�Ƿ�Ϊ��һ�����
	for(int i=pos;i<n;i++){
		if(!used[i]){
			if(res==p[i]){//�պ�����
				used[i]=1;
				if(search(t+1,len,0)) return 1;
				used[i]=0;
				return 0;
			}else if(res>p[i]){
				used[i]=1;
				if(search(t,res-p[i],i+1)) return 1;
				used[i]=0;
				if(first) return 0;
				//��i��������һ����������ʧ�ܣ��Ͳ��������ĳ�������������
				while(p[i]==p[i+1]) i++;//������ͬ����
			}
		}
	}
	return 0;
}
int main()
{
	while(scanf("%d",&n),n){
		maxlen=totlen=0;
		int i;
		for(i=0;i<n;i++){
			scanf("%d",&p[i]);
			totlen+=p[i];
			if(maxlen<p[i]) maxlen=p[i];
		}
		sort(p,p+n,cmp);// >
		for(i=maxlen;i<totlen;i++){//[maxlen..totlen)
			if(totlen%i==0)// can divide
			{
				memset(used,0,sizeof(used));
				len=i;
				if(search(1,len,0)) break;
			}
		}
		printf("%d\n",i);
	}
	return 0;
}