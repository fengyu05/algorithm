#include <iostream>
#include <algorithm> 
using namespace std;

#define N 128

struct Hnode{
	char ch;
	int weight;
	int p,l,r;
};
Hnode Ht[2*N];
char **Hc;

template<class Item>class Heap{
public:
	Item heap[2*N];
	int n;
	int size(){return n;}
	void init(){n=0;}
	void push(Item x){
		heap[n++]=x;
		push_heap(heap,heap+n);
	}
	Item pop(){
		pop_heap(heap,heap+n);
		return heap[--n];
	}
};
struct nd{
	int id,w;
	nd(int id=0,int w=0):id(id),w(w){}
};
bool operator<(nd& a,nd& b){ return a.w>b.w;}
Heap<nd> pq;
int CreateTree(char c[],int w[],int n)
{
	int i,s1,s2;
	if(n<=1) return 0;
	pq.init();
	for(i=1;i<=n;i++){
		Ht[i].ch=c[i-1];
		Ht[i].weight=w[i-1];
		pq.push(nd(i,Ht[i].weight));
	}
	for(i=1;i<2*n;i++)
		Ht[i].p=Ht[i].l=Ht[i].r=0;
	// construct Huffman Tree
	for(i=n+1;i<2*n;i++){
		// 选取p==0,wieght最小的两棵树
		s1=pq.pop().id;
		s2=pq.pop().id;
		Ht[s1].p=Ht[s2].p=i;
		Ht[i].l=s1;
		Ht[i].r=s2;
		Ht[i].weight=Ht[s1].weight+Ht[s2].weight;
		pq.push(nd(i,Ht[i].weight));
	}
	return i-1;// return root
}
void LeafCode(int root,int n)
{
	int i,p=root,cdlen=0;
	char code[N];
	Hc=new char*[n+1];
	for(i=1;i<=p;i++)
		Ht[i].weight=0;
	while(p){
		if(Ht[p].weight==0){
			Ht[p].weight=1;
			if(Ht[p].l!=0){
				p=Ht[p].l;
				code[cdlen++]='0';
			}
			else if(Ht[p].r==0){
				Hc[p]=new char[cdlen+1];
				code[cdlen]=0;
				strcpy(Hc[p],code);
			}
		}else if(Ht[p].weight==1){
			Ht[p].weight=2;
			if(Ht[p].r!=0){
				p=Ht[p].r;
				code[cdlen++]='1';
			}
		}else{
			Ht[p].weight=0;
			p=Ht[p].p;
			--cdlen;
		}
	}
}
char Decode(char *buff,int root){
	int pre=root,p;
	while(*buff){// *buff!=0
		p=root;
		while(p){
			pre=p;
			if(*buff=='0') p=Ht[p].l;
			else p=Ht[p].r;
			buff++;
		}
		buff--;
	}
	return Ht[pre].ch;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	char c[]={'a','b','c','d'};
	int w[]={2,7,4,5};
	int n=4;
	// construct the code tree
	int root=CreateTree(c,w,n);
	// list the code table
	LeafCode(root,n);
	// show
	for(int i=1;i<=n;i++){
		printf("%s\n",Hc[i]);
	}
	// query
	printf("%c\n",Decode("111",root));
	return 0;
}