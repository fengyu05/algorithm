// stack,queue,heap
#define maxN 500

int stack[maxN],top;
// init top=0;
// push stack[top++]=x;
// pop  x=stack[--top];
// top  x=stack[top-1];

template<class Item>class Queue{
public:
	Item queue[M];
	int front,rear;
	void init(){front=-1,rear=-1;}
	int next(int pos){return (pos+1)%N;}
	void push(Item x){ queue[rear=next(rear)]=x;}
	Item pop(){ return queue[front=next(front)];}
	int size(){ return rear-front;}
};
template<class Item>class Heap{
public:
	Item heap[M];
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
	void improve(Item x){
		int dex;
		for(dex=0;dex<n;dex++){
			if(heap[dex]==x)
				break;
		}
		if(dex<n){
			heap[dex]=x;
			push_heap(heap,heap+dex);
		}else push(x);
	}
};


// version diy
void fixup(int k){ 
	while(k>1&&cmp(heap[k],heap[k/2])){
		swap(heap[k],heap[k/2]);
		k=k/2;
	}
}
void fixdown(int k){
	while(2*k<=N){
		int j=2*k;
		if(j<N&&cmp(heap[j+1],heap[j])) j++;
		if(cmp(heap[k],heap[j])) break;
		swap(heap[k],heap[j]); k=j;
	}
}
void push(int x){ 
	heap[++N]=x;
	fixup(N);
}
int pop(){
	swap(heap[1],heap[N--]);
	fixdown(1);
	return heap[N+1];
}
//int top(){ return heap[1]; }
void buildheap(int n){
	N=n;
	for(int i=n/2;i>0;i--)
		fixdown(i);	
}
void heapsort(int n){
	buildheap(n);
	while(N>1){
		swap(heap[1],heap[N]);
		--N;
		fixdown(1);
	}
}

