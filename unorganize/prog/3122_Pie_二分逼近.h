#include <iostream>
#include <cmath>
using namespace std;
double s[10000];

double pi=acos(-1);
const double deta=0.00001;
int main()
{
	int cas,n,f,p,tmp;  
	scanf("%d",&cas);
	while(cas--)
	{
        scanf("%d%d",&n,&f); f++;
        p=0;
		while(p<n){
			scanf("%d",&tmp);
			s[p++]=tmp*tmp;
		}
        double max = 100000000.0;
		double min =0.0;
		while(max-min > deta){
			double mid =(max+min)/2;
			int num=0;
			for(p=0;p<n;p++){
				if( s[p] >= mid)
                     num +=(int)(s[p] / mid);
			   if( num > f) break;
			}
			if(num>=f)	min = mid;
			else max = mid;
		}
		double rst = (max+min)/2;
		printf("%.5lf\n",rst*pi);
	}
	return 0;
}