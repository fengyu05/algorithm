#include <iostream>
//#include <ctime>
using namespace std;

#define N 128//0
struct HF {
	int len,sign,prec;
	char s[N];
	HF(int inte=0){
		prec=len=0;
		sign=1;
		if(inte<0) inte=-inte,sign=-1;
		do{
			s[++len]=inte%10;
			inte/=10;
		}while(inte>0);
	}
	HF(char* str){
		int p, i , j ;
		s[0]=0,s[1]=0, sign=1;
		if(str[0]=='-'){ sign = -1; str++; };
		if(str[0]=='+'){ sign = 1; str++; };
		len=strlen(str);
		for(p=0; p<len; p++)
			if( str[p]=='.') break;
		if (p==len) prec = 0;
		else prec = len-1-p;
		for( i=len-1,j=0; i >=0; i--)
			if (str[i]!='.' )
				s[++j] = str[i]-'0';
		while(j>1 && !s[j]) --j;
		len = j;
	}
	void print(){
		if (sign<0) printf("-");
		int i ,k,low=1;
		for( i=len ; i>prec ; i--) printf("%d",s[i]);
		if (len<=prec ) printf("0");
		k=i;
		while( k>0 && s[k]==0 ) k--;
		if (k==0){
			printf(".0\n");
			return;
		}
		printf(".");
		if (len<prec)
			for(int j=0;j< prec-len ; j++)
				printf("0");
		while(s[low]==0) low++;
		while(i>=low ) printf("%d",s[i--]);
		printf("\n");
	}
	// + for left shift - for right shift
	void shift(int sl){	prec+=sl;}
};
int main()
{
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	HF c="1000.000000";
	c.print();
	return 0;
}