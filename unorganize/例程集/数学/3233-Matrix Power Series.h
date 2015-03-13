/*  3233-Matrix Power Series
 * fengyu05
 * 题目:求S = A + A^2 + A^3 + … + A^k

	两种办法，一种是递推
	先把A提出来，算 F(K)=I+A+A^2+A^3+...+A^(K-1)
	F(N)可以分奇偶递推:
	若N为偶数，F(N)=F(N/2)+F(N/2)*A^(N/2)
	若N为奇数，F(N)=I+ F(N/2)*A + F(N/2) * (A^(N/2+1))

	另外一个巧妙的办法就是构造一个这样的矩阵
	A I
	O I
	O为零矩阵，I为单位矩阵
	这个矩阵的K次方是
	A^K I+A+A^2+..+A^(K-1)
	O   I
*/
#include <iostream>
using namespace std;

#define N 64
int m;
int I[N][N],_tmp1[N][N],_tmp2[N][N];
void init(){
	memset(I,0,sizeof(I));
	for(int i=0;i<N;i++) I[i][i]=1;
}
void add(int c[N][N],int a[N][N],int b[N][N],int n){ // c=a+b
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			c[i][j]=a[i][j]+b[i][j];
		}
}
void muti(int c[N][N],int a[N][N],int b[N][N],int n){ // c=a*c
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			c[i][j]=0;
			for(int k=1;k<=n;k++){
				c[i][j]=(c[i][j]+a[i][k]*b[k][j])%m;
			}
		}
}
void pow(int c[N][N],int a[N][N],int k,int n){ // c=a^k
	if(k==1){
		muti(c,a,I,n);
		return;
	}
	pow(_tmp1,a,k/2,n);
	muti(_tmp2,_tmp1,_tmp1,n);
	if(k%2==0) muti(c,_tmp2,I,n);
	else muti(c,_tmp2,a,n);
}
int mat[N][N],re[N][N];
void main()
{
	int k,n;
	init();
	scanf("%d%d%d",&n,&k,&m);
	int i,j;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			scanf("%d",&mat[i][j]);
			if(i==j)
				mat[i][j+n]=mat[i+n][j+n]=1;
		}
	}
	pow(re,mat,k,n*2);
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			re[i][j]+=re[i][j+n];
			re[i][j]-=re[i+n][j+n];
			printf("%d",re[i][j]%m);
			if(j==n) printf("\n");
			else printf(" ");
		}
	}
}