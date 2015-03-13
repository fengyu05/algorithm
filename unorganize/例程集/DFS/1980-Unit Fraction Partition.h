/* 1980 Unit Fraction Partition
 * 将分数分解成埃及分数和，求可能方案数
 * (p,q,a,n) p/q=1/x1+1/x2+...1/xi st. i<=n && x1*x2*..<=a
 */
const double EPS=1e-12;

int p,q,a,n;
int cnt;
void search(int den,double sum,int cura,int left){
	if(sum<-EPS) return;
	if(sum>=-EPS&&sum<=EPS){ cnt++;return;}
	else{
		for(int i=den;1;i++){
			if(sum-(double)1/i*left>EPS) break;
			if(cura*i>a) break;
			search(i,sum-(double)1/i,cura*i,left-1);
		}
	}
}
int main(){
	while(scanf("%d%d%d%d",&p,&q,&a,&n),p){
		cnt=0;
		search(1,(double)p/q,1,n);
		printf("%d\n",cnt);
	}
	return 0;
}
