#include <iostream>
#include <cmath>
using namespace std;
#define Max 32768
#define INF 1e99
void main(){
	int a,b,aa,bb,f=1,l=1;
	scanf("%d%d",&a,&b);
	double tmp=INF,r=(double)a/b,dd;
	while(f<Max&&l<Max){
		dd=fabs((double)f/l-r);
		if(  dd< tmp && (f*b!=l*a)){
			tmp=dd;
			aa=f;bb=l;
		}
		if((double)f/l< r) f++;
		else l++;
	}
	printf("%d %d\n",aa,bb);
}