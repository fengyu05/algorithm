#include <iostream>
using namespace std;

/* string - matching algorithm */
#define T_LEN 65536
#define P_LEN 256
char T[T_LEN],P[P_LEN];//[0..]
//------------------ Rabin-Karp --------------------------------------
//a^b mod n 
int mod_exp(int a, int b, int n)
{
	int t=1,y=a;
	while(b!=0){
		if (b&1) t=t*y%n;
		y=y*y%n;//advert overflow
		b>>=1;
	}
	return t ;
} 
int Rabin_Karp(int n,int m,int start_pos,int d,int Q){
	int h=mod_exp(d,m-1,Q);
	int p=0,t=0,s=start_pos;
	for(int i=0;i<m;i++){
		p=(d*p+P[i])%Q;
		t=(d*t+T[s+i])%Q;
	}
	for(;s<n-m;s++){
		if(p==t){
			bool match=true;
			for(int i=0;i<m;i++){
				if(P[i]!=T[s+i]){
					match=false;
					break;
				}
			}
			if(match) return s;
		}
		t=(d*(t-T[s]*h)+T[s+m])%Q;
		if(t<0) t+=Q;
	}
	return -1;
}
//--------------------- finite automata ------------------------------
#define SIZE 256 // siz of alphabet
#define min(a,b) (a<b?a:b)
int tran[P_LEN][SIZE];
int automata(int n,int m,int start_pos){
	int state=0 , s=start_pos;
	for(;s<n;s++){
		state=tran[state][T[s]];
		if(state==m) return s;
	}
	return -1;
}
bool suffix(char *a,int a_len,char *b,int b_len){
	//true iff a is b suffix
	int i=0;
	for(;i<a_len;i++){
		if(a[a_len-1-i]!=b[b_len-1-i]) break;
	}
	return i==a_len;
}
void compute_tran_fun(int m,char beg,char end){
	char tmp[SIZE];
	strcpy(tmp,P);
	for(int q=0;q<=m;q++){
		//a belong to [beg,end]
		for(char a=beg;a<=end;a++){
			int k=min(m+1,q+2);
			bool stop=false;
			do{
				k--;
				char ch=tmp[q];
				tmp[q]=a;
				if(suffix(P,k,tmp,q+1))
					stop=true;
				tmp[q]=ch;
			}while(!stop);
			tran[q][a]=k;
		}
	}
}
void print_tran(int m,char beg,char end){
	printf("%s","state");
	for(char ch=beg;ch<=end;ch++){
		printf(" %c ",ch);
	} printf("\n");
	for(int i=0;i<=m;i++){
		printf("%3d  ",i);
		for(char ch=beg;ch<=end;ch++){
			printf(" %d ",tran[i][ch]);
		} printf("\n");	
	}
}
void automata_solve(){
	// ababaca
	// abababacaba
	scanf("%s%s",P,T);
	int m=strlen(P);
	int n=strlen(T);
	compute_tran_fun(m,'a','c');
	print_tran(m,'a','c');
	int re=automata(n,m,0);
	printf("match at T[%d,%d]\n",re-m+1,re);
}
//----------------- Kunth Morris Pratt algoithm ----------------
int next[P_LEN];
void compute_prefix_fun(int m){
	next[0]=0;
	int k=0;
	for(int q=1;q<m;q++){
		while(k>0&&P[k]!=P[q]){
			k=next[k-1];
		}
		if(P[k]==P[q]) k++;
		next[q]=k;		
	}
}
int KMP_match(int n,int m,int start_pos){
	int q=0;
	for(int i=start_pos;i<n;i++){
		while(q>0&&P[q]!=T[i])
			q=next[q-1];
		if(P[q]==T[i]) q++;
		if(q==m){
			return i-m+1;
			//q=next[q-1]; for next match
		}
	}
	return -1;
}
// KMP conformity edition
int KMP(int n,int m)
{
	int p=0,t=0, next[P_LEN];
	next[0]=-1;
	for(int i=1;i<m;i++){
		int j=next[i-1];
		while(j>=0&&P[i]!=P[j+1]) j=next[j];
		if (P[i]==P[j+1]) next[i]=j+1;
		else next[i]=-1;
	}
	while(p<m&&t<n){
		if (P[p]==T[t]){
			p++;t++;
		}
		else if(p==0)t++;
		else p=next[p-1]+1;
	}
	if(p<m) return -1;
	else return t-m;
}
void KMP_solve(){
	scanf("%s%s",P,T);
	int m=strlen(P);
	int n=strlen(T);
	compute_prefix_fun(m);
	int re=KMP_match(n,m,0);
	int re2=KMP(n,m);
	printf("KMP1: %d\n",re);
	printf("KMP2: %d\n",re2);
}
//-------------------------------------------------------------
int main()
{
	freopen("t.in", "r", stdin);
	KMP_solve();
	return 0;
}
