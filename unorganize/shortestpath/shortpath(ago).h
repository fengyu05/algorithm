#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

/* short path using adj-matrix
  * base algorithm
  * Dijkstra , BellmanFord , Floyd
  * with careful test	
  * fengyu
  * 12.13 2007
*/
#define N 3000
#define INF 1e99//int时切勿用0x7fffffff(算法中使用了+)
double mat[N][N];//mat[0..n)[0..n)
double dist[N];
int pred[N];

//-------------- Dijkstra ----------------------------------------------
//*0 单源短路 
//*1 多重边存在时，只保留最短边
//*2 不允许负边
//*3 use INF for edge not exist
//(I) primary Dijkstra O(n^2)
void primary_Dij(int s,int n)
{
	bool flag[N]={0};
	for(int i=0;i<n;i++){
		dist[i]=mat[s][i];
		pred[i]=s;
	}
	flag[s]=true,dist[s]=0;
	for(int k=0;k<n;k++){
		double val=INF;
		int dex=-1;
		for(int j=0;j<n;j++)
			if(!flag[j] && val>dist[j])
				dex=j,val=dist[j];			
		if(dex==-1) return;
		flag[dex]=true;
		for(int i=0;i<n;i++)
			if(!flag[i] && dist[i]>dist[dex]+mat[dex][i]){
				dist[i]=dist[dex]+mat[dex][i];
				pred[i]=dex;
			}
	}
}
//(II) Heap implementation O(n^2/logn)
struct Node{ 
	int id;
	double val;
	Node(int id=0,double val=0):val(val),id(id){}
};
bool operator<(Node& a,Node &b){ return a.val > b.val;}
void heap_Dij(int s,int n){ // best performance in large n
	Node hp[N];
	for(int i=0;i<n;i++){
		hp[i].val=dist[i]=mat[s][i];
		hp[i].id=i;
		pred[i]=s;
	}
	dist[s]=0;
	make_heap(hp,hp+n);
	while(n>0){
		pop_heap(hp,hp+n);
		n--;
		int dex=hp[n].id;
		for(int i=0;i<n;i++){
			int id=hp[i].id;
			if( dist[id]>dist[dex]+mat[dex][id]){
				hp[i].val=dist[id]=dist[dex]+mat[dex][id];
				pred[id]=dex;
				push_heap(hp,hp+i+1);//(***)
			}
		}
	}
}
void showpath(int e){
	if(pred[e]!=e){
		showpath(pred[e]);
		printf("- [%.2lf] ->%d",mat[pred[e]][e],e);
	}else
		printf("%d",e);
}
//(III) Dijkstra的变种
//(a) 求最大最短的路径
//* init mat[][] with 0 
double min(double a,double b){ return a<b?a:b;}
void maxminpath(int s,int n)
{
	bool flag[N]={0};
	for(int i=0;i<n;i++){
		dist[i]=mat[s][i];
		pred[i]=s;
	}
	flag[s]=true,dist[s]=0;
	for(int k=0;k<n;k++){
		double val=0;
		int dex=-1;
		for(int j=0;j<n;j++)
			if(!flag[j] && val<dist[j])
				dex=j,val=dist[j];			
		if(dex==-1) return;
		flag[dex]=true;
		for(int i=0;i<n;i++)
			if(!flag[i] && dist[i]<min(dist[dex],mat[dex][i])){
				dist[i]=min(dist[dex],mat[dex][i]);
				pred[i]=dex;
			}
	}
}
//(b) 求最小最长的路径
//* init mat[][] with INF
double max(double a,double b){ return a>b?a:b;} 
void minmaxpath(int s,int n)
{
	bool flag[N]={0};
	for(int i=0;i<n;i++){
		dist[i]=mat[s][i];
		pred[i]=s;
	}
	flag[s]=true,dist[s]=0;
	for(int k=0;k<n;k++){
		double val=INF;
		int dex=-1;
		for(int j=0;j<n;j++)
			if(!flag[j] && val>dist[j])
				dex=j,val=dist[j];			
		if(dex==-1) return;
		flag[dex]=true;
		for(int i=0;i<n;i++)
			if(!flag[i] && dist[i]>max(dist[dex],mat[dex][i])){
				dist[i]=max(dist[dex],mat[dex][i]);
				pred[i]=dex;
			}
	}
}
// --------------  BellmanFord -----------------
// label-correcting algorithm O(nm)
//*0 单源最短  
//*1 允许负边 负环检测
void Bellman(int s,int n){
	deque<int> que; // make sure large enough	
	int cnt=0;
	for(int i=0;i<n;i++) dist[i]=INF;
	dist[s]=0 ; pred[s]=s;//[*] root
	que.push_back(s),que.push_back(-1);// -1 for mark				
	while(que.size()){
		int v=que.front();
		que.pop_front();
		if(v==-1){
			if(cnt++>n) return;
			que.push_back(v);
		}else{
			for(int i=0;i<n;i++)
				if(dist[i]>dist[v]+mat[v][i]){
					dist[i]=dist[v]+mat[v][i];			
					que.push_back(i);			
					pred[i]=v;//[*]
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
// --------------- Floyd --------------------
//*0 全源短路
//*1 允许负边 负环检测
//*2 use INF for edge not exist
//*3 return false when negative cycle exist
double dis[N][N];
bool Floyd(int n) 
{
	int i,j,k;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			dis[i][j]=mat[i][j];
		}
	}
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			for(k=0;k<n;k++)
				if(dis[j][i]+dis[i][k]<dis[j][k]){
					dis[j][k]=dis[j][i]+dis[i][k];
				}
	for(i=0;i<n;i++)
		if(dis[i][i]<0) return false;
	return true;
}
//---------------- test --------------------------------------
void init(int n){
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			mat[i][j]=INF;
}
void print(int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			printf("%5.0lf",mat[i][j]);
		} printf("\n");
	}
}
void ran_mat(int n){
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			if(i==j) mat[i][j]=0;
			else{
				mat[i][j]=(double)rand()*10000/RAND_MAX;
			}
		}
}
void gen_test(int n){
	ran_mat(n);
	//print(n);
	double re_i,re_ii;
	int s=n*rand()/RAND_MAX;
	int t=n*rand()/RAND_MAX;
	// test 1
	primary_Dij(s,n);
	re_i=dist[t];
	showpath(t); printf("\n");
	// test 2
	heap_Dij(s,n);
	re_ii=dist[t];
	printf("%d -> %d : %5.0lf %5.0lf\n",
		s,t,re_i,re_ii);
	if(re_i==re_ii)
		printf("Success!!\n");
	else{
		printf("Fail!\n");
		system("pause");
	}
}
void negarc_test(int n){
	ran_mat(n);
	print(n);
	int s=n*rand()/RAND_MAX;
	Bellman(s,n);
	if(iscycle(n)){
		printf("Negative Cycle exist!\n");
	}else{
		printf("No negative Cycle!\n");
		Floyd(n);
		for(int j=0;j<n;j++){
			if(dis[s][j]!=dist[j]){
				printf("Error!");
				system("pause");
				break;
			}
		}
	}
}
int main()
{
	int test_cas=10;
	while(test_cas--){
		gen_test(3000);
	}
	return 0;
}
