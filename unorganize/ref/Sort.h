#ifndef std__SORT__
#define std__SORT__
namespace basic_sort{
template<class Item> void exch(Item& A,Item& B){ Item t(A);A=B;B=t;}
template<class Item> void compexch(Item& A,Item& B){ if(B<A) exch(A,B);}
inline int min(int A,int B){return (A<B)?A:B;}

template<class Item>
void selection(Item a[], int l,int r){
	for(int i=l;i<r;i++){
		int min=i;
		for(int j=i+1;j<=r;j++)
			if(a[j]<a[min])
				min=j;
		exch(a[i],a[min]);
	}
}

template<class Item>
void insertion(Item a[],int l,int r){
	int i;
	for(i=r;i>l;i--) compexch(a[i-1],a[i]);
	for(i=l+2;i<=r;i++){
		int j=i;
		Item v=a[i];
		while(v<a[j-1]){
			a[j]=a[j-1];
			j--;
		}
		a[j]=v;
	}
}

template<class Item>
void bubble(Item a[],int l,int r){
	for(int i=l;i<r;i++)
		for(int j=r;j>i;j--)
			compexch(a[j-1],a[j]);
}

template<class Item>
void shellsort(Item a[],int l,int r){
	int h;
	for(h=1;h<=(r-1)/9;h=3*h+1);
	for(;h>0;h/=3)
		for(int i=l+h;i<=r;i++){
			int j=i;
			Item v=a[i];
			while(j>=l+h&&v<a[j-h]){
				a[j]=a[j-h];
				j-=h;
			}
			a[j]=v;
		}
}

// -------------------- quicksort ---------------------
static const int sort__MINSIZE =10;
template<class Item>
inline int partition(Item a[],int l,int r){
	int i=l-1,j=r;
	Item v=a[r];
	for(;;)
	{
		while(a[++i]<v);
		while(v<a[--j]) if(j==l) break;
		if(i>=j) break;
		exch(a[i],a[j]);
	}
	exch(a[i],a[r]);
	return i;
}

template<class Item>
void quicksort(Item a[],int l,int r){	
	if(r<=l) return;
	int i=partition(a,l,r);
	quicksort(a,l,i-1);
	quicksort(a,i+1,r);
}

template<class Item>
void quicksort_av(Item a[],int l,int r){// Median-fo-Three 
	if(r-l<=sort__MINSIZE) return;
	exch(a[(l+r)/2],a[r-1]);
	compexch(a[l],a[r-1]);
		compexch(a[l],a[r]);
			compexch(a[r-1],a[r]);
	int i=partition(a,l+1,r-1);
	quicksort_av(a,l,i-1);
	quicksort_av(a,i+1,r);
}


template<class Item> //X
inline void three_way_partition(Item a[],int l,int r,int& j,int& i){
	int p=i=l-1,q=j=r; // p==i q==j
	Item v=a[r];
	for(;;){
		while(a[++i]<v);
		while(v<a[--j]) if(j==l) break;
		if(i>=j) break;
		exch(a[i],a[j]);
		if(a[i]==v){p++;exch(a[p],a[i]);}
		if(v==a[j]){q--;exch(a[q],a[j]);}
	}
	exch(a[i],a[r]);
	j=i-1;
	i=i+1;
	for(int k=l;k<=p;k++,j--) exch(a[k],a[j]);
	for(int k=r-1;k>=p;k--,i++) exch(a[k],a[i]);
}


template<class Item>//X
void dk_quicksort(Item a[],int l,int r){
	if(r<=l) return;
	int i,j;
	three_way_partition(a,l,r,j,i);
	dk_quicksort(a,l,j);
	dk_quicksort(a,i,r);	
}

template<class Item>
Item& select(Item a[],int l,int r,int k){
	while(r>l){
		int i=partition(a,l,r);
		if(i>=k) r=i-1;
		if(i<=k) l=i+1;
	}
	return a[k];
}
//-------------------------- mergesort --------------------------
template<class Item>
void in_place_merge(Item a[],int l,int m,int r){
	int i,j;
	static Item aux[5000];
	for(i=m+1;i>l;i--) aux[i-1]=a[i-1];
	for(j=m;j<r;j++) aux[r+m-j]=a[j+1];

	for(int k=l;k<=r;k++)
		a[k]=(aux[j]<aux[i])?aux[j--]:aux[i++];
}
template<class Item>
void mergesortTD(Item a[],int l,int r){
	if(r<=l) return;
	int m=(r+l)/2;
	mergesortTD(a,l,m);
	mergesortTD(a,m+1,r);
	in_place_merge(a,l,m,r);
}
template<class Item>
void mergesortBU(Item a[],int l,int r){
	for(int m=1;m<=r-l;m+=m)
		for(int i=l;i<=r-m;i+=m+m)
			in_place_merge(a,i,i+m-1,min(i+m+m-1,r));
}
template<class Item>
void out_merge(Item out[],Item a[],int l,int m,int r){
	int i=l,j=m+1;
	while(i<=m&&j<=r)
		out[l++]=(a[i]<a[j])?a[i++]:a[j++];
	for(;i<=m;i++)
		out[l++]=a[i];
	for(;j<=r;j++)
		out[l++]=a[j];
}
template<class Item>
void mergesort_av(Item a[],Item b[],int l,int r){
	if(r-l<=sort__MINSIZE){
		insertion(a,l,r);
		return;
	}
	int m=(l+r)/2;
	mergesort_av(b,a,l,m);
	mergesort_av(b,a,m+1,r);
	out_merge(a,b,l,m,r);
}

}// end of ns basic_sort

namespace std{
	template<class Item>
	void quicksort(Item a[],int l,int r){
		basic_sort::quicksort_av(a,l,r);
		basic_sort::insertion(a,l,r);
	}
	template<class Item>
	void mergesort(Item a[],int l,int r){
		Item* aux=new Item[r-l+1];
		for(int i=l;i<=r;i++) aux[i]=a[i];
		basic_sort::mergesort_av(a,aux,l,r);
		delete [] aux;		
	}

}
#endif