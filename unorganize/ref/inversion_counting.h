double inv(int n,int a[]){
	int l=n>>1,r=n-1,i,j;
	int* v=new int[n];
	double ret=(r>1?(inv(l,a)+inv(r,a+l):0);
	for(i=j=0;i<=l;v[i+j]=a[i],i++)
		for(ret+=j;j<r&&(i==l||a[i]>a[l+j]);v[i+j]=a[l+j],j++);
	memcpy(a,v,sizeof(int)*n);
	delete[] v;
	return ret;
}