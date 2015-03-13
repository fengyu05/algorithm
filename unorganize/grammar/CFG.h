// Problem   Any fool can do it
// Algorithm Memoization + Ruccurence
// Runtime   O(n^3)
/*
Set          ::= "{" List "}"
Elementlist  ::= <empty> | List
List         ::= Element | Element "," List
Element      ::= Atom | Set
Atom         ::= "{" | "}" | ","

==>
Set          ::= "{" List "}"
List		 ::= <empty> | Element "," List | List
Element      ::= "{" | "}" | "," | Set
*/
#include<iostream>
using namespace std;
#define N 256
char str[256];
char set[N][N],lis[N][N];

char isELM(int a,int b);
char isLIS(int a,int b);
char isSET(int a,int b);

char isELM(int a,int b){
	char c=str[a];
	if(a==b&&(c=='{'||c=='}'||c==',')) return 1;
	return isSET(a,b);
}
char isLIS(int a,int b){
	if(a>b) return 1;
	if(lis[a][b]==-1){
		int re=0;
		if(isELM(a,b)) re=1;
		else{
			for(int i=a+1;i<b;i++){
				if(str[i]==','){
					if(isELM(a,i-1)&&isLIS(i+1,b)){
						re=1;
						break;
					}
				}
			}
		}
		lis[a][b]=re;
	}
	return lis[a][b];
}
char isSET(int a,int b){
	if(a>=b) return 0;
	if(set[a][b]==-1){
		int re=0;
		if(str[a]=='{'&&str[b]=='}'){
			if(isLIS(a+1,b-1)) re=1;
		}
		set[a][b]=re;
	}
	return set[a][b];
}

int main()
{	
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",str);
		memset(set,-1,sizeof(set));
		memset(lis,-1,sizeof(set));
		int len=strlen(str);
		printf("Word #%d: ",i);		
		int re=isSET(0,len-1);	
		if(re==0)printf("No ");
		printf("Set\n");
	}
	return 0;
}