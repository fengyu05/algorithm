//分支限界
Type queue[maxN],front,rear;
int init(){front=-1,rear=-1;}
int next(int pos){return (pos+1)%maxN;}
void push(Type x){ queue[rear=next(rear)]=x;}
Type pop(){ return queue[front=next(front)];}
int size(){ return rear-front;}

Type MaxLoading(Type w[],Type c,int n)
{
	init();
	push(-1);
	int i=1;
	Type cw=0,bestw=0,r=0;
	for(int j=2;j<=n;j++)
		r+=w[i];
	while(1){		
		// leftchild node
		double wt=cw+w[i];
		if(wt<=c){// x[i]=1
			if(wt>bestw) bestw=wt;
			if(i<n) push(wt);
		}
		// rightchild node
		if(cw+r>bestw&&i<n)//x[i]=0
			push(cw);
		// next level node
		cw=pop(); 
		if(cw==-1){
			if(!size()) return bestw;
			push(-1);
			cw=pop();
			i++;
			r-=w[i];
		}
	}
}