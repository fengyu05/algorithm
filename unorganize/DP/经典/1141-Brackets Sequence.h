/* 1141 Brackets Sequence
 * fengyu05
 */
#include <iostream>
using namespace std;

#define N 128
#define INF 0x7fffffff
char tk[N][N][300];// mind the last size
int d[N][N];
int main()
{	
	char str[N];
	while(gets(str+1)){
	str[0]=' ';
	int len=strlen(str),i;
	len--;
	for(i=1;i<=len;i++){
		d[i][i-1]=0;
		tk[i][i-1][0]=0;
		d[i][i]=1;
		char tmp=str[i];
		if(tmp=='('||tmp==')'){
			tk[i][i][0]='(';
			tk[i][i][1]=')';
			tk[i][i][2]=0;
		}
		if(tmp=='['||tmp==']'){
			tk[i][i][0]='[';
			tk[i][i][1]=']';
			tk[i][i][2]=0;
		}
	}
	for(int p=1;p<=len-1;p++){
		for(i=1;i<=len-p;i++){
			int j=i+p;
			d[i][j]=INF;
			int cho=0;
			if( (str[i]=='('&&str[j]==')') || (str[i]=='['&&str[j]==']') ){
				if(d[i+1][j-1]<d[i][j]){
					d[i][j]=d[i+1][j-1];
					cho=-1;
				}
			}
			if( str[i]=='(' || str[i]=='[' ){
				if(d[i+1][j]+1<d[i][j]){
					d[i][j]=d[i+1][j]+1;
					cho=-2;
				}
			}
			if( str[j]==')' || str[j]==']' ){
				if(d[i][j-1]+1<d[i][j]){
					d[i][j]=d[i][j-1]+1;
					cho=-3;
				}
			}
			for(int k=i;k<=j-1;k++){
				if(d[i][k]+d[k+1][j]<d[i][j]){
					d[i][j]=d[i][k]+d[k+1][j];
					cho=k;
				}
			}
			if(cho==-1){
				strcpy(tk[i][j]+1,tk[i+1][j-1]);
				int re=strlen(tk[i+1][j-1]);
				if(str[i]=='('){
					tk[i][j][0]='(';
					tk[i][j][re+1]=')';
					tk[i][j][re+2]=0;
				}else{
					tk[i][j][0]='[';
					tk[i][j][re+1]=']';
					tk[i][j][re+2]=0;
				}
			}
			if(cho==-2){
				strcpy(tk[i][j]+1,tk[i+1][j]);
				int re=strlen(tk[i+1][j]);
				if(str[i]=='('){
					tk[i][j][0]='(';
					tk[i][j][re+1]=')';
					tk[i][j][re+2]=0;
				}else{
					tk[i][j][0]='[';
					tk[i][j][re+1]=']';
					tk[i][j][re+2]=0;
				}
			}
			if(cho==-3){
				strcpy(tk[i][j]+1,tk[i][j-1]);
				int re=strlen(tk[i][j-1]);
				if(str[j]==')'){
					tk[i][j][0]='(';
					tk[i][j][re+1]=')';
					tk[i][j][re+2]=0;
				}else{
					tk[i][j][0]='[';
					tk[i][j][re+1]=']';
					tk[i][j][re+2]=0;
				}
			}
			if(cho>0){
				strcpy(tk[i][j],tk[i][cho]);
				int re=strlen(tk[i][cho]);
				strcpy(tk[i][j]+re,tk[cho+1][j]);
			}
		}
	}
	//printf("%d\n",d[1][len]);
	printf("%s\n",tk[1][len]);
	}
	return 0;
}
