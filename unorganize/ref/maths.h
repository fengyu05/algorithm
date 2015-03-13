// 约瑟夫问题
// 0..n-1个人,从0数起剔除第m个(先剔除m-1)
// k=m%n
//J(n,m)=(J(n-1,m)+k)%n
//J(1,m)=0
int J(int n,int m){//O(n)
	int k=m%n;
	if(k==0) k=n;
	int re=0;
	for(int i=2;i<=n;i++){
		re=(re+k)%i;
	}
	return re;
}

// 0..n-1个人,剔除没第2个(先剔除1,3..)
int J(int n){//O(log(n))
	if(n<3) return 0;
	if(n%2==0)
		return J(n/2)*2;
	else{
		n=(n+1)/2;
		return mod(J(n)-1,n)*2;
	}
		
}
/*
function : solving linear equations Ax=b
input : n,A[ i ][ j](1<=i , j<=n) ,b[ i](1<=i<=n)
output : A^-1,the inverse matrix of A
B[ i ] , the root of the equations
detA , the value of determinant A
*/
#include<math.h>
const int MAX=101;
const double eps=1e-10;
int n;
double A[MAX][MAX] ,b[MAX] ,detA;
bool solve_equations ()
{
	int i , j ,k;
	for( i=1;i<=n; i++)	b[ i]=-b[ i ];
	detA=1.0;
	for(k=1;k<=n;k++){
		detA*=A[k ][ k ];
		if (fabs(A[k][ k])<eps)	return false ; //No solution
		A[k ][k]=1/A[k ][ k];
		for( j=1;j<=n; j++){
			if ( j!=k)
				A[k ][ j]=-A[k][ j ]*A[k ][ k];
		}
		b[k]=-b[k]*A[k ][ k ];
		for( i=1;i<=n; i++){
			if ( i!=k){
				for( j=1;j<=n; j++){
					if ( j!=k)
						A[ i ][ j]=A[ i ][ j]+A[ i ][ k]*A[k ][ j ];
				}
				b[ i]=b[ i]+A[ i ][ k]*b[k ];
				A[ i ][ k]=A[ i ][ k]*A[k ][ k];
			}
		}
	}
	return true;
}