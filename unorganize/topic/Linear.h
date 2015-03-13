#include <iostream>

using namespace std;
#define N 128

// Linear Equation in R
#define EPS 1e-8
int dcmp(double x){
	if(x>EPS) return 1;
	if(x<-EPS) return -1;
	return 0;
}
double A[N][N];
int reduce(int n,int m){
	int i,j,k,r=0;
	for(i=0;i<n;i++){
		for(j=r;j<m&&!dcmp(A[j][i]);j++);
		if(j>=m) continue;
		if(j>r){
			for(k=0;k<=n;k++)
				swap(A[r][k],A[j][k]);
		}
		for(j=0;j<m;j++){
			double tmp;
			if(j!=r&&dcmp(A[j][i]))
				tmp=A[j][i]/A[r][i];
			for(k=0;k<=n;k++)
				A[j][k]-=tmp*A[r][k];
		}
		r++;
	}
	for(i=0;i<m;i++) if(dcmp(A[i][n])){
		for(j=0;j<n&&!dcmp(A[i][j]);j++);
		if(j==n) return 0;
	}
	return 1;
}
int main()
{
	freopen("t.in", "r", stdin);

	return 0;
}