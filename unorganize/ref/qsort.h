template<class Item> void exch(Item& A,Item& B){ Item t(A);A=B;B=t;}
// stl stype qsort
template<class Item>
Item* partition(Item *begin,Item *end){
	Item *i=begin-1,*j=end-1;
	Item& v=*j;
	for(;;)
	{
		while(*(++i)<v);
		while(v<*(--j)) if(j==begin) break;
		if(i>=j) break;
		exch(*i,*j);
	}
	exch(*i,v);
	return i;
}

template<class Item>
void qsort(Item *begin,Item *end){	
	if(end<=begin) return;
	Item *m=partition(begin,end);
	qsort(begin,m);
	qsort(m+1,end);
}
