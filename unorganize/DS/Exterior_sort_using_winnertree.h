#include <iostream>
#include <algorithm>

#define N 16
#define M 16
#define INF 100000000
template<class T> class WinnerTree {
#define MaxSize 256
private:
	int n;      //当前大小
	int LowExt;  //最底层的外部节点
	int offset;  //2^k-1
	int t[MaxSize];      //赢者树数组
	T *e;        //元素数组

	int winner(int b,int c){
		if(e[c]<e[b]) return c;
		else return b;		
	}
	void play(int p, int lc, int rc)
	{
		t[p] = winner( lc, rc);
		//若在右孩子处，则可能有多场比赛
		while (p > 1 && p % 2) {
			t[p/2] = winner( t[p-1], t[p]);
			p /= 2; 
		}
	}

public:
	void Initialize(T a[], int size)
	{	// constrain: 1<size<Maxsize
		n = size;
		e = a;
		int i, s;
		for (s = 1; 2*s <= n-1; s += s);//s = 2^log (n-1)
		LowExt = 2*(n-s);
		offset = 2*s-1;
		//最底层外部节点的比赛
		for (i = 2; i <= LowExt; i += 2)
			play( (offset+i)/2, i-1, i);
		//处理其余外部节点
		if (n % 2) {	//当n奇数时，内部节点和外部节点的比赛
			play(n/2 , t[n-1],LowExt+1);
			i = LowExt+3;
		}else
			i = LowExt+2;
		// i为最左剩余节点
		for (; i <= n; i += 2)
			play((i-LowExt+n-1)/2, i-1,i);
	}
	int Winner()  const {return (n) ? t[1] : 0;}
	int Winner(int i) const {return (i < n) ? t[i] : 0;}
	void RePlay(int i)
	{
		int p,lc,rc; // p and children
		//找到第一个比赛节点及其子女
		if (i <= LowExt) {//从最底层开始
			p = (offset + i)/2;
			lc = 2*p - offset; // p的左孩子
			rc = lc+1; 
		}
		else {
			p = (i-LowExt+n-1)/2;
			if (2*p == n-1) {
				lc = t[2*p];
				rc = i;
			}else {
				lc = 2*p - n + 1 + LowExt;
				rc = lc+1;
			}
		}
		t[p] = winner(lc, rc);
		//剩余节点的比赛
		p /= 2;  //移到父节点处
		for (; p >= 1; p /= 2)
			t[p] = winner(t[2*p], t[2*p+1]);
	}
};


int b[N][M];
int val[N],pos[N];
int main()
{
#ifndef ONLINE_JUDGE
  	freopen("t.in", "r", stdin);
#endif
	int n,m,i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		for(j=0;j<m;j++)
			scanf("%d",&b[i][j]);
		b[i][j]=INF;
	}
	for(i=1;i<=n;i++){
		std::sort(b[i],b[i]+m);
		val[i]=b[i][0];
		pos[i]=0;
	}
	// val[1..n]
	int cnt=n*m;
	WinnerTree<int> wt;
	wt.Initialize(val, n);
	while(cnt){
		int dex=wt.Winner();
		printf("[ %d ] ",val[dex]);
		pos[dex]++;
		val[dex]=b[dex][ pos[dex] ];
		wt.RePlay(dex);
		cnt--;
	}
	return 0;
}
