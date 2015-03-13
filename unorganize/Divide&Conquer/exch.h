//O(1) 空间数组换位
// a[0:n-1]中 a[0:k-1] a[k:n-1]交换位置
// 三次反转算法
template<class T> void reverse(T a[],int i,int j){
	while(i<j){ swap(a[i],a[j]); i++,j--; }
}
template<class T> void exch(T a[],int n,int k){
	reverse(a,0,k-1);
	reverse(a,k,n-1);
	reverse(a,0,n-1);
}