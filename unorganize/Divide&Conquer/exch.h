//O(1) �ռ����黻λ
// a[0:n-1]�� a[0:k-1] a[k:n-1]����λ��
// ���η�ת�㷨
template<class T> void reverse(T a[],int i,int j){
	while(i<j){ swap(a[i],a[j]); i++,j--; }
}
template<class T> void exch(T a[],int n,int k){
	reverse(a,0,k-1);
	reverse(a,k,n-1);
	reverse(a,0,n-1);
}