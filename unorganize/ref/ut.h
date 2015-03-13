template<class T>inline const T& min(const T& a, const T& b){return b < a ? b : a;}
template<class T>inline const T& max(const T& a, const T& b){return a < b ? b : a;}
int fcmp(double a,double b)
{
    if(a > b+eps) return 1;
    if(a < b-eps) return -1;
    return 0;
}
int cmp(const void *a,const void *b){return *(int*)b - *(int*)a;}
//  取位
inline int digit(__int64 i,int n){
	return (i>>(n-1))%2;
}
int round(int n){//整数四舍五入
//eg : 1444445 => 2000000	
	int dig,mark=10;
	while(mark<n){
		dig=n%mark;
		n-=dig;
		if(dig>=mark/2)
			n+=mark;
		mark*=10;
	}
	return n;
}
#define _cmp(a,b) ((a)<(b))
template<class T>
T kth_element(T a[],int n,int k) // the smallest k=0
{
	T tmp,key;
	int l=0,r=n-1,i,j;
	while(l<r){
		i=l-1,j=r+1;
		for(key=a[(i+j)/2];i<j;){
			for(j--;_cmp(key,a[j]);j--);
			for(i++;_cmp(a[i],key);i++);
			if(i<j) tmp=a[i],a[i]=a[j],a[j]=tmp;
		}
		if(k>j) l=j+1;else r=j;
	}
	return a[k];
}






// Ackermann function
int A(int n,int m){
	if(n==0) return m+1;
	if(n>0&&m==0) return A(n-1,1);
	else return A(n-1,A(n,m-1));		
}


