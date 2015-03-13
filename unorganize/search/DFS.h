//------------------  DFS ----------------------------
//1) --------------- Backtrack Search ------------------
//2) DFSBnB 分支限界的DFS ，由DFS加上最优性剪枝
// Recur
void Backtrack(int t){
	if(t>n) output(x));
	else for(int i=f(n,t);i<=g(n,t);i++){
		x[t]=h(i);
		if(Constraint(t)&&Bound(t))
			Backtrack(t+1);
	}
}
//Iterative
void Backtrack()
{
	int t=1;
	while(t>0)
	{
		if(f(n,t)<=g(n,t))
			for(int i=f(n,t);i<=g(n,t);i++){
				x[t]=h(i);
				if(Constraint(t)&&Bound(t)){
					if(Solution(t)) output(x);
					else t++;
				}
			}
		else t--;
	}
}
//排列树
void backtrack(int t){
    if (t>n) output(x);
    else 
       for(int i=t;i<=n;i++){
           swap(x[t],x[i]);
           if (constraint(t) && bound(t))
                 backtrack(t+1);
           swap(x[t],x[i]);
       }
}
//子集树
void backtrack(int t){
    if (t>n) output(x);
    else 
       for(int i=t;i<=1;i++){
           x[t]=i
           if (constraint(t) && bound(t))
                 backtrack(t+1);
       }
}

//------------------- Application -----------------------------

/* 1.装载问题 -- 子集树搜索,约束&限界剪枝
问题:求是否存在将n个重量为wi的集装箱装上载量为c1,c2的船(NP)
(*若 Sigma(i=1:n,wi)=c1+c2 为子集和问题,当c1=c2,等价于划分问题)
问题归约:将一艘船尽可能装满,剩下的可装入第二艘为可行解
于是归于为特殊0-1背包(价值等于重量)
  reduce to:  max( Sigma(i=1:n,wi*xi) )
             st.  Sigma(i=1:n,wi*xi)<=c1
			   xi@{0,1}, 1<=i<=n (@ for belong to)
*/
int n,x[N],bestx[N];
double w[N];
double c,cw,bestw,r;//容量,当前重量,最优重量,剩余容量
void Backtrack(int i){
	if(i>n){
		if(cw>bestw){
			for(int j=1;j<=n;j++)
				bestx[j]=x[j];
			bestw=cw;
		}
		return;
	}
	r-=w[i];
	if(cw+w[i]<=c){//约束剪枝
		x[i]=1; //left subtree
		cw+=w[i];
		Backtrack(i+1);
		cw-=w[i];
	}
	if(cw+r>bestw){ // 限界剪枝		
		x[i]=0; //right subtree
		Backtrack(i+1);
	}
	r+=w[i];
}
double MaxLoading(){
	cw=0,bestw=0,r=0;
	for(int i=1;i<=n;i++)
		r+=w[i];
	Backtrack(1);
	return bestw;
}
/* 2.批处理作业调度 -- 排列树搜索,限界剪枝
问题:n个作业集合J=(J1,J2,...Jn).每个需在机器1加工后2加工
i作业在j机器需时Mij,Fji为i作业在j机器的完成时间
 min( Sigma(i=1:n,F2i) )
*/
int M[N][2];// 各作业处理时间
int x[N],bestx[N];//当前作业调度,当前最优调度
int f2[N],f1;//机器2完成处理时间,机器1完成处理时间
int f,bestf,n;//完成时间和,当前最优值,作业数
void Backtrack(int i){
	if(i>n){
		for(int j=1;j<=n;j++)
			bestx[j]=x[j];
		bestf=f;
	}else{
		for(int j=i;j<=n;j++){
			f1+=M[x[j]][0];
			f2[i]=(f2[i-1]>f1?f2[i-1]:f1)+M[x[j]][1];
			f+=f2[i];
			if(f<bestf){
				swap(x[i],x[j]);
				Backtrack(i+1);
				swap(x[i],x[j]);
			}
			f1-=M[x[j]][0];
			f-=f2[i];
		}
	}
}
int Flow(){
	f1=f=0;
	bestf=INF;
	for(int i=1;i<=n;i++)
		f2[i]=0,x[i]=i;
	Backtrack(1);
	return bestf;
}
/* 3.符号三角形
*/
int n,  //第一行符号数
 half,  //n*(n+1)/4
 count, //当前+个数
