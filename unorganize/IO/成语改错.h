#include<iostream>

#define N 65536
#define M 33000
int p[N-M]={0};

char dic[20000][10];
int cmp(char str[],int x){
	int i=0,dif=0,pos=-1;
	while(str[i]!=0){
		if(str[i] < 0) {
			if(str[i]==dic[x][i]&&str[i+1]==dic[x][i+1]){
				
			}else{
				dif++;
				pos=i;
				if(dif>1) return -1;
			}
			i++;
		}
		i++;
	}
	return pos;
}
int main()
{
	//freopen("t.in", "r", stdin);
	int n,m,i;char str[256];
	scanf("%d%d",&n,&m);
	for(i=0;i<n;i++){
		scanf("%s",str);
		char *ptr=str;
		while((*ptr)!=0){
			if((*ptr) < 0) {
				unsigned short re=*((short*)ptr);
				p[re-M]=i+1;
				ptr++;
			}
			ptr++;
		}
	}
	int cnt=0;
	for( i=0;i<m;i++){
		scanf("%s",dic[cnt]);
		char *ptr=dic[cnt];
		bool hasword=false;
		while((*ptr)!=0){
			if((*ptr) < 0) {
				unsigned short re=*((short*)ptr);
				if(p[re-M]>0){
					hasword=true;
					break;
				}
				ptr++;
			}
			ptr++;
		}
		if(hasword) cnt++;
	}
	char tar[10];
	scanf("%s",tar);
	for(i=0;i<cnt;i++){
		int re=cmp(tar,i);
		if(re>=0){
			unsigned short k1=*((short*)(tar+re));
			unsigned short k2=*((short*)(dic[i]+re));
			if(p[k1-M]>0&&p[k2-M]>0){
				printf("%s\n",dic[i]);
				return 0;
			}
		}
	}
	return 0;
}