// Interval min cover 
struct node{ int a,b;} pp[16000];
bool cmp(node& x,node& y){ return x.a<y.a||(x.a==y.a&&x.b>y.b);}
int main()
{
	int n,i;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d%d",&pp[i].a,&pp[i].b);
	}
	sort(pp,pp+n,cmp);
	int cnt=0;
	int ss=pp[0].a,tt=pp[0].b;
	for(i=1;i<n;i++){
		while(pp[i].b<=tt&&i<n){
			i++;
			cnt++;
		}
		while(pp[i+1].b>=pp[i].b&&pp[i+1].b<=ss&&i<n){
			i++;
			cnt++;
		}
		ss=pp[i].a,tt=pp[i].b;
	}
	int mincover=n-cnt;
}