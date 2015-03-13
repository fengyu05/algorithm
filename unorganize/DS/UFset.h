#define maxN 10240
class UFset //并查集:rank启发式合并,路径压缩
{
public:
	int p[maxN],r[maxN];
	UFset(int n){
		for(int i=0;i<n;i++){
			p[i]=i;
			r[i]=0;
		}
	}
	int find(int x){
		int t=x;
		while(t!=p[t]) t=p[t];
		while(x!=p[x]){int tmp=p[x];p[x]=t;x=tmp;}
		return t;
	}
	void Union(int x,int y){
		x=find(x),y=find(y);
		if(r[x]>r[y]) p[y]=x;
		else p[x]=y;
		if(r[x]==r[y]) r[y]++;
	}
};

// extend for UFset
int p[maxN],e[maxN],front[maxN]; 
// p[] is p-link is mark the size *(-)									  
// e[] is for diff()
// front[] is for find2 & Movefront()
// record howmany element is in front of x
void UFset(int n){
	memset(p,-1,n*sizeof(int)); 
	//memset(e,-1,n*sizeof(int));
	//memset(front,0,n*sizeof(int));
}
int find(int x){
	int t=x;
	while(p[t]>0) t=p[t];
	while(x!=t){int tmp=p[x];p[x]=t;x=tmp;}
	return t;
}
void Union(int x,int y){
	x=find(x),y=find(y);
	if(x==y) return;
	if(p[x]<p[y])	p[x]+=p[y],p[y]=x;
	else	p[y]+=p[x],p[x]=y;
}
int size(int x){ return -p[find(x)];}
//
void diff(int x,int y){
	int a=find(x),b=find(y);
	if(e[a]!=-1) p[e[a]]=b;
	e[a]=b;
	if(e[b]!=-1) p[e[b]]=a;
	e[b]=a;
}
//
int find2(int x){
	int t=x;
	while(p[t]>0) t=p[t];
	while(x!=t){
		int tmp=p[x];
		p[x]=t;
		int j=tmp;
		do{//迭代求出路径上每一个子结点相对于r的相对位置 
             front[x]+=front[j];
             j=p[j];
           }while(j>0);
		x=tmp;
	}
	return t;
}
void Movebehind(int a,int b) //mova a behind b
{	
	a=find2(a),b=find2(b);
	if(a==b) return;
	int num=-p[a]; // size of a
	p[a]=b;
	front[a]=-p[b];//计算a的相对位置为 size of b 
	p[b]-=num; //计算新集合的结点数 
}

void makeset(int x){ rank[x] = 0; p[x]=x; }
int findset(int x){
	int i, px= x;
	while (px!= p[px]) px= p[px]; 
	while (x != px) { i = p[x]; p[x] = px; x = i; }
	return px;
}
void unionset(int x , int y){
	x = findset(x); y = findset(y);
	if(rank[x] > rank[y]) p[y] = x;
	else { p[x] = y; if(rank[x] == rank[y]) rank[y]++; }
}
