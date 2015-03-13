template < int  N > // ��ʾ��������Ϊ[0,N)������N������2������;
class  PointTree {
public:
    int  a[ 2 * N];
    int  size; 
    void  clear() { memset( this , 0 , sizeof(*this));} 
	PointTree(){clear();}
    void  add( int  n) {
        int  i = N + n;  ++ size; 
        for ( ++ a[i]; i > 1 ; i /= 2 )
            if ( ~ i & 1 ) a[i / 2 ] ++ ;
    }  
    int  cntLs( int  n) { // ͳ��С�� 
        int  i = N + n,c = 0 ;  // ��ͳ��С�ڵ�����c=a[i]; 
        for (; i > 1 ; i /= 2 ) 
            if (i & 1 ) c += a[i / 2 ];
        return  c;
    }
    int  cntGt( int  n) {  return  size - a[N + n] - cntLs(n); }  
	void del(int n){
        if(!a[n+=N])return;
        --size;
        for(--a[n]; n>1; n/=2)
            if(~n&1)--a[n/2];
    }
    /**//*  �������㼯�е�iС����(��0����)
     *    ע�⣺���i>=size ����N-1 
     */ 
    int operator[](int n){
        int i=1;
        while(i<N){
            if(n<a[i]) i*=2;
            else n-=a[i], i=i*2+1;
        }
        return i-N;
    }    
}; 