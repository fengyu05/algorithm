
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define N 256
#define INF 0x7fffffff
int w[N][N],m[N][N],s[N][N];
// x1..xn
// node: (0..x1) x1 (x1..x2) x2 ... xn (xn..INF)
//  pr :    a0   b1   a1     b2 ... bn   an
// deep:    di
// total path: P=sum{i:1..n,bi*(di+1)}+sum{j:0..n,aj*dj}

void OptimalBST(int a[],int b[],int n){
	for(int i=0;i<=n;i++){
		w[i+1][i]=a[i];
		m[i+1][i]=0;
	}
	for(int d=0;d<n;d++)
		for(int i=1;i<=n-d;i++){
			int j=i+d;
			w[i][j]=w[i][j-1]+a[j]+b[j];
			m[i][j]=INF;
			for(int k=i;k<=j;k++){
				int tmp=m[i][k-1]+m[k+1][j];
				if(tmp<m[i][j]){
					m[i][j]=tmp;
					s[i][j]=k;
				}
			}
			m[i][j]+=w[i][j];
		}
}
void OBST2(int a[],int b[],int n){
	for(int i=0;i<=n;i++){
		w[i+1][i]=a[i];
		m[i+1][i]=0;
		s[i+1][i]=0;
	}
	for(int d=0;d<n;d++)
		for(int i=1;i<=n-d;i++){
			int j=i+d;
			int i1=max(s[i][j-1],i);
			int j1=max(s[i+1][j],j);
			w[i][j]=w[i][j-1]+a[j]+b[j];
			m[i][j]=INF;
			for(int k=i1;k<=j1;k++){
				int tmp=m[i][k-1]+m[k+1][j];
				if(tmp<m[i][j]){
					m[i][j]=tmp;
					s[i][j]=k;
				}
			}
			m[i][j]+=w[i][j];
		}
}
//四边形不等式
/*   min{ m(i,k-1)+m(k,j) }=   min{ m(i,k-1) + m(k,j) }
  (i<k<=j)            s(i,j-1)<=k<=s(i+1,j)
*/

int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int a[]={2,2,2,2,2,2};
	int b[]={0,3,4,5,3,5};
	int n=5;
	//OptimalBST(a,b,n);
	OBST2(a,b,n);
	return 0;
}