p[N][N];//符号三角形矩形
int sum;//已找到的符号三角形数
void Backtrack(int t){
	if( (count>half)||(t*(t-1)/2-count>half) ) return;
	if(t>n) sum++;
	else for(int i=0;i<2;i++){
		p[1][t]=i;
		count+=i;
		int j;
		for(j=2;j<=t;j++){
			p[j][t-j+1]=p[j-1][t-j+1]^p[j-1][t-j+2];
			count+=p[j][t-j+1];
		}
		Backtrack(t+1);
		for(j=2;j<=t;j++){
			count-=p[j][t-j+1];			
		}
		count-=i;
	}
}
int Compute(){
	count=sum=0;
	half=n*(n+1)/2;
	if(half%2==1) return 0;
	half/=2;
	memset(p,0,sizeof(p));
	Backtrack(1);
	return sum;
}
/* 4.n后问题
*/
 //--------------------  求一个n queen 解  ----------------------------
/* TLE in POJ 3239 */
	int n,x[N]; //solution [1..n]
	bool row[N];
	bool dl[2*N];//向左下的对角线 l=x[i]+i-1
	bool dr[2*N];//向右下的对角线 r=n+x[i]-i
	bool backtrack(int t)
	{
		for(int i=(n%2?2:1);i<=n;i+=2){
			int l=i+t-1,r=n+i-t;
			if(row[i]==0&&dl[l]==0&&dr[r]==0){
				x[t]=i;
				row[i]=1;dl[l]=1;dr[r]=1;
				if(t==n) return true;
				if(backtrack(t+1)) return true;
				row[i]=0;dl[l]=0;dr[r]=0;
			}
		}
		return false;
	}
	void nqueen(){
		memset(row,0,N);
		memset(dr,0,2*N);
		memset(dl,0,2*N);
		if(n%2==0){
			int m=n/2;
			for(int i=1;i<=m;i++){
				x[i]=2*i;
				//row[2*i]=1; //useless
				dl[ 3*i-1 ]=1;
				dr[ n+i ] =1;
			}
			backtrack(m+1);
		}else{
			int m=n/2+1;
			for(int i=1;i<=m;i++){
				x[i]=2*i-1;
				//row[2*i]=1; //useless
				dl[ 3*i-2 ]=1;
				dr[ n+i-1 ] =1;
			}
			backtrack(m+1);
		}
	}
//---------------- 求所有解的个数  ------------------------------------
	int n,x[N],ans; //solution [1..n]
	bool row[N];
	bool dl[2*N],dr[2*N];
	//向右下的对角线，向左下的对角线
	void backtrack(int t)
	{
		if(t>n){
			ans++;
			for(int k=1;k<n;k++) printf("%d ",x[k]);
			printf("%d\n",x[n]);
			return;
		}
		for(int i=1;i<=n;i++){
			int l=i+t-1,r=n+i-t;
			if(row[i]==0&&dl[l]==0&&dr[r]==0){
				x[t]=i;
				row[i]=1;dl[l]=1;dr[r]=1;
				backtrack(t+1);
				row[i]=0;dl[l]=0;dr[r]=0;
			}
		}
	}
	void nqueen(){
		memset(row,0,N);
		memset(dr,0,2*N);
		memset(dl,0,2*N);
		ans=0;
		backtrack(1);
	}
/* 6.0-1背包问题
*/
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
/* 7.最大团问题
    最大团=最大完全子图
最大独立集=最大不相连子图
G图的最大团=G的补图的最大独立集
*/
int mat[N][N],n;
int x[N],bestx[N];//当前解,当前最优解
int cn,bestn;//当前点数,当前最大点数
void Backtrack(int i){
	if(i>n){
		for(int j=1;j<=n;j++)
			bestx[j]=x[j];
		bestn=cn;
		return;
	}
	int OK=1;
	for(int j=1;j<i;j++){
		if(x[j]&&mat[i][j]==0){
			//i,j不相连
			OK=0;
			break;
		}
	}if(OK){
		x[i]=1;
		cn++;
		Backtrack(i+1);
		x[i]=0;
		cn--;
	}
	if(cn+n-i>bestn){
		x[i]=0;
		Backtrack(i+1);
	}
}
int MaxClique(){
	cn=bestn=0;
	Backtrack(1);
	return bestn;
}
/* 8.图m着色问题
使相连边不同颜色,求最小着色数
枚举颜色数,迭代加深搜索
*/
int n,m;//点数，颜色数
bool mat[N][N];
int x[N];//可行解
bool OK(int k){
	for(int j=0;j<n;j++)
		if(mat[k][j]==1&&x[j]==x[k])
			return false;
	return true;
}
//init ans=0,x[]={0} 
bool search(int t)
{
	if(t>n){
		return true;			
	}else
		for(int i=1;i<=m;i++){
			x[t]=i;
			if(OK(t)) if(search(t+1))
				return true;
		}
	return false;
}
	for(m=1;m<10;m++){
		if(search(0))
			break;
	}
/* 9.旅行销售员问题
*/
#define NoEdge 1e99 
int n;
int	x[N],//当前解
int	bextx[N];//最优解
double mat[N][N];// [1..n]
double	cc,bestc; //当前费用，最优费用

