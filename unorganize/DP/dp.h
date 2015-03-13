/*
    动态规划
(I)  基础
1.   Characterize the structure of an optimal solution.
	 识别最优结构(最优子结构,无后效性,子问题重叠) 
2.   Recursively define the value of an optimal solution.
	 递归定义状态转移方程(阶段X状态X决策) 
3.   Compute the value of an optimal solution in a bottom-up fashion.
	 自下向上求解 或自上向下记忆化递归 
4.   Construct an optimal solution from computed information. 
	 重构解路径 Trackback

两种动机:
(1)利用递归的子问题重叠,进行记忆化
(2)把问题看成多阶段决策问题
**.递归建立模型,容易算出状态前趋,适合顺推
 多阶段决策建立模型,容易算出状态后继,适合逆推

无后效性和子结构:决策只取决于当前状态的特征因素
如果多阶段决策问题,具有最优子结构(最优决策的子序列也是最优)和无后效性
则可用动态规划来解决
动态规划的高效性源于子问题重叠

状态表示:动态规划方法的核心,状态的可定义性源于问题无后效性
状态是人为规定的,可以通过增加维数方法来消除后效性
也可在保持无后效性前提下修改状态表示

状态转移:状态转移的可定义性源于问题最优子结构
当问题不具有最优子结构时,通过增加维数方法来解决
但注意结果可能使子问题不重叠,从而动态规划失去意义.

算法复杂度:状态数*决策数*转移费用

常见模型:
1.线性模型

(II) 典例
1. 一维DP(状态集为一维)
阶段:n 状态:s 决策:c
	f[0][j]=init(j)
	f[i][j]=min|max{ op(f[i-1][k]) }
	{ 0<i<n , 0<=j<s , 0<=k<c }

sample:
 双流水线问题(算导15.1)

2. 三角DP
阶段:d=i-j 状态:i~j 决策:i~j
	m[i,j]=init(i) if i=j
	m[i,j]=min|max{ op(m[i,k],m[k+1][j]) }

*/
//code:
for(int i=0;i<n;i++) m[i][i]=init(i);
for(int d=1;d<n;d++){//  if d=1 then i<n-1 , if d=n-1 i<1 => i=0
	for(int i=0;i<n-d;i++){  //      j=i+1 ,          j=n-1
		int j=i+d;
		m[i][j]=INF;// for min-optimal
		for(int k=i;k<j;k++){
			int q=op(m[i][k],m[k+1][j]);
			if(q<m[i][j])
				m[i][j]=q,s[i][j]=k;
		}
	}
}
/*
sample:
 矩阵链问题(算导15.2)
 最优二叉树(算导15.5)
*/
// code:
void optimal_bst(int n,int p[],int q[],int e[][],int w[][],int root[][]){
	int i,l,j,r;
	for(i=0;i<=n;i++){
		e[i+1][i]=p[i];
		w[i+1][i]=q[i];
	}
	for(l=1;l<=n;l++){
		for(i=1;i<=n-l+1;i++){
			j=i+l-1;
			e[i][j]=-1;  // mark unlimits as -1;
			w[i][j]=w[i][j-1]+p[j]+q[j];
			for(r=i;r<=j;r++){
				int t=e[i][r-1]+e[r+1][j]+w[i][j];
				if(t<e[i][j]||e[i][j]==-1)
					e[i][j]=t;
				root[i][j]=r;
			}
		}
	}
}
void construct_bst(int i,int j,tree p){
	if(i<j) return;
	int r=root[i][j];	
	node f(r,p);
	construct_bst(i,r-1,f);
	construct_bst(r+1,n,f);	
} /*
3. 二维DP
阶段~  状态~ 决策~

sample:
 LCS问题(算导15.4)
*/ 
// code:
int val[N][N]={0};
char solu[N][N]; //a[0..x) b[0..y) val[1..x][1..y]
	int LCS(int a[],int b[],int x,int y)
	{
		for(int i=1;i<=x;i++)
			for(int j=1;j<=y;j++){
				if(a[i-1]==b[j-1]){
					val[i][j]=val[i-1][j-1]+1;
					solu[i][j]='\\';
				}else{
					if(val[i-1][j]>val[i][j-1]){
						val[i][j]=val[i-1][j];
						solu[i][j]='|';
					}else{
						val[i][j]=val[i][j-1];
						solu[i][j]='-';
					}
				}
			}
		return val[x][y];
	}	
	void print_lcs(int a[],int i,int j){
		if(i==0||j==0) return;
		switch(solu[i][j])
		{
		case '\\':
			print_lcs(a,i-1,j-1);
			cout<<a[i-1];
			break;
		case '|':
			print_lcs(a,i-1,j);
			break;
		case '-':
			print_lcs(a,i,j-1);
			break;
		}
	}

 
