/*
    ��̬�滮
(I)  ����
1.   Characterize the structure of an optimal solution.
	 ʶ�����Žṹ(�����ӽṹ,�޺�Ч��,�������ص�) 
2.   Recursively define the value of an optimal solution.
	 �ݹ鶨��״̬ת�Ʒ���(�׶�X״̬X����) 
3.   Compute the value of an optimal solution in a bottom-up fashion.
	 ����������� ���������¼��仯�ݹ� 
4.   Construct an optimal solution from computed information. 
	 �ع���·�� Trackback

���ֶ���:
(1)���õݹ���������ص�,���м��仯
(2)�����⿴�ɶ�׶ξ�������
**.�ݹ齨��ģ��,�������״̬ǰ��,�ʺ�˳��
 ��׶ξ��߽���ģ��,�������״̬���,�ʺ�����

�޺�Ч�Ժ��ӽṹ:����ֻȡ���ڵ�ǰ״̬����������
�����׶ξ�������,���������ӽṹ(���ž��ߵ�������Ҳ������)���޺�Ч��
����ö�̬�滮�����
��̬�滮�ĸ�Ч��Դ���������ص�

״̬��ʾ:��̬�滮�����ĺ���,״̬�Ŀɶ�����Դ�������޺�Ч��
״̬����Ϊ�涨��,����ͨ������ά��������������Ч��
Ҳ���ڱ����޺�Ч��ǰ�����޸�״̬��ʾ

״̬ת��:״̬ת�ƵĿɶ�����Դ�����������ӽṹ
�����ⲻ���������ӽṹʱ,ͨ������ά�����������
��ע��������ʹ�����ⲻ�ص�,�Ӷ���̬�滮ʧȥ����.

�㷨���Ӷ�:״̬��*������*ת�Ʒ���

����ģ��:
1.����ģ��

(II) ����
1. һάDP(״̬��Ϊһά)
�׶�:n ״̬:s ����:c
	f[0][j]=init(j)
	f[i][j]=min|max{ op(f[i-1][k]) }
	{ 0<i<n , 0<=j<s , 0<=k<c }

sample:
 ˫��ˮ������(�㵼15.1)

2. ����DP
�׶�:d=i-j ״̬:i~j ����:i~j
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
 ����������(�㵼15.2)
 ���Ŷ�����(�㵼15.5)
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
3. ��άDP
�׶�~  ״̬~ ����~

sample:
 LCS����(�㵼15.4)
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

 
