// Catalan numbers
int c[maxN];
c[0]=1;
c[1]=1;
for(i=2;i<maxN;i++){
	c[i]=0;//
	for(int k=0;k<i;k++)
		c[i]+=c[k]*c[i-k-1];	
	//cout<<"c["<<i<<"]="<<c[i]<<endl;
}
//
//n��+1��n��-1���ɵ�2n���䲿�ֺͶ��ǷǸ������и���������n�����Ķ�����������
//����Catalan��Cn
long Cat(long n)
{
	double result;
	long dv;
	if(n==0)return 1;
	result=1;
	dv=n;
	for(long i=n+2;i<=2*n;i++){
		result*=double(i);
		while(result>1&&dv>1){
			result/=double(dv);
			dv--;
		}
	}
	while(dv>1){
		result/=double(dv);
		dv--;
	}
	return long(result+0.5);
}
// ��Ե��� sorting by swap
int swap_num(int a[],int pos[],int n){ // a[1..n]��������  ,pos[1..n]��������
	int sum=0;
	for(i = 1;i <= n;i++)
		{
			if(a[i] != i)
			{
			   a[pos[i]] = a[i];
			   pos[a[i]] = pos[i];	
			   sum++;
			}
		}
	return sum
}
