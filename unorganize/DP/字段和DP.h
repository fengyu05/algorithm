//最大子段和
int MaxSum(int n,int a[]){
	int sum=0,b=0;
	for(int i=0;i<n;i++){
		if(b>0) b+=a[i];
		else b=a[i];
		if(b>sum) sum=b;
	}
	return sum;
}
//最大子矩阵和 (2维最大子段)
#define N 128
int a[N][N],b[N];
int MaxSum2(int m,int n){
	int sum=0;
	for(int i=0;i<m;i++){
		for(int k=0;k<n;k++) b[k]=0;
		for(int j=i;j<m;j++){
			for(int k=0;k<n;k++) b[k]+=a[j][k];
			int max=MaxSum(n,b);
			if(max>sum) sum=max;
		}
	}
	return sum;
}