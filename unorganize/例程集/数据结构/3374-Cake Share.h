/* Cake Share
 * fengyu05
 * 问题:求分母小于等于n,的第k个真分数
 * 方法:Considering symmetry in Stern-Brocot Tree
   利用SB-tree的对称性,压缩空间
*/
#include<iostream>
using namespace std ;
typedef pair<int,int> P ;
#define num first 
#define den second

int n,cnt;
P arr[4000000];
void create(P left,P right)
{
	if(left.den + right.den > n) return ;
	create(left,P(left.num + right.num,left.den + right.den)) ;
	arr[++cnt] = P(left.num + right.num,left.den + right.den) ;
	create(P(left.num + right.num,left.den + right.den),right) ;
}

int main()
{
	int index,cas ;
	scanf("%d%d",&n,&cas) ;
	cnt=0;
	arr[++cnt] = P(0,1) ;
	create(P(0,1),P(1,2)) ;
	while(cas--)
	{
		scanf("%d",&index) ;
		if(index > 2*cnt + 1 || n == 1 && index > 2)
			printf("No Solution\n") ;
		else if(index <= cnt)
			printf("%d/%d\n",arr[index].num,arr[index].den) ;
		else if(n == 1 && index == 2)
			printf("1/1\n") ;
		else if(index == cnt + 1)
			printf("1/2\n") ; 
		else printf("%d/%d\n",
			arr[2*cnt - index + 2].den - arr[2*cnt - index + 2].num,
			arr[2*cnt - index + 2].den);
	}
}
