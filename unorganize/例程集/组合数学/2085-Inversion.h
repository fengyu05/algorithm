/* 2085-Inversion
  求逆序为m的最小一个n排列
  解法:点数
 */
#include <iostream>
using namespace std;
#define N 65536
int a[N],inv[N],per[N];

void cal(int n,int m){
	memset(inv,0,sizeof(inv));
	for(int i=1;i<n;i++){
		if(m>per[n-i]){			
			m-=n-i;
			inv[i]=n-i;
		}
	}
}
template < int  cnt > // 表示可用区间为[0,N)，其中N必须是2的幂数;
class  PointTree {
public:
    int  a[ 2 * cnt];
    int  size; 
    void  clear() { memset( this , 0 , sizeof(*this));} 
	PointTree(){clear();}
    void  add( int  n) {
        int  i = N + n;  ++ size; 
        for ( ++ a[i]; i > 1 ; i /= 2 )
            if ( ~ i & 1 ) a[i / 2 ] ++ ;
    }  
    int  cntLs( int  n) { // 统计小于 
        int  i = N + n,c = 0 ;  // 若统计小于等于则c=a[i]; 
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
    /**//*  解决：求点集中第i小的数(由0数起)
     *    注意：如果i>=size 返回N-1 
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
void perm(int n)
{//由逆序列生成原列
	PointTree<N> pt;int i;
	for(i=1;i<=n;i++) pt.add(i);
	for(i=1;i<=n;i++){
		int tmp=pt[inv[i]];
		a[tmp]=i;
		pt.del(tmp);
	}
}
template<class T>
void print(T beg,T end,char* text=""){
    cout<<text<<*beg;
    for (++beg;beg!=end;++beg) {
        cout<<' '<<*beg;
    }
    cout<<endl;
}
int main()
{
	int n,m,i;
	per[1]=0;
	for(i=2;i<N;i++) per[i]=per[i-1]+i-1;
	while(scanf("%d%d",&n,&m),n!=-1){
		cal(n,m);
		perm(n);
		print(a+1,a+1+n);
	}
	return 0;
}