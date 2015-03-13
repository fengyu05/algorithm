#include<iostream>
using namespace std;

bool aA0(char x){
	if(x>='A'&&x<='Z') return true;
	else if(x>='a'&&x<='z') return true;
	else if(x>='0'&&x<='9') return true;
	return false;
}
char s1[256],s2[256];
struct CK{
	int a,b;
};
CK X[256],Y[256];
int cut(char str[],CK C[]){
	int i=0,cnt=0;
	while (str[i] != '\0'){
		if(str[i] < 0) {
			C[cnt].a=i;
			C[cnt].b=i+1;
			cnt++,i++;
		}
		else{
			if(aA0(str[i])){
				C[cnt].a=i;
				while(aA0(str[i])) i++;
				C[cnt].b=i-1;
				cnt++;
				continue;
			}else{
				C[cnt].a=C[cnt].b=i;
				cnt++;
			}
		}
		i++;
	}
	return cnt;
}
bool same(int x,int y){
	int a1=X[x].a,b1=X[x].b,a2=Y[y].a,b2=Y[y].b;
	if((b1-a1)!=(b2-a2)) return false;
	for(int i=a1,j=a2;i<=b1;i++,j++){
		if(s1[i]!=s2[j]) return false;
		//printf("%c",s1[i]);
	}
	return true;
}
void put(char str[],CK C[],int l){
	for(int i=0;i<l;i++){
		for(int j=C[i].a;j<=C[i].b;j++){
			printf("%c",str[j]);
		}
		printf("\n");
	}
}
int val[256][256],last[256][256];
	//a[0..x) b[0..y) val[1..x][1..y]
	int LCS(int x,int y)
	{
		for(int i=1;i<=x;i++)
			for(int j=1;j<=y;j++){
				if(same(i-1,j-1)){
					last[i][j]=last[i-1][j-1]+1;
					int d=last[i][j];
					val[i][j]=val[i-d][j-d]+last[i][j]*last[i][j];
				}else{
					if(val[i-1][j]>val[i][j-1]){
						val[i][j]=val[i-1][j];
					}else{
						val[i][j]=val[i][j-1];
						last[i][j]=0;
					}
				}
			}
		return val[x][y];
	}	
int main()
{	
	freopen("t.in", "r", stdin);
	scanf("%s",s1);
	scanf("%s",s2);
	int L1=cut(s1,X),L2=cut(s2,Y);
	memset(val,0,sizeof(val));
		memset(last,0,sizeof(last));
	int re=LCS(L1,L2);
	printf("%d\n",re);
	return 0;
}
/*
INPUT:
内容相？１２345６???web2.00#
why内容相似???1234567890,web#00
OUTPUT: 19
*/