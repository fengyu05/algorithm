// 负权数 展开
int n,r,len; //r for base
char a[256];

void comput(){
	int i,p,n1,r1;
	n1=abs(n),r1=abs(r);
	len=-1;
	memset(a,0,sizeof(a));
	while(n1>0){
		len++;
		a[len]=n1%r1;
		n1/=r1;
	}
	if(n>0) p=1;
	else p=0;
	while(p<=len){
		if(a[p]>0){
			a[p+1]++;
			i=p+1;
			while(a[i]>=r1){
				a[i]-=r1;
				i++;
				a[i]++;
			}
			if(i>len) len=i;
			a[p]=r1-a[p];
		}
		p+=2;
	}
}
void print(){
	for(int i=len;i>=0;i--){
		if(a[i]<10) printf("%d",a[i]);
		else printf("%c",a[i]-10+'a');
	}
	printf("\n");
}

// 10进制  展开成 base进制  
int base(int q,int b,int r[]){// b:base
  int k=0;
  while(q!=0){
    r[k]=q%b;
    q/=b;
    k++;
  }return k;
}
int cal(int n,int b,int r[]){
	int re=0;
	for(int i=0,j=1;i<n;i++,j*=b){
		re+=r[i]*j;
	}return re;
}
//n在b进制下有多少位
 k=log(b,n+1);
//=------------------------
int inv_num(int a){//翻转一个整数 1234 -> 4321
	int re=0;
	while(a){
		re=re*10+a%10;
		a/=10;
	}
	return re;
}
//return the howmany digit
int tostring(int n,char *pos){
	int i=0,t=1;
	while(t<=n){ t*=10,i++;}
	t=i;
	for(i--;i>=0;i--){
		int d=n%10;
		*(pos+i)=d+'0';
		n/=10;
	}
	return t;
}

// digital root
int digit_root(char str[]){
	int i=0,re=0;
	while(str[i]){
		re=(re+(str[i++]-'0'))%9;
	}
	return (re==0)?9:re;
}
int root(int n){
	int i=0,re=0;
	while(n){
		re=(re+(n%10))%9;
		n/=10;
	}
	return (re==0)?9:re;
}
int root_mul(int a,int b){
	return root(root(a)*root(b));
}