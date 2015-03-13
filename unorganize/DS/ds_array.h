template<class Item,int __SIZE>class Stack{
public:
	Item array[__SIZE];
	int top;
	void init(){top=0;}
	void push(Item x){ array[top++]=x;}
	Item pop(){ return array[--top];}
	Item peek(){ return array[top-1];}
	int size(){ return top;}
};
template<class Item,int __SIZE>class Queue{
public:
	Item array[__SIZE];
	int front,rear;
	void init(){front=-1,rear=-1;}
	int next(int pos){return (pos+1)%__SIZE;}
	void push(Item x){ array[rear=next(rear)]=x;}
	Item pop(){ return array[front=next(front)];}
	int size(){ return rear-front;}
};
template<class Item,int __SIZE>class Heap{
public:
	Item array[__SIZE];
	int n;
	int size(){return n;}
	void init(){n=0;}
	void push(Item x){
		array[n++]=x;
		push_heap(array,array+n);
	}
	Item pop(){
		pop_heap(array,array+n);
		return array[--n];
	}
	void improve(Item x){
		int dex;
		for(dex=0;dex<n;dex++){
			if(array[dex]==x)
				break;
		}
		if(dex<n){
			array[dex]=x;
			push_heap(array,array+dex);
		}else push(x);
	}
};
//------------------------------------------------------
template<class Item,int __SIZE>class Min_Max_Heap{
public://小大根交替堆,require Item
	Item c_heap[__SIZE];
	int cnt;
	void init(){cnt=0;}
	int min_max(int idx)
	{//判断大层(1)还是小层(0)
		int r=0;
		while(idx>1){
			idx>>=1;
			r++;
		}
		return r&1;
	}
	int h_cmp(int idx_f, int idx_c)
	{
		int r=c_heap[idx_f]-c_heap[idx_c];
		if(min_max(idx_f)==0)r=-r;
		return r;
	}
	void add_new(Item cl)
	{
		c_heap[++cnt]=cl;
		int f=cnt>>1, c=cnt;
		if(f>0 && h_cmp(f, c)<0)
		{
			swap(c_heap[f], c_heap[c]);
			c=f; f>>=2;
		}else f>>=1;
		for(; f>0; c=f, f>>=2)
		{
			if(h_cmp(f, c)>=0)break;
			swap(c_heap[f], c_heap[c]);
		}
	}
	void adjust(int idx)
	{
		int c, i, j;
		while((idx<<1)<=cnt)
		{
			for(i=0, c=idx<<1; i<2 && c<=cnt; i++, c++)
			{
				if(h_cmp(idx, c)<0)
				swap(c_heap[idx], c_heap[c]);
			}  
			//找出孙节点中最小的节点
			j=0;
			Client temp=c_heap[idx];
			for(i=0, c=idx<<2; i<4 && c<=cnt; i++, c++)
			{
				if(h_cmp(idx, c)<0)
				{
					c_heap[idx]=c_heap[c];
					j=c;
				}
			}
			if(j==0)break;
			//最小孙节点再和其父节点比较
			c_heap[j]=temp;
			if(h_cmp(j>>1, j)<0)
				swap(c_heap[j>>1], c_heap[j]);
			idx=j;
		}
	}
	int get_min(Item &res)
	{
		if(cnt<1) return 0;
		res=c_heap[1];
		c_heap[1]=c_heap[cnt--];
		adjust(1);
		return 1;
	}
	int get_max(Item &res)
	{
		if(cnt<1)return 0;
		int i=1;
		if(cnt>1)
		{
			i=2;
			if(cnt>2 && h_cmp(2, 3)<0)
			i=3;
		}
		res=c_heap[i];
		c_heap[i]=c_heap[cnt--];
		adjust(i);
		return 1;
	}
};
struct Client{
	int k, p;
	Client(int k=0,int p=0):k(k),p(p){}
	operator int() const{ return p; }	
};