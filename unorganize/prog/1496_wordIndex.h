#include <iostream>

using namespace std;
#define N 32
int c[N][N];
int index[N];
bool valid(char str[]){
	for(int i=1;str[i];i++){
		if(str[i]<=str[i-1]) return false;
	}
	return true;
}
void main()
{
	int i,j,k;
	for(i=1;i<=26;i++){
		c[i][0]=1;
		c[i][i]=1;
		for(j=1;j<i;j++)
			c[i][j]=c[i-1][j]+c[i-1][j-1];
	}
	for(i=1;i<=26;i++){
		index[i]=1;
		for(j=1;j<i;j++) index[i]+=c[26][j];
	}
	char str[16];
	while(gets(str)){
		if(!valid(str)){
			printf("0\n");
			continue;
		}
		int re=0;
		int len=strlen(str);
		re+=index[len];
		char last='a';
		int use=26;
		for(i=len-1;i>=0;i--){
			int dif=str[len-1-i]-last;
			if(i==0){ re+=dif;break;}
			last=str[len-1-i]+1;
			for(int j=1;j<=dif;j++)
				re+=c[use-j][i];
			use-=dif+1;
		}
		printf("%d\n",re);
	}
}
