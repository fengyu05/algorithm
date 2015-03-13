// Order Statistic Tree, online RMQ (O(n),O(logn)) , Winner Tree

const int N = 131072; //N is a power of 2 and just bigger than n
int ost[N*2],L; //ost[1..2N] ost[i]保存i子树覆盖的区间里最值的序号
int p[N];     //[0..n)
inline int RMQmin(int i,int j)
{// < to get min, > to get max
	return p[i] < p[j]?i:j;
}
void build(int n)//p[0..n)
{
	 L=1;//[1..L-1]内部节点 [L..2L-1] 叶节点
	 while(L<n) L<<=1;
     int f = L, t = L + n - 1, i;//[f,t]
     for(i = 0; i < n; ++i) ost[i+L] = i;
     for( ;f < t; f /= 2, t /= 2){
        for(i = f; i < t ; i+= 2)
            ost[i/2] = RMQmin(ost[i],ost[i+1]);
        if(!(t&1)) ost[t/2] = ost[t];
     }
}
int query(int ss, int ee)//return { i|a[i]=min{a[ss .. ee]} }
{
    ss += L, ee += L;
    int k = RMQmin(ost[ss] ,ost[ee]);
    for(int f = ss, t = ee; f+1 < t; f/=2, t/=2)
    {
        if( !(f&1) ) k = RMQmin(ost[f+1],k);
        if( (t&1) )  k = RMQmin(ost[t-1],k);
    }
    return k;
}
void update(int pos,int x){
	p[pos]=x;
	pos += L;
	int k,nxt;
	for(; pos>1; pos/=2){
		if(pos&1) nxt=pos-1;
		else nxt=pos+1;
		k = RMQmin(ost[pos],ost[nxt]);
		if(k==ost[pos/2]) break;
		else ost[pos/2]=k;
	}
}