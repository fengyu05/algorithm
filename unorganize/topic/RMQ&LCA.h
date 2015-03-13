/* -----------------RMQ  && LCA ----------------------
�㷨����	�������		ʱ������		�ռ�����
ST�㷨		һ��RMQ����		O(NlogN)-O(1)	O(NlogN)
Tarjan�㷨	LCA����			O(Na(N) + Q)	O(N)
��1RMQ�㷨	��1RMQ����		O(N)-O(1)		O(N)

����ת��
1: RMQ(A��i��j) = LCA(T��i��j) T�ǽ�����A���е�Cartesian Tree

2: LCA(T, u, v) = RMQ(B, pos(u), pos(v))

���и���T����DFS�����������Ľ�㰴��˳�����һ������Ϊ2N-1�����У�
��֮ΪT��ŷ������F,��BΪF����ؽ������.
ÿ����㶼��ŷ�������г��֣����Ǽ�¼���u��ŷ�������е�һ��
���ֵ�λ��Ϊpos(u)

**
һ��RMQ����	 =>	  LCA����	=>   ��1RMQ����
  ST�㷨	O(n) Tarjan�㷨 O(n) ��1RMQ�㷨

*/
//-----------------------------------------------------------------
//1:  Range Maximum Query
// ST�㷨 O(NlogN) Ԥ����, O(1) ѯ�� ,O(NlogN) �ռ�
int a[N],h[N][maxL]; // maxL = sqrt{N} + 3
#define maximum(a,b) (a<b?a:b) // < for min, > for max
void PreProcess(int n)
{
	int i , j , l ;
	for( i=0;i<n; i++) h[i][0]=a[i];
	for( j=1,l=1; l*2<=n; j++,l*=2)
		for( i=0; i<=n-l *2; i++)
			h[i][j] =maximum(h[i][j-1],h[i+l][j-1]);
}
int Query(int s , int t) // return max{a[s .. t]}
{
	int j=0,l=1;
	while( 2*l<=t-s+1 ){ j++; l*=2; }
	return maximum(h[s][j],h[t+1-l][j]);
}
// O(N) Ԥ����, O(sqrt(N)) ѯ��, O(N)�ռ�
int a[N] ,b[maxL], L;
#define _cmp(x,y) (a[x]<a[y]) // < for min,> for max
void PreProcess(int n)
{
	int i , j ,up,k;
	L = (int)sqrt(n);
	for( i=k=0; i<n; k++ ) {
		up=i+L;
		if ( up>n ) up = n;
		for( j=i +1; j<up; j++)
			if(_cmp(j,i)) i=j ;
		b[k]=i ; i=up;
	}
}
int Find(int s , int t) // return { i|a[i]=max{a[ss .. ee]} }
{
	int i ,up,u,v,k;
	u = s / L; v = t / L; k = s;
	if ( u<v ) {
		k=s ; up=(u+1)*L;
		for( i=u+1; i<v ; i++) if(_cmp(b[i],k)) k =b[i];
		for( i=s  ; i<up; i++) if( _cmp(i,k)) k = i ;
		for( i=v*L; i<=t; i++) if( _cmp(i,k)) k = i ;
	} else 
		for( i=s ; i<=t ; i++) if( _cmp(i,k))  k = i ;
	return k;
}

//------------------------------------------------------------------
//2: Least Common Ancestor
int n,h, root ; // maxh-1 = h = floor ( log ( 2 , n-1 ) )
int pnt[N][maxh] ,son[N] , next [N] ,depth[N];
int stack [N] , mylog[N];
int GetParent(int x, int len)
{
	while(len>0){
		x = pnt[x ][ mylog[ len ] ];
		len -= ( 1<<mylog[len] );
	}
	return x;
}
int LCA(int x, int y) // O( log N )
{
	int nx,ny,px,py,low ,mid, high ;
	low=0;
	high = depth[x]<depth[y] ? depth[x] : depth[y];
	px = GetParent(x, depth[x]-high ) ;
	py = GetParent(y, depth[y]-high ) ;
	if ( px == py ) return px;
	while(high-low>1)
	{
		mid = mylog[high-low-1];
		nx = pnt[px ][mid];
		ny = pnt[py ][mid];
		mid = high - (1<<mid);
		if ( nx == ny ) low = mid;
		else{ high = mid; px = nx; py = ny; }
	}
	return pnt[px ][ mylog[high-low ]];
}
int LCA2(int x, int y) // O( log^2 N )
{
	int low ,mid, high ;
	low = 0;
	mid = high = depth[x]<depth[y] ? depth[x ] : depth[y ];
	if ( GetParent(x, depth[x]-mid) != GetParent(y, depth[y]-mid) )
	while(low+1<high)
	{
		mid = (low + high ) / 2;
		if ( GetParent(x, depth[x]-mid) != GetParent(y, depth[y]-mid) )
		high = mid; else low = mid;
	} else low = high ;
	return GetParent(x, depth[x]-low ) ;
}
void dfs(int d, int cur)
{
	int i , j ;
	stack [d] = cur ;
	depth[ cur] = d;
	for( j=1,i =2; i<=d; j++,i *=2 )
		pnt[ cur ][ j]=stack [d-i ];
	for( j=son[ cur ]; j ; j=next [ j ])
		dfs ( d+1, j );
}
void main()
{
	int i , j ,k, l ;
	for( i=0,j=1; j<N; i++)
	{
		k = j *2; if ( k>N ) k = N;
		while( j<k ) mylog[ j++] = i ;
	}
	cin>>n;
	for( i =1; i<=n; i++) {
		son[i] = next[i] = 0;
		for( j=0; j<=h; j++)
			pnt[i][j] = 0;
	}
	for( i =1; i<n; i++) {
		cin >> j >> k;
		pnt[j][0] = k;
		next[j]=son[k ];
		son[k]=j ;
	}
	for( i =1; i<=n; i++)
		if (pnt[i][0]==0 ){
			root=i ;
			break;
		}
	dfs( 0 , root ); // Preprocess Parent Array
	for(cin>>k; k; k--){
		cin >> i >> j;
		cout << LCA(i , j) <<endl ;
	}
}

//4: Cartesian Tree
int lson[N] , rson[N] ,pnt[N] , root;
void BuildCartesianTree(int a[], int n)
{
	int i , j ;
	for( i=0; i<n; j=i++) {
		pnt[i]=i-1;
		lson[i]=rson[i]=-1;
		j=i ;
		while( pnt[ j]>=0 && a[ i]>a[pnt[ j ]] )
			j = pnt[ j ];
		if ( j!=i ) { pnt[ i]=pnt[ j ]; lson [ i]=j ; pnt[ j]=i ; };
		if (pnt[i]>=0) rson[pnt[ i ]]= i ;
	}
	for( i=0;i<n; i++)
		if(pnt[i]<0) root=i ;
}

