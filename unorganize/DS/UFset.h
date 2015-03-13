#define maxN 10240
class UFset //���鼯:rank����ʽ�ϲ�,·��ѹ��
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
		do{//�������·����ÿһ���ӽ�������r�����λ�� 
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
	front[a]=-p[b];//����a�����λ��Ϊ size of b 
	p[b]-=num; //�����¼��ϵĽ���� 
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
