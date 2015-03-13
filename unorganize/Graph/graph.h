// adj-list use link
struct node
{	int id;
	node* next;
	node(int id,node *next=0):id(id),next(next){}
}; typedef node* link;
link adj[N];
void insert(int x,int y){adj[x]=new node(y,adj[x]);}
// travel
for(link lk=adj[i];lk;lk=lk->next){//(**) make sure i here refer correctly
	int id=lk->id;
}
bool edge(int x,int y){
	for(link lk=adj[x];lk;lk=lk->next)
		if(lk->id==y) return true;
	return false;
}
void remove(int x,int y){
	for(link lk=adj[x],p=0;lk;p=lk,lk=lk->next){
		if(lk->id== y){
			if(p) p->next=lk->next;
			else adj[x]=lk->next;
			delete lk;
			return;
		}
	}
}
void free(link l){
	if(l->next) free(l->next);
	delete l;
}
void print(int n){
	for(int i=1;i<=n;i++){
		printf(" %d :",i);
		for(link lk=adj[i];lk;lk=lk->next){
			printf(" %d",lk->id);
		}
		printf("\n");
	}
}
// use vector
typedef vector<int> vi;
#define rep(i,n) for(i=0;i<n;i++)
#define forr(i,a,b) for(i=a;i<=b;i++)
#define pb push_back
#define N 1000000
vi adj[N];
