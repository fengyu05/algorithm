struct node{
	short val;
	int x,y;
	node* next;
	node(int x,int y,short val,node* next=0)
		:x(x),y(y),val(val),next(next){}
};
typedef node* link;
link hash[N];

void init(){
	memset(hash,0,sizeof(hash));
}
void insert(int x,int y,int val){
	int id=Hash(x,y);
	hash[id]=new node(x,y,val,hash[id]);
}
state find_del(int x,int y){
	int id=Hash(x,y);
	link p=0;
	for(link lk=hash[id];lk;lk=lk->next){
		if(lk->x==x&&lk->y==y){
			int val=lk->val;
			if(p==0){//front
				hash[id]=lk->next;
			}else p->next=lk->next;
			delete lk;
			return state(x,y,val);
		}
		p=lk;
	}return null;
}