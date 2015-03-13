#include <iostream>
#include <deque>
#include <algorithm>
#include <ctime>
using namespace std;
/* short path using adj-list
  * Dijkstra , BellmanFord 
  * with careful test	
  * fengyu
  * lately edit:3.16 2008
*/
#define N 100000
#define INF 1e99
#define min(a,b) (a<b?a:b)
struct Node
{	int id;
	double val;
	Node* next;
	Node(int id,double val,Node *next=0)
		:id(id),val(val),next(next){}
}; typedef Node* link;
link adj[N];
void insert(int x,int id,double val){
	adj[x]=new Node(id,val,adj[x]);
}
void init(int n){
	memset(adj,0,n*sizeof(link));
}
bool edge(int x,int y){
	for(link lk=adj[x];lk;lk=lk->next)
		if(lk->id==y) return true;
	return false;
}
void print(int n){
	for(int i=0;i<n;i++){
		printf(" %d :",i);
		for(link t=adj[i];t;t=t->next){
			printf(" %d [%5.2lf]",t->id,t->val);
		}
		printf("\n");
	}
}
int e_cnt;
double dist[N];
int pred[N];
//-------------- Dijkstra ----------------//O(n^2)
//*0 单源短路 
//*1 不允许负边
//*2 多重边存在时，只保留最短边
void Dijkstra(int s,int n)
{
	bool flag[N]={0};
	for(int i=0;i<n;i++){
		dist[i]=INF;
		pred[i]=-1;
	}
	dist[s]=0,pred[s]=s;
	for(int k=0;k<n;k++){
		double val=INF;
		int dex=-1;
		for(int j=0;j<n;j++)
			if(!flag[j] && val>dist[j])
				dex=j,val=dist[j];			
		if(dex==-1) return;
		flag[dex]=true;
		for(link lk=adj[dex];lk;lk=lk->next){
			int id=lk->id;
			double val=lk->val;
			if(!flag[id] && dist[id]>dist[dex]+val){
				dist[id]=dist[dex]+val;
				pred[id]=dex;
			}
		}
	}
}
void showpath(int e){
	if(pred[e]!=e&&pred[e]!=-1){
		showpath(pred[e]);
		printf("-->%d",e);
	}else
		printf("%d",e);
}
//(II) Heap implementation O(n^2/logn)
struct Item{ 
	int id;
	double val;
	Item(int id=0,double val=0):val(val),id(id){}
} hp[N];
bool operator<(Item& a,Item &b){ return a.val > b.val;}
void heap_Dij(int s,int n){ // slow than Dijkstra
	for(int i=0;i<n;i++){
		hp[i].id=i;
		hp[i].val=dist[i]=INF;
	}
	hp[i].val=dist[s]=0;
	make_heap(hp,hp+n);
	while(n>0){
		pop_heap(hp,hp+n--);
		int dex=hp[n].id;
		bool flag[N]={0};
		double tmp[N];
		for(int j=0;j<n;j++) tmp[j]=INF;
		for(link lk=adj[dex];lk;lk=lk->next){
			tmp[lk->id]=lk->val;
			flag[lk->id]=true;
		}
		for(int i=0;i<n;i++){
			int id=hp[i].id;
			if(flag[id]&&dist[id]>dist[dex]+tmp[id]){
				hp[i].val=dist[id]=dist[dex]+tmp[id];
				push_heap(hp,hp+i+1);//(***)
			}
		}
	}
}
//-----------------shortest path for DAG ---------------
// step1: tpsort ,step2: scan  //O(n+m)
void spDAG(int s,int n){
	//step 1;
	int ord[N],in[N]={0};
	int i,front=-1,rear=-1;
	for(i=0;i<n;i++)
		for(link lk=adj[i];lk;lk=lk->next)
			in[lk->id]++;
	for(i=0;i<n;i++) if(in[i]==0) ord[++rear]=i;
	while(front<rear){
		int v=ord[++front];
		for(link lk=adj[v];lk;lk=lk->next){
			int id=lk->id;
			if(--in[id]==0)
				ord[++rear]=id;
		}
	}
	//step 2;
	for(i=0;i<=n+1;i++){
		dist[i]=INF;
	}
	dist[s]=0;
	for(i=0;i<n;i++){
		if(ord[i]==s) break;
	}
	for(i;i<n;i++){
		int cur=ord[i];
		for(link lk=adj[cur];lk;lk=lk->next){
			int id=lk->id;
			double val=dist[cur]+lk->val;
			if(val<dist[id]) dist[id]=val;
		}
	}
}
// --------------  BellmanFord -----------------
//*0 单源最短  
//*1 允许负边 负环检测
void Bellman(int s,int n){
	deque<int> que; // make sure large enough	
	int cnt=0;
	for(int i=0;i<n;i++) dist[i]=INF;
	dist[s]=0 ; pred[s]=s;//[*] root
	que.push_back(s),que.push_back(-1);// -1 for mark				
	while(que.size()){
		int dex=que.front();
		que.pop_front();
		if(dex==-1){
			if(cnt++>n) return;
			que.push_back(dex);
		}else{
			for(link lk=adj[dex];lk;lk=lk->next){
				int id=lk->id;
				double val=lk->val;
				if(dist[id]>dist[dex]+val){
					dist[id]=dist[dex]+val;			
					que.push_back(id);			
					pred[id]=dex;//[*]
				}
			}
		}
	}
}
bool iscycle(int n){//负环检测
	for(int i=0;i<n;i++){
		bool flag[N]={0};
		int p=i;
		while(p!=pred[p]){
			flag[p]=1;
			p=pred[p];
			if(flag[p]==1)
				return true;
		}
	}
	return false;
}
//-------------- test -----------------------------
void ran_list(int n,int m){
	while(m--){
		int a=n*rand()/RAND_MAX,b=n*rand()/RAND_MAX;
		int c=100*rand()/RAND_MAX;
		if(a!=b&&c!=0){
			if(!edge(a,b)){//不允许多重边
				e_cnt++;
				insert(a,b,c);
			}
		}
	}
}
void ran_dag(int n,int m){
	while(m--){
		int a=n*rand()/RAND_MAX,b=n*rand()/RAND_MAX;
		int c=100*rand()/RAND_MAX;
		if(a>b) swap(a,b);
		if(a!=b&&c!=0){
			if(!edge(a,b)){//不允许多重边
				e_cnt++;
				insert(a,b,c);
			}
		}
	}
}
void gen_test(int n,int m){
	init(n);
	e_cnt=0;
	//ran_list(n,m);
	ran_dag(n,m);
	printf("%d Edges\n",e_cnt);
	//print(n);
	double re_i,re_ii;
	int s=0,t=n-1,ss;
	//----------- test 1 ------------------
			ss = clock(); 
	Dijkstra(s,n);
			printf("%f\n", (double)(clock()-ss)/1000); 
	re_i=dist[t];
	showpath(t); printf("\n");
	//----------- test 2 ------------------
			ss = clock();
	//heap_Dij(s,n);
	//Bellman(s,n);
	spDAG(s,n);
			printf("%f\n", (double)(clock()-ss)/1000); 
	re_ii=dist[t];
	showpath(t); printf("\n");
	//------------------------------------------------
	printf("%d -> %d : %5.0lf %5.0lf\n",
		s,t,re_i,re_ii);
	if(re_i==re_ii)
		printf("Success!!\n");
	else{
		printf("Fail!\n");
		system("pause");
	}
}
int main()
{
	int test_cas=10;
	while(test_cas--){
		gen_test(50000,200000);
	}
	return 0;
}
