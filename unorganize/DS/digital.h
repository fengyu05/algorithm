#define L 128 // word length
#define N 1000000
typedef int vtype;

char tree[N],s[L];
int son[N],bro[N],cnt;
vtype data[N];
vtype find(char s[])
{
	int i,j=0;
	for( i=0;s[i];i++){
		j=son[j];
		while( j && tree[j]!=s[i] ) j=bro[j];
		if (!j) return -1;
	}
	return data[j];
}
void add(char s[],vtype x)
{
	int i,j=0,p;
	for( i=0;s[i];i++){
		p=j;j=son[j];
		while(j&&tree[j]!=s[i]) j=bro[j];
		if(!j){
			tree[++cnt]=s[i]; son[cnt]=0;
			bro[cnt]=son[p]; son[p]=cnt;
			data[cnt]=-1; j=cnt;
		}
	}
	data[j]=x;
}
void init(){ cnt=0;bro[cnt]=son[cnt]=0;data[0]=-1;}