#define N 128//0
struct HP {
	int len;
	char s[N];
	HP(int inte=0){
		len=0;
		do{
			s[++len]=inte%10;
			inte/=10;
		}while(inte>0);
	}
	HP(char* str){
		len=strlen(str);
		for(int i=1;i<=len; i++)
			s[i]=str[len-i]-'0';
		while(!s[len]&&len>1) len--;
	}
	void print(){
		for(int i=len;i>=1;i--)
			printf("%d",s[i]);
		printf("\n");
	}
	int tostring(char* str){
		for(int i=len,j=0;i>=1;i--,j++)
			str[j]=s[i]+'0';
		str[j]=0;
		return len;
	}
};
int compare(HP& a,HP& b){
	if (a.len>b.len ) return 1;
	if (a.len<b.len ) return -1;
	int i=a.len;
	while((i>1)&&(a.s[i]==b.s[i])) i--;
	return a.s[i]-b.s[i];
}
HP operator+(HP& a,HP& b){
	HP c;
	int l= (a.len>b.len)?a.len:b.len;
	for(int i=1; i<=l;i++){
		if(i<=a.len) c.s[i]+=a.s[i];
		if(i<=b.len) c.s[i]+=b.s[i];
		c.s[i+1]=c.s[i]/10; c.s[i]%=10;
	}
	c.len=l+1;
	while(!c.s[c.len]&&c.len>1) c.len--;
	return c;
}
HP operator-(HP& a,HP& b){//ct: a >= b 
	HP c;
	for(int i=1,j=0; i<=a.len;i++) {
		c.s[i]=a.s[i]-j ;
		if (i<=b.len) c.s[i]-=b.s[i];
		if (c.s[i]<0){ j=1; c.s[i]+=10; }
		else j=0;
	}
	c.len=a.len;
	while(c.len>1&&!c.s[c.len]) c.len--;
	return c;
}
HP operator*(HP& a,HP& b){
	HP c;
	int i , j ;
	c.len=a.len+b.len ;
	for( i=1;i<=c.len ; i++) c.s[i]=0;
	for( i=1;i<=a.len ; i++)
		for( j=1;j<=b.len ; j++){
			c.s[i+j-1]+=a.s[i]*b.s[j];
			c.s[i+j]+=c.s[i+j-1]/10;
			c.s[i+j-1]%=10;
		}
	for(i=c.len;c.s[i];i++){
		c.s[i+1]=c.s[i]/10;
		c.s[i]%=10;
	}
	while(c.len>1 &&!c.s[c.len]) c.len--;
	return c;
}
HP operator%(HP& a,HP& b){
	HP d;
	for(int i=a.len; i>0;i--){
		int j;
		if( d.len!=1 || d.s[1]!=0 ){ 
			for(j=d.len;j>0;j--)
				d.s[j+1]=d.s[j];
			++d.len;
		}
		d.s[1]=a.s[i];
		while((j=Compare(d,b))>=0 ){
			d=d-b;
			if(j==0) break;
		}
	}
	return d;
}
HP operator/(HP& a,HP &b){
	HP d,c;
	for(int i=a.len; i>0; i--){
		int j;
		if(d.len!=1 || d.s[1]!=0 ){
			for( j=d.len; j>0;j--)
				d.s[j+1]=d.s[j];
			++d.len;
		}
		d.s[1]=a.s[i]; c.s[i]=0;
		while( ( j=Compare(d,b))>=0 ){
			d=d-b;	c.s[i]++;
			if(j==0) break;
		}
	}
	c.len=a.len;
	while(c.len>1&&c.s[c.len]==0) c.len--;
	return c;
}
HP divide(HP& a,HP& b,HP& d=HP(0)){
	HP c;
	d=0;
	for(int i=a.len; i>0; i--){
		int j;
		if(d.len!=1 || d.s[1]!=0 ){
			for( j=d.len; j>0;j--)
				d.s[j+1]=d.s[j];
			++d.len;
		}
		d.s[1]=a.s[i]; c.s[i]=0;
		while( ( j=Compare(d,b))>=0 ){
			d=d-b;	c.s[i]++;
			if(j==0) break;
		}
	}
	c.len=a.len;
	while(c.len>1&&c.s[c.len]==0) c.len--;
	return c;
}

// for test
void main()
{
	int ss = clock();
	int right=0;
	for(int i=0;i<10000;i++){
		int a=abs(rand()*rand());
		int t=abs(rand());

		if(t==0) continue;
		int r=a%t;
		HP ha=a,ht=t,hd;
		HP hr=divide(ha,ht,hd);
		HP hr2=r;
		if(Compare(hd,hr2)!=0){
			printf("%d / %d= %d  while ",a,t,r);
			hr.print();
		}else right++;
	}
	printf("%d are right\n",right);
   printf("%f\n", (double)(clock()-ss)/1000); 

}