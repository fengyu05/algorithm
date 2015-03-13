// 0/1 knapsack problem
// DP
// n number of Item
// w[] weight
// v[] value
// x[] answer
// dp[maxN][maxC]
// c knapsack capability
int knap(int i,int j){	// recurrence equation 
	if(i==n) return (j<w[n])?0:v[n];
	if(j<w[i]) return knap(i+1,j);
	return max(knap(i+1,j),knap(i+1,j-w[i])+v[i]);
}
// 整数权kp的dp解
inline max(int a,int b){return a>b?a:b;}
inline min(int a,int b){return a<b?a:b;}
#define maxN 1000
#define maxC 1000
int v[maxN],w[maxN]; //range[1..n]
int dp[maxN][maxC];
bool x[maxN];
int Knapsack(int n,int c)
{
	int i,j,minc;
	minc=min(w[n]-1,c);
	for(j=0;j<=minc;j++) dp[n][j]=0;
	for(j=w[n]; j<=c; j++) dp[n][j]=v[n];
	for (i=n-1; i>1; i--) {
		minc=min(w[i]-1,c);
		for (j=0; j<=minc; j++)
			dp[i][j] = dp[i+1][j];
		for (j= w[i]; j<=c; j++)
			dp[i][j] = max(dp[i+1][j], dp[i+1][j-w[i]] + v[i]);
	}
	dp[1][c] = dp[2][c];
	if (c >= w[1])
		dp[1][c] = max(dp[1][c], dp[2][c-w[1]] + v[1]);
	return dp[1][c];
}
void Traceback(int n, int c)
{
	for (int i = 1; i < n; i++)
		if (dp[i][c] == dp[i+1][c]) x[i] = 0;
		else {
			x[i] = 1;
			c -= w[i];
		}
	x[n] = (dp[n][c]) ? 1 : 0;
}


// backtrack
class Knapsack
{
public:
	struct Item{ double val;int w;} item[maxN];
	bool maxcmp(const Item& a,const Item& b){
		return a.val/a.w > b.val/b.w ; }
	int n;
	int cw,c;//当前重量,容量
	double cp,bestp;//当前价值,最优价值
	double Bound(int i)
	{//计算上界
		double cleft=c-cw;
		double b=cp;
		//以物品的val/w递减装入物品
		while(i<=n&&item[i].w<=cleft){
			cleft-=item[i].w;
			b+=item[i].val;
			i++;
		}
		//装满背包
		if(i<=n) b+=item[i].val/item[i].w*cleft;
		return b;
	}
	void Backtrack(int i)
	{
		if(i>n){
			bestp=cp;
			return;
		}
		if(cw+item[i].w<=c){// x[i]=1
			cw+=item[i].w;
			cp+=item[i].val;
			Backtrack(i+1);
			cw-=item[i].w;
			cp-=item[i].val;
		}
		if(Bound(i+1)>bestp)//x[i]=0;
			Backtrack(i+1);
	}
	Knapsack(int c,int n):c(c),n(n){
		cp=0,cw=0,besp=0;
		sort(item,item+n,maxcmp);
		Backtrack(1);
	}
}