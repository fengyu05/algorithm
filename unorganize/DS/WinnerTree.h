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
		//��ײ��ⲿ�ڵ�ı���
		for (i = 2; i <= LowExt; i += 2)
			play( (offset+i)/2, i-1, i, winner);
		//���������ⲿ�ڵ�
		if (n % 2) {	//��n����ʱ���ڲ��ڵ���ⲿ�ڵ�ı���
			play(n/2 , t[n-1],LowExt+1,winner);
			i = LowExt+3;
		}else
			i = LowExt+2;
		// iΪ����ʣ��ڵ�
		for (; i <= n; i += 2)
			play((i-LowExt+n-1)/2, i-1,i, winner);
	}
	int Winner()  const {return (n) ? t[1] : 0;}
	int Winner(int i) const {return (i < n) ? t[i] : 0;}
	void RePlay(int i, int(*winner) (T a[], int b, int c))
	{
		int p,lc,rc; // p and children
		//�ҵ���һ�������ڵ㼰����Ů
		if (i <= LowExt) {//����ײ㿪ʼ
			p = (offset + i)/2;
			lc = 2*p - offset; // p������
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
		//ʣ��ڵ�ı���
		p /= 2;  //�Ƶ����ڵ㴦
		for (; p >= 1; p /= 2)
			t[p] = winner(e, t[2*p], t[2*p+1]);
	}
private:
	int MaxSize; 
	int n;      //��ǰ��С
	int LowExt;  //��ײ���ⲿ�ڵ�
	int offset;  //2^k-1
	int *t;      //Ӯ��������
	T *e;        //Ԫ������
	void play(int p, int lc, int rc, int(*winner)(T a[], int b, int c))
	{
		t[p] = winner(e, lc, rc);
		//�����Һ��Ӵ���������жೡ����
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
{	// avail[]Ϊ���ӵ�ʣ������
	// nΪ��Ʒ������s[]Ϊ����Ʒ����Ҫ�Ŀռ�
	WinnerTree<int> W(n);
	W.Initialize(avail, n, winner);
	//����Ʒ����������
	for (int i = 1; i <= n; i++) {//��s [i]�����㹻�����ĵ�һ������
		int p=2; //�Ӹ�����������ʼ��ѯ
		while (p<n) {
			int winp = W.Winner( p ) ;
			if (avail[winp] < s[i]) p++ ;//��һ����������������				
			p *= 2; 
		}
		p /= 2;

		int b;		
		if (p < n) {//��һ���ڵ㴦
			b = W.Winner ( p ) ;
			//��b���Һ��ӣ���Ҫ�������b - 1��
			//��ʹb�����ӣ����ּ��Ҳû��ʲô������
			if (b > 1 && avail[b-1] >= s[i]) b--;
		}else //��nΪ����ʱ
			b = W.Winner (p/2) ;
		std::cout << "Pack object " << i << " in bin " << b << "\n";
		avail[b] -= s[i]; //���¿�������
		W.RePlay(b, winner);
	}
}