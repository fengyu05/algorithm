#define NULLKEY -1
#define L 7
#define M 3

typedef int Item;

struct BucketNode{
	Item KeyData[M];
	BucketNode* nxt;
};
typedef BucketNode* Link;
BucketNode Bucket[L];

void init(){
	for(int i=0;i<L;i++){
		for(int k=0;k<M;k++){
			Bucket[i].KeyData[k]=NULLKEY;
		}
		Bucket[i].nxt=0;
	}
}
int Hash(Item& x){ return x%L;}
int Inset(Item x){
	int dex=Hash(x),i;
	for(i=0;i<M;i++){
		if(Bucket[dex].KeyData[i]==NULLKEY){
			Bucket[dex].KeyData[i]=x;
			break;
		}
	}
	if(i<M) return 0;
	Link front=&Bucket[dex] , t=Bucket[dex].nxt;
	if(t!=NULL){
		while(t!=NULL){
			for(int k=0;k<M;k++){
				if(t->KeyData[i]==NULLKEY){
					t->KeyData[i]=x;
					break;
				}
				front=t;
				if(k==M) t=t->nxt;
				else break;
			}
		}
	}else{
		Link s=new BucketNode;
		if(!s) return -1;
		for(int k=0;k<M;k++){
			s->KeyData[k]=NULLKEY;
		}
		s->KeyData[0]=x;
		t->nxt=s;		
	}
	return 0;
}