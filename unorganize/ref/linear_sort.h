// Counting sort
const int K;// Max-key
void counting_sort(int a[],int b[],int n){
	int c[K+1]={0},i;
	for(i=0;i<n;i++)
		c[a[i]]++;
	for(i=1;i<=k;i++){
		c[i]=c[i]+c[i-1];
	}
	for(int j=n-1;j>=0;j--){
		b[c[a[j]]]=a[j];
		c[a[j]]--;
	}
}