/* 2295 A DP Problem
 * feng 
 */

#include <iostream>
using namespace std;
int main()
{
#ifndef ONLINE_JUDGE
	freopen("I:\\acm\\acm\\input.txt", "r", stdin);
#endif
	char str[270];
	int test;
	scanf("%d\n",&test);
	while(test--){
		gets(str);
		int x=0,c=0,i=0,m=1,n=1,temp=0;
		bool first_num=true;
		while(1){
			if(str[i]>='0'&&str[i]<='9'){
				temp=temp*10+str[i]-'0';
				first_num=false;
			}else{
				if(str[i]=='x'){
					if(first_num) temp=1;
					x+=m*n*temp;
				}else
					c+=m*n*temp;
				temp=0;
				m=1;
				first_num=true;
				if(str[i]=='-') m=-1;
				if(str[i]=='=') n=-1;
				if(str[i]=='\0') break;
			}     
			i++;
		}
		if(x==0&&c==0) printf("IDENTITY\n");
		else if(x==0) printf("IMPOSSIBLE\n");
		else if(c==0) printf("0\n");
		else{
			float re=(float)-c/x;
			printf("%.0f\n",re); 
		}
	}  
}