int Horner(int poly[],int n,int x){
	int re=poly[n-1];
	for(int i=n-2;i>=0;i--){
		re=re*x+poly[i];
	}return re;
}
int add(int a[],int b[],int n,int c[]){
	for(int i=0;i<n;i++){
		c[i]=a[i]+b[i];
	}
	while(c>0&&c[n-1]==0) n--;
	return n;
}
int mul(int a[],int n,int b[],int m,int c[]){
	//(init c)
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			c[i+j]+=b[i]*a[j];
		}
	}
	return m+n-1;
}

