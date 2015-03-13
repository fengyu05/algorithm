/*  2761 Feed the dogs	
 * 10576K	2935MS	C++	2084B
 * fengyu05
 * ��Ŀ:����һ������Ҫ��ѯ��m�������еĵ�kСԪ�أ�
   ������m�������ǲ��ụ������ġ�

 * ����:һά����ɢ��,�߶���-���Σ��Ե�ͳ��

 * �ⷨ:��m�����䰴����˵��������ο���ÿ�����䣬
   ͬʱά��һ�����ϡ�����ĳ������[s,t]ʱ�����ڼ���
   �в��������е���ɾ�����Ѳ��ڼ������������е�����
   �룬����¼�����еĵ�kСֵ�������� m �����以��
   ����������������ÿ��������һ�μ��ϣ���һ�μ��ϡ�
	�������������ɢ�������,�������߶�����ά��������ϣ�
	��ô���롢ɾ�������kСֵ�ĸ��Ӷȶ���O(logn)����ģ�
	�ܸ��ӶȾ���O(nlogn+mlogn)��
 */

#include <iostream>
#include <algorithm>
using namespace std;
// һά����ɢ��
// segmentTree �߶���-���Σ��Ե�ͳ��
class segmentTree
{
public:
	struct node
	{
		int beg,end,cnt; // [beg,end]
		node *l,*r; // children
		node(int a,int b):beg(a),end(b),cnt(0),l(0),r(0){}
	};typedef node* link;
	link root;
	segmentTree(int a,int b){root=build(a,b);}

	link build(int a,int b){
		link p=new node(a,b);
		if(b>a){			
			p->l=build(a,(a+b)/2);
			p->r=build((a+b)/2+1,b);
		}
		return p;
	}
	void update(int p,int val=1,link x=0){
		// val=1: insert val=-1: remove
		if(x==0) x=root;
		if(p<= x->end && p>= x->beg) x->cnt+=val;
		if(x->end > x->beg){
			int mid=(x->beg+x->end)/2;
			if(p<=mid) update(p,val,x->l);
			else update(p,val,x->r);
		}
	}
	int query(int nth,link x=0){// return the nth point 
		if(x==0) x=root;       // in the tree
		if(x->beg == x->end) return x->beg;
		if(nth<= x->l->cnt) return query(nth,x->l);
		else return query(nth-x->l->cnt,x->r);
	}
};
#define N 100002
#define M 50000

int a[M],b[M],nth[M],p[M],re[M];
bool cmp(int x,int y){ return a[x]<a[y];}

int og[N]; //ԭ����
int d_og[N];//��ɢ��������
int d_to_og[N];//��ɢ������ԭֵ��
int ord[N];//ԭ�����������
bool cmp2(int x,int y){ return og[x]<og[y]; }

int main()
{	
	int n,m,i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d",&og[i]);
		d_to_og[i]=og[i];
		ord[i]=i;
	}
	sort(d_to_og+1,d_to_og+n+1);
	sort(ord+1,ord+n+1,cmp2);
	for(i=1;i<=n;i++){
		// ord[x]=y => d_og[y]=x
		d_og[ ord[i] ]=i;
	}
	for(i=0;i<m;i++){
		scanf("%d%d%d",&a[i],&b[i],&nth[i]);
		p[i]=i;
	}
	sort(p,p+m,cmp);
	segmentTree st(1,n);
	int ss=a[p[0]],tt=b[p[0]];
	for(i=ss;i<=tt;i++){
		st.update(d_og[i]);
	}
	re[p[0]]=st.query(nth[p[0]]);
	for(i=1;i<m;i++){
		for(j=ss;j<a[p[i]];j++)
			st.update(d_og[j],-1);
		for(j=tt+1;j<=b[p[i]];j++)
			st.update(d_og[j],1);
		re[p[i]]=st.query(nth[p[i]]);
		ss=a[p[i]];
		tt=b[p[i]];
	}
	for(i=0;i<m;i++){
		printf("%d\n",d_to_og[re[i]]);
	}
	return 0;
}