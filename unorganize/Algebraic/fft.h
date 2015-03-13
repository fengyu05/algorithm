//------------  Fash Fourier Transform ------------------------------------
#include <iostream>
#include <cmath>
#include <complex>
using namespace std;

const double EPS=1e-8;
const double PI=acos(-1.0);
#define CP complex<double>

inline int max(int a, int b){ a>b?a:b; }
inline int dcmp(double a){ if (a<-EPS) return -1; return a>EPS; }

void fft(CP x[], int n,CP y[], int bInv) // y=Wx, w[j ,k]=e^ijk
{
	if (n==1){ y[0]=x[0]; return; }
	CP *xeven = new CP[n/2] , *xodd = new CP[n/2] ,w(1,0) ,
	*yeven = new CP[n/2] , *yodd = new CP[n/2] , wn;
	int i;
	if (bInv)
		wn=CP( cos(-2*PI/n) , sin(-2*PI/n) );
	else wn=CP( cos ( 2* PI/n) , sin ( 2* PI/n) );
	for( i =0; i<n/2; i++)
	{
		xeven[ i ] = x[ i *2 ];
		xodd [ i ] = x[ i *2+1];
	}
	fft (xeven , n/2 , yeven , bInv );
	fft (xodd , n/2 , yodd , bInv );
	for( i =0; i<n/2; i++)
	{
		y[ i ] = yeven[ i ] + w*yodd[ i ];
		y[ i+n/2] = yeven[ i ] - w*yodd[ i ];
		w *= wn;
	}
	delete xeven,yeven,xodd,yodd;
}

//FFT - Polynomial Multiplication
//Poly form: a[0..na) a0*x^0+a1*x^1+...+a(n-1)*x^(n-1)
void PolyMulti(double a[], int na,double b[], int nb,double c[], int &nc)
{
	int i ,n=na>nb?na:nb;
	n=1<<((int) ceil(log(2*n)/log(2)-EPS ));
	CP *x=new CP[n] , *ya=new CP[n] , *yb=new CP[n] , *yc=new CP[n];
	for( i=0;i<n; i++) x[i]=i<na?a[i]:0;
	fft(x,n,ya,0);
	for( i=0;i<n; i++) x[i]=i<nb?b[i]:0;
	fft(x,n,yb,0);
	for( i=0;i<n; i++) yc[i]=ya[i]*yb[i];
	fft(yc,n,x,1);
	for( i=0;i<n; i++) c[i]=x[i].real()/n;
	for(nc=n; nc>0 && dcmp(c[nc-1])==0; nc--);
	delete x,ya,yb,yc;
}
void testPolyMulti(){
	double a[8],b[8],c[8];
	int na,nb,nc,i;
	scanf("%d%d",&na,&nb);
	for(i=0;i<na;i++) scanf("%lf",&a[i]);
	for(i=0;i<nb;i++) scanf("%lf",&b[i]);
	PolyMulti(a,na,b,nb,c,nc);
	for(i=0;i<nc;i++) printf("% 4.1lf",c[i]);
	printf("\n");
}
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	testPolyMulti();
	return 0;
}