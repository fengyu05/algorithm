typedef sel Item;

struct llinkNode{
	Item key;
	llinkNode* next;
	int cnt;
	llinkNode(Item k,llinkNode* nxt=0):key(k),next(nxt){cnt=1;}
};
typedef llinkNode* llink;
llink Hash[L];

void init(){
	_clr(Hash);
}
void putin(Item x){
	int dex=x;
	if(Hash[dex]==0){
		Hash[dex]=new llinkNode(x);
	}else{
		llink ptr=Hash[dex];
		while(ptr!=0&&ptr->key!=x){
			ptr=ptr->next;
		}
		if(ptr==0){
			Hash[dex]=new llinkNode(x,Hash[dex]);
		}else{
			ptr->cnt++;
		}
	}
}