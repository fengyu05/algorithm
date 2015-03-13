/*  3321-Apple Tree
 *  8236K	357MS	C++	1615B
 *  fengyu05
 *  给出一棵广义树,动态修改节点上的数值(0-1),询问各节点上的子树的数值和
 *  tip:If we label the forks with their DFS-visit-time,
 then a sub-tree is a consecutive interval of labels. 
 Then we can use segment-tree or tree array to handle it.
 */
#include <iostream>
using namespace std;
#define N 100004
#define M 131072
struct node
{	int u;
	node* next;
	node(int u,node *next=0):u(u),next(next){}
}; typedef node* link;

link adj[N];
int n;
void insert(int x,int y){adj[x]=new node(y,adj[x]);}
int pre[N],post[N];
int ord;
void dfs(int u){// dfs 记录进入时间pre[],和离开时间post[]
	pre[u]=++ord;
	bool vis=false;
	for(link lk=adj[u];lk;lk=lk->next){
		int vec=lk->u;
		if(pre[vec]==0){
			dfs(vec);
			vis=true;
		}
	}
	post[u]=ord;
}
bool ap[N];
class treeA{
public:
	int c[M]; // M must be the power of 2
	int lowBit(int x) {
		return x & (x ^ (x - 1));
	}
	void add(int x, int k) { // k can be negative 
		// a[x] += k
		while (x <= M) {
			c[x-1] += k;
			x += lowBit(x);
		}
	}
	int query(int x) {// sum:a[1..x];
		int ret = 0;
		while (x > 0) {
			ret += c[x-1];
			x -= lowBit(x);
		}
		return ret;
	}
	void init(){
		memset(c,0,sizeof(c));
	}
} A;
int main()
{	
	scanf("%d",&n);
	int i,x,y,m;
	for(i=0;i<n-1;i++){ 
		scanf("%d%d",&x,&y);
		insert(x,y),insert(y,x);
	}
	memset(pre,0,sizeof(int)*(n+1));
	ord=0;
	dfs(1);
	A.init();
	for(i=1;i<=n;i++){
		ap[i]=true;
		A.add(pre[i],1);
	}
	scanf("%d\n",&m);
	char ch;
	while(m--){
		scanf("%c%d\n",&ch,&x);
		if(ch=='C'){
			if(ap[x]){//has apple
				ap[x]=false;
				A.add(pre[x],-1);
			}else{
				ap[x]=true;
				A.add(pre[x],1);
			}
		}else{			
			int a=pre[x],b=post[x];
			if(a==1){
				printf("%d\n",A.query(b));
			}else{
				printf("%d\n",A.query(b)-A.query(a-1));
			}
		}
	}
	return 0;
}