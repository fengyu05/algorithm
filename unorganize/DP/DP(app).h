//最大子段和
int MaxSum(int n,int a[]){
	int sum=0,b=0;
	for(int i=0;i<n;i++){
		if(b>0) b+=a[i];
		else b=a[i];
		if(b>sum) sum=b;
	}
	return sum;
}
//最大子矩阵和 (2维最大子段)
int a[N][M],b[N];
int MaxSum2(int m,int n){
	int sum=0;
	for(int i=0;i<m;i++){
		for(int k=0;k<n;k++) b[k]=0;
		for(int j=i;j<m;j++){
			for(int k=0;k<n;k++) b[k]+=a[j][k];
			int max=MaxSum(n,b);
			if(max>sum) sum=max;
		}
	}
	return sum;
}

//凸多边形最优三角剖分

template<class Type>
void MinWeightTrianguation(int n,Type** t,int **a)
{
	for(int i=1;i<=n;i++) t[i][i]=0;
	for(int r=2;i<=n;r++){
		for(int i=1;i<=n-r+1;i++){
			int j=i+r-l;
			t[i][j]=t[i+1][j]+w(i-1,i,j);
			s[i][j]=i;
			for(int k=i+1;k<i+r-1;k++){
				int u=t[i][k]+t[k+1][j]+w(i-1,k,j);
				if(u<t[i][j]){
					t[i][j]=u;
					s[i][j]=k;
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////
// Bitonic euclidean traveling-salesman problem
#define SIZE 10
struct point
{
	int x,y;
	point(int x=0,int y=0):x(x),y(y){}
	bool operator<(const point& p){
		return x<p.x;
	}
};
inline double dist(point p1,point p2){
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
double val[SIZE][SIZE];
int solu[SIZE];
double bitonic(point p[],int n){
	sort(p,p+n);
	val[0][1]=dist(p[0],p[1]);
	for(int i=1;i<n;i++){
		for(int j=0;j<i-1;j++)
			val[j][i]=val[j][i-1]+dist(p[i],p[i-1]);
		if(i>1){
			double min=val[0][j]+dist(p[i],p[0]); // min init
			solu[i-1]=0;
			for(int k=1;k<j;k++){
				double temp=val[k][j]+dist(p[i],p[k]);
				if(min>temp){
					min=temp;
					solu[i-1]=k;
				}
			}
			val[i-1][i]=min;
		}
		if(i==n-1){
			for(int j=0;j<i;j++)
				val[j][i]+=dist(p[j],p[i]);
		}
	}
	double min=val[0][n-1]; solu[n-1]=0;
	for(int j=1;j<n-1;j++)
		if(min>val[j][n-1]){
			min=val[j][n-1];
			solu[n-1]=j;
		}
	return min;
}

	void ct_solu(int n,int out[]){ // not complete
		int *sel=new int[n],**b=new int[2][n];
		sel[n-1]=solu[n-1];
		for(int i=n-2;i>0;i--){
			if(sel[i+1]==i)
				sel[i]=solu[i];
			else
				sel[i]=sel[i+1];
		}
		cnt[0]=sel[0]=0;
		int cnt_0=1,cny_1=0,pos=0;
		for(i=1;i<n;i++){
			if(sel[i]==sel[i-1]) b[pos][o_c++]=i;
			else{
				//
			}
		}
		delete [] sel,b;
	}
//-----------------------------------------------------------------