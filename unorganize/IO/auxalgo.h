template <class T>
void read(T beg,int cnt){
    while(cnt--) cin>>(*beg++);
}
template<class T>
void print(T beg,int cnt,char* text=""){
    cout<<text<<*beg;
    while(cnt-->1)
        cout<<' '<<*(++beg);
    cout<<endl;
}
template <class T>
void insert(T beg, int first, int last){
    for(int i=first; i<=last;++i)
        *beg=i,++beg;
}

// 数出最多相同元素的个数
typedef double item;
int countmost(item a[],int n)
{// a[] must be sort
	int re=1,tmp=1;
	for(int i=1;i<n;i++){
		if(a[i]==a[i-1]){
			tmp++;
			if(tmp>re) re=tmp;
			//(tmp<re) for countless
		}else
			tmp=1;		
	}
	return re;
}