/* 2718 Smallest Difference
 * Ì°ÐÄ+±©Á¦
 * feng
 */
#include <iostream>

using namespace std;
#define MAXINT 1000000
template<class Item> void exch(Item& A,Item& B){ Item t(A);A=B;B=t;}
int dif(int a[],int b[],int n){
	int re=0;
	for(int i=0;i<n;i++)
		re=re*10+a[i]-b[i];
	return re;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("D:\\acm\\acm\\input.txt", "r", stdin);
	//freopen("D:\\acm\\acm\\output.txt", "w", stdout);
#endif
    int cas,p[10],a[5],b[5];
    cin>>cas; cin.get();
    while(cas--) {
		char ch;
        int j=0;
		while((ch=cin.get())!='\n'&&!cin.eof()){
            if(ch>='0'&&ch<='9')  p[j++]=ch-'0'; 
        }
		if(j==2) cout<<p[1]-p[0]<<endl;
        else if(j%2==1){
            if(p[0]==0) exch(p[0],p[1]);
			a[0]=p[0]; b[0]=0;
			for(int i=1;i<=j/2;i++){
				a[i]=p[i];
				b[i]=p[j-i];
			}
			cout<<dif(a,b,j/2+1)<<endl;
        } else {
			int val=MAXINT,temp;
			for(int i=(p[0]?0:1);i<j-1;i++){
				temp=p[i+1]-p[i];
				if(temp<val)
					val=temp;
			}
			int min=MAXINT;
			for(i=(p[0]?0:1);i<j-1;i++){
				if((p[i+1]-p[i])==val){
					a[0]=p[i+1];
					b[0]=p[i];
					int a_c=1,b_c=j/2;
					for(int k=0;k<j;k++){
						if(k==i+1||k==i) continue;
						if(a_c<j/2) a[a_c++]=p[k];
						else b[--b_c]=p[k];
					}
					temp=dif(a,b,j/2);
					min=min<temp?min:temp;
				}
			}
			cout<<min<<endl;
        }          
    }        
	return 0; 
}