// 求 n表示为连续整数相加的可行方法数
// eg: 15=>4
// 15=1+2+3+4+5
// 15=2+3+4+5+6
// 15=7+8
// 15=15
#include<stdio.h>
void main()
{
	int n,i,ways;
 	scanf("%d",&n);
 	ways = 0;
 	if(n%2 != 0) ways++;
 	for(i = 1;i < n;i = i + 2){
 		if(n%i == 0) ways++;
 	}
 	printf("%d\n",ways);
}