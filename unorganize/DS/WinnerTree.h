template<class T>
class WinnerTree {
public:
	WinnerTree(int m = 10):MaxSize(m),t(new int[m]),n(0){}
	~WinnerTree() {delete [] t;}
	void Initialize(T a[], int size, int(*winner)(T a[], int b, int c))
	{	// constrain: 1<size<Maxsize
		n = size;
		e = a;
		int i, s;
		for (s = 1; 2*s <= n-1; s += s);//s = 2^log (n-1)
		LowExt = 2*(n-s);
		offset = 2*s-1;
		//最底层外部节点的比赛
		for (i = 2; i <= LowExt; i += 2)
			play( (offset+i)/2, i-1, i, winner);
		//处理其余外部节点
		if (n % 2) {	//当n奇数时，内部节点和外部节点的比赛
			play(n/2 , t[n-1],LowExt+1,winner);
			i = LowExt+3;
		}else
			i = LowExt+2;
		// i为最左剩余节点
		for (; i <= n; i += 2)
			play((i-LowExt+n-1)/2, i-1,i, winner);
	}
	int Winner()  const {return (n) ? t[1] : 0;}
	int Winner(int i) const {return (i < n) ? t[i] : 0;}
	void RePlay(int i, int(*winner) (T a[], int b, int c))
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
		t[p] = winner(e, lc, rc);
		//剩余节点的比赛
		p /= 2;  //移到父节点处
		for (; p >= 1; p /= 2)
			t[p] = winner(e, t[2*p], t[2*p+1]);
	}
private:
	int MaxSize; 
	int n;      //当前大小
	int LowExt;  //最底层的外部节点
	int offset;  //2^k-1
	int *t;      //赢者树数组
	T *e;        //元素数组
	void play(int p, int lc, int rc, int(*winner)(T a[], int b, int c))
	{
		t[p] = winner(e, lc, rc);
		//若在右孩子处，则可能有多场比赛
		while (p > 1 && p % 2) {
			t[p/2] = winner(e, t[p-1], t[p]);
			p /= 2; 
		}
	}
};
int winner(int a[],int b,int c){
	if(a[c]>a[b]) return c;
	else return b;		
}
void FirstFitPack(int s[], int n,int avail[])
{	// avail[]为箱子的剩余容量
	// n为物品数量，s[]为各物品所需要的空间
	WinnerTree<int> W(n);
	W.Initialize(avail, n, winner);
	//将物品放入箱子中
	for (int i = 1; i <= n; i++) {//将s [i]放入足够容量的第一个箱子
		int p=2; //从根的左子树开始查询
		while (p<n) {
			int winp = W.Winner( p ) ;
			if (avail[winp] < s[i]) p++ ;//第一个箱子在右子树中				
			p *= 2; 
		}
		p /= 2;

		int b;		
		if (p < n) {//在一树节点处
			b = W.Winner ( p ) ;
			//若b是右孩子，需要检查箱子b - 1。
			//即使b是左孩子，这种检查也没有什么副作用
			if (b > 1 && avail[b-1] >= s[i]) b--;
		}else //当n为奇数时
			b = W.Winner (p/2) ;
		std::cout << "Pack object " << i << " in bin " << b << "\n";
		avail[b] -= s[i]; //更新可用容量
		W.RePlay(b, winner);
	}
}