/* Problem 2559:
 Largest Rectangle in a Histogram
Divide-and-conquer using order-statistic trees.

Initially, build a binary, node- and leaf-labeled tree 
that contains the histogram as its frontier, i.e., as 
its leaves from left to right. Mark each inner node with
 the minimum of the labels of its subtree. Note that such
 a tree is most efficiently stored in an array using the 
 heap data structure, where the children of node i are 
 located at positions i*2 and i*2+1, respectively. With 
 such an order-statistic tree, the minimum element in a 
 subhistogram (i.e., a subsegment of the sequence of heights)
 can be found in O(log(n)) steps by using the additional 
 information in the inner nodes to avoid searching all leaves.
To calculate the maximum rectangle unter a subhistogram, we 
thus find the minimum height in that subhistogram, and divide 
it at just that place into two smaller histograms. The maximum
 rectangle is either completely in the left part, or completely
 in the right part, or it contains the rectangle with minimum 
 height. The first two cases are solved recursively, while in 
 the third case we know that the width of the maximum rectangle
 is the width of the whole subhistogram, since we chose the 
 minimum height. Because every element serves exactly once as 
 a place to divide, and we spend O(log(n)) for every division, 
 the complexity of this algorithm is O(n*log(n)).
*/
/* 4520K	250MS */
#define N 131072

int p[N];
int os[2*N],len;
int Min(int x,int y){
	if(x==-1) return y;
	if(y==-1) return x;
	if(p[x]<p[y]) return x;
	else return y;
}
//½ô´ÕµÄost
void build_order_statistic_trees(int left,int right){// [left..right]
	while(left!=right){
		int i;
		for(i=left;i<right;i+=2){
			os[i/2]=Min(os[i],os[i+1]);//**
		}
		if(i==right) os[i/2]=os[i];
		left>>=1,right>>=1;
	}
}
int query(int a,int b,int pos,int left,int right){//[a..b]
	if(a<=left&&right<=b) return os[pos];
	int mid=(left+right)/2;
	int m1=-1,m2=-1;
	if(a<=mid)
		m1=query(a,b,pos*2,left,mid);
	if(b>=mid+1)
		m2=query(a,b,pos*2+1,mid+1,right);
	return Min(m1,m2);//**
}
int query(int a,int b){
	return query(a,b,1,len,2*len-1);
}
double cal(int a,int b){
	if(a>b) return 0;
	if(a==b) return p[a];
	int pos=query(len+a,len+b);
	double re=(double)(b-a+1)*p[pos];
	double r1=cal(a,pos-1);
	double r2=cal(pos+1,b);
	if(r1>re) re=r1;
	if(r2>re) re=r2;
	return re;
}
int main()
{	
	int n;
	while(scanf("%d",&n),n){
		len=1;
		while(len<n) len=len<<1;
		for(int i=0;i<n;i++){//[len..len+n-1]
			scanf("%d",&p[i]);
			os[i+len]=i;
		}		
		build_order_statistic_trees(len,len+n-1);
		printf("%.0lf\n",cal(0,n-1));
	}
	return 0;
}