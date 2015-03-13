#include <iostream>

using namespace std;
#define N 128

void LUP_solve(double LU[][N],double b[],double x[],int P[],int n){
	double y[N];
	int i,j;
	for(i=0;i<n;i++){
		y[i]=b[P[i]];
		for(j=0;j<i;j++)
			y[i]-=LU[i][j]*y[j];
	}
	for(i=n-1;i>=0;i--){
		x[i]=y[i];
		for(j=i+1;j<n;j++)
			x[i]-=LU[i][j]*x[j];
		x[i]/=LU[i][i];
	}
}
bool LUP_decompose(double A[][N],int P[N],int n){
	for(int i=0;i<n;i++){
		P[i]=i;
	}
	for(int k=0;k<n;k++){
		if(A[k][k]==0){
			for(int i=k+1;i<n;i++){
				if(A[i][k]!=0){
					swap(P[i],P[k]);
					for(int j=0;j<n;j++)
						swap(A[i][j],A[k][j]);
					break;
				}
			}
			return false;// A is sigular matrix
		}
		for(int i=k+1;i<n;i++){
			A[i][k]/=A[k][k];
			for(int j=k+1;j<n;j++){
				A[i][j]-=A[i][k]*A[k][j];
			}
		}
	}
	return true;
}
void transpose(double A[][N],int n){
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			swap(A[i][j],A[j][i]);
}
void inver(double A[][N],double X[][N],int n){
	int P[N];
	LUP_decompose(A,P,n);
	double b[N];
	memset(b,0,sizeof(b));
	for(int i=0;i<n;i++){
		b[i]=1;
		LUP_solve(A,b,X[i],P,n);
		b[i]=0;
	}
	transpose(X,n);
}
void read(double A[][N],int n){
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%lf",&A[i][j]);
}
void print(double A[][N],int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			printf("%8.2lf",A[i][j]);
		printf("\n");
	}
}
// -------------- --------------------  ------------------------
double A[N][N],b[N],x[N],X[N][N];
bool solve(int n){
	int P[N];
	bool re=LUP_decompose(A,P,n);
	if(!re) return false;
	LUP_solve(A,b,x,P,n);
	return true;
}
void read_augment(int n){// read augment matrix to A,b
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			scanf("%lf",&A[i][j]);
		scanf("%lf",&b[i]);
	}
}
void put_result(int n){// 
	for(int i=0;i<n;i++)
		printf(" x%d = %.4lf \n",i,x[i]);	
}



int main()
{
	freopen("t.in", "r", stdin);
	int n;
	scanf("%d",&n);
	read(A,n);
	print(A,n);
	inver(A,X,n);
	print(X,n);
	return 0;
}