void init(){
	cc=bestc=0;
	for(int i=1;i<n;i++)
		x[i]=i;
}
void search(int i)
{
	if(i==n){
		if(cc+mat[ x[n-1] ][ x[n] ]+mat[ x[n] ][ 1 ]<bestc||
			bestc==0){
			for(int j=0;j<n;j++)
				bestx[j]=x[j];
			bestc=cc+mat[ x[n-1] ][ x[n] ]+mat[ x[n] ][1];
		}else{
			for(int j=i;j<=n;j++)
				if(cc+mat[ x[i-1] ][ x[j] ]<bestc){
					swap(x[i],x[j]);
					cc+=mat[ x[i-1] ][ x[i] ];
					search(i+1);
					cc-=mat[ x[i-1] ][ x[i] ];
					swap(x[i],x[j]);
				}
		}
	}
}
/* 10.圆排列问题
给定n个圆的半径,将它们放在同一水平面上,
求最小总长度的圆排列
*/
double _min,//当前最优值
       x[N],//当前圆排列圆心坐标
	   r[N];//当前圆排列圆半径
int n;
double center(int t){
	//计算当前所选择圆心横坐标
	double tmp=0;
	for(int j=1;j<t;j++){
		float valuex=x[j]+2.0*sqrt(r[t]*r[j]);
		if(valuex>tmp) tmp=valuex;
	}return tmp;
}
void Compute(){
	double low=0,high=0;
	for(int i=1;i<=n;i++){
		if(x[i]-r[i]<low) low=x[i]-r[i];
		if(x[i]+r[i]>high) high=x[i]+r[i];
	}
	if(high-low<_min) _min=high-low;
}
void Backtrack(int t){
	if(t>n) Compute();
	else
		for(int j=t;j<=n;j++){
			swap(r[t],r[j]);
			double centerx=center(t);
			if(centerx+r[t]+r[1]<_min){//下界约束
				x[t]=centerx;
				Backtrack(t+1);
			}
			swap(r[t],r[j]);
		}
}
double CirclePerm(){
	_min=INF;
	Backtrack(1);
	return _min;
}
/* 11.电路板排列问题
*/
int n,m,
	x[N],bestx[N],
	bestd,//当前最优密度
	total[N],//连接块j的电路板数
	now[N],//当前解中所含连接j的电路板数
	B[N][N];//连接块数组
void Backtrack(int i,int cd){
	if(i==n){
		for(int j=1;j<=n;j++){
			bestx[j]=x[j];
		}
		bestd=cd;
	}else
		for(int j=1;j<=n;j++){
			//选择x[j]为下一块电路板
			int ld=0;
			for(int k=1;k<=m;k++){
				now[k]+=B[x[j]][k];
				if(now[k]>0&&total[k]!=now[k])
					ld++;
			}
			//更新ld
			if(cd>ld) ld=cd;
			if(ld<bestd){//搜索子树
				swap(x[i],x[j]);
				Backtrack(i+1,ld);
				swap(x[i],x[j]);
			}
			//恢复状态
			for(k=1;k<=m;k++){
				now[k]-=B[x[j]][k];
			}
		}
}
int Arrangment(){// n,m
	bestd=m+1;
	memset(total,0,sizeof(total));
	memset(now,0,sizeof(now));
	for(int i=1;i<=n;i++){
		x[i]=i;
		for(int j=1;j<=m;j++){
			total[j]+=B[i][j];
		}
	}
	Backtrack(1,0);
	return bestd;
}
/* 12.连续邮资问题
	可发行n种不同面值邮票,每张信封最多允许贴m张
	给定一种面值设计,使连续邮资区间最大([1..])
*/
// WA
int n,m,maxvalue,
	maxl,//邮资上限
	x[N],//当前解
	y[L],//贴出各种邮资所需最少邮票数
	bestx[N];//最优解
void Backtrack(int i,int r){
	for(int j=0;j<=x[i-2]*(m-1);j++)
		if(y[j]<m)
			for(int k=1;k<=m*y[j];k++)
				if(y[j]+k<y[j+x[i-1]*k])
					y[j+x[i-1]*k]=y[j]+k;
	while(y[r]<INF) r++;
	if(i>n){
		if(r-1>maxvalue){
			maxvalue=r-1;
			for(int j=1;j<=n;j++)
				bestx[j]=x[j];
			return;
		}
	}
	int z[L];
	for(int k=1;k<L;k++)
		z[k]=y[k];
	for(j=x[i-1]+1;j<=r;j++){
		x[i]=j;
		Backtrack(i+1,r);
		for(int k=1;k<L;k++){
			y[k]=z[k];
		}
	}
}
int MaxStamp(){//n,m
	maxvalue=0;
	memset(x,0,sizeof(x));
	for(int i=1;i<L;i++) y[i]=INF;
	x[1]=1;
	y[0]=0;
	Backtrack(2,1);
	return maxvalue;